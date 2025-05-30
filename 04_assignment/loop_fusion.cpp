#include "utility.cpp"

using namespace llvm;

enum AdjacencyStatus {
    NotAdjacent = 0,
        GuardedAdjacent = 1,
        UnguardedAdjacent = 2
};

// =========================== CHECK 1 (Adiacenza) ===============================
/*
Funzione che usiamo nel check1 per controllare l'uguaglianza delle due
espressioni contenute nelle guardie, nel caso 1 (quello appunto con due loop
guarded)
*/
bool AreEquivalentComparisons(Value * expr0, Value * expr1) {
    ICmpInst * cmp1 = dyn_cast < ICmpInst > (expr0);
    ICmpInst * cmp2 = dyn_cast < ICmpInst > (expr1);
    if (!cmp1 || !cmp2) {
        return false;
    }
    if (cmp1 -> getOperand(0) -> getType() != cmp2 -> getOperand(0) -> getType())
        return false;

    // Ci facciamo dare il predicato e i due operandi, per non limitarci al
    // semplice controllo sull'esattezza membro a membro
    ICmpInst::Predicate pred1 = cmp1 -> getPredicate();
    Value * lhs1 = cmp1 -> getOperand(0);
    Value * rhs1 = cmp1 -> getOperand(1);

    ICmpInst::Predicate pred2 = cmp2 -> getPredicate();
    Value * lhs2 = cmp2 -> getOperand(0);
    Value * rhs2 = cmp2 -> getOperand(1);

    // ontrolla che sia esattamente uguale
    if (pred1 == pred2 && lhs1 == lhs2 && rhs1 == rhs2) return true;

    // Controlla se sono uguali ma semplicemente invertite (es. x < 0 == 0 > x)
    if (lhs1 == rhs2 && rhs1 == lhs2) {
        // Questa funzione permette di scambiare il predicato, come nell'esempio
        // sopra
        auto swapped = ICmpInst::getSwappedPredicate(pred2);
        if (pred1 == swapped) return true;
    }

    return false;
}

/**
Funzione che controlla che il blocco che collega i due loop non contenga in
mezzo altre istruzioni. Distinguiamo due casi:
- Se stiamo parlando di due loop guarded dobbiamo avere esattamente 1 branch e 1
compare
- In caso di due loop non guarded dobbiamo avere esattamente 1 branch
*/
bool clear_intermediate_bb(BasicBlock * bb, bool is_guarded) {
    int branch_count = 0;
    int icmp_count = 0;
    int phi_count = 0;

    for (Instruction & I: * bb) {
        if (isa < BranchInst > (I)) {
            branch_count++;
        } else if (isa < ICmpInst > (I)) {
            icmp_count++;
        } else if (isa < PHINode > (I)) {
            continue;
        } else {
            return false;
        }
    }

    if (is_guarded)
        return branch_count == 1 && icmp_count == 1;
    else
        return branch_count == 1 && icmp_count == 0;
}

/*
Check 1: adiacenza
Abbiamo usato un enum personalizzato come tipo di ritorno, perche' ci servira'
sapere se siamo nel caso 1 o nel caso 2 (ovvero con Loop entrambi guarded o
entrambi non guarded) nel check 3 sulla cf equivalenza.
*/
AdjacencyStatus are_adjacent(Loop * L0, Loop * L1) {
    bool L0_guarded = L0 -> isGuarded();
    bool L1_guarded = L1 -> isGuarded();

    outs() << "\tL0_guarded: " << L0_guarded << "\n";
    outs() << "\tL1_guarded: " << L1_guarded << "\n";

    // --- CASO 1: Entrambi guarded ---
    if (L0_guarded && L1_guarded) {
        outs() << "\t[✓] Entrambi i loop sono guarded\n";

        BranchInst * guard0 = L0 -> getLoopGuardBranch();
        BranchInst * guard1 = L1 -> getLoopGuardBranch();

        if (!guard0 || !guard1) {
            outs() << "\t[X] Una delle guardie è null\n";
            return NotAdjacent;
        }

        // Ora facciamo un controllo sul fatto che il BB a cui punta la guardia 0,
        // ovviamente non quello dentro al loop deve essere l'entry del loop 1, che
        // in questo caso e' il blocco che contiene la guardia 1
        BasicBlock * entry1 = guard1 -> getParent();
        BasicBlock * out_guard0 =
            guard0 -> getSuccessor(1); // ipotizziamo true = dentro, false = fuori
        if (out_guard0 != entry1) {
            outs() << "\t[X] La guardia di L0 non punta all'entry di L1\n";
            return NotAdjacent;
        }
        outs() << "\t[✓] La guardia di L0 punta all'entry di L1\n";

        // Ora controlliamo che non ci siano istruzioni nel blocco di guardia per
        // assicurarci che i loop siano effettivamente adiacenti, senza rischiare
        // che delle istruzioni tra i due loop si "infilino" nel bb della guardia 1
        bool is_guarded = true;
        if (!clear_intermediate_bb(out_guard0, is_guarded)) {
            outs() << "\t[X] Il blocco intermedio non è pulito\n";
            return NotAdjacent;
        }

        // Finito di controllare la struttura del CFG, dobbiamo assicurarci che le
        // condizioni delle guardie siano equivalenti
        Value * expr0 = guard0 -> getCondition();
        Value * expr1 = guard1 -> getCondition();

        outs() << "\tCondizione guard0: " << * expr0 << "\n";
        outs() << "\tCondizione guard1: " << * expr1 << "\n";

        if (AreEquivalentComparisons(expr0, expr1)) {
            outs() << "\t[✓] Le condizioni di guardia sono equivalenti\n";
            return GuardedAdjacent;
        } else {
            outs() << "\t[X] Le condizioni di guardia sono diverse\n";
            return NotAdjacent;
        }
    }

    // --- CASO 2: Entrambi non guarded ---
    if (!L0_guarded && !L1_guarded) {
        outs() << "\t[✓] Entrambi i loop NON sono guarded\n";

        BasicBlock * exitL0 = L0 -> getExitBlock();
        BasicBlock * preheaderL1 = L1 -> getLoopPreheader();
        outs() << "\tPreheader L1: " << preheaderL1 -> getName() << "\n";

        outs() << "\tExit L0: " << exitL0 -> getName() << "\n";

        if (!exitL0 || !preheaderL1) {
            outs() << "\t[X] Exit0 o preheader1 è null\n";
            return NotAdjacent;
        }

        bool is_guarded = false;
        if (exitL0 == preheaderL1 &&
            clear_intermediate_bb(preheaderL1, is_guarded)) {
            return UnguardedAdjacent;
        }

        outs() << "\t[X] I blocchi non coincidono o contengono istruzioni non "
        "valide\n";
        return NotAdjacent;
    }

    // --- CASO 3: Uno guarded, l’altro no ---
    outs() << "\t[X] Un solo loop è guarded: caso non valido per adiacenza\n";
    return NotAdjacent;
}
// =========================== FINE CHECK 1 ===============================

// =========================== CHECK 3 (CF EQUIVALENZA) ===============================

/*
Check 3: cf equivalenza
Prima ricaviamo i due BB su cui verificare la condizione in questi due casi:
- se stiamo facendo i controlli con due loop guarded allora le condizioni di dom
e postdom le controllo su i BB che contengono le guard
- se siamo nel caso di due loop non guarded, le condizioni di dom e postdom le
controllo sui Preheader Successivamente, controlliamo che il blocco selezionato
del loop0 domini il loop1 e viceversa per la postdominanza.
*/
bool are_cf_equivalent(Loop * L0, Loop * L1, DominatorTree & DT,
    PostDominatorTree & PDT, AdjacencyStatus status) {
    BasicBlock * B0 = nullptr;
    BasicBlock * B1 = nullptr;

    // Distinguiamo i due casi, cambiano solo i blocchi di partenza ma la logica e
    // il codice sotto rimane uguale
    if (status == UnguardedAdjacent) {
        B0 = L0 -> getLoopPreheader();
        B1 = L1 -> getLoopPreheader();
    } else if (status == GuardedAdjacent) {
        B0 = L0 -> getLoopGuardBranch() -> getParent();
        B1 = L1 -> getLoopGuardBranch() -> getParent();
    }

    // Controllo per sicurezza
    if (!B0 || !B1) return false;

    // Check sulla dominanza L0->L1
    bool L0_dom_L1 = false;
    DomTreeNode * LI_Node = DT.getNode(B0);
    for (auto * DTN: breadth_first(LI_Node)) {
        if (DTN -> getBlock() == nullptr) continue;
        BasicBlock * curr_block = DTN -> getBlock();
        if (curr_block == B1) {
            L0_dom_L1 = true;
            break;
        }
    }

    // Check sulla postdominanza L1->L0
    bool L1_postdom_L0 = false;
    auto * LI1_Node = PDT.getNode(B1);
    for (auto * PDTN: breadth_first(LI1_Node)) {
        if (PDTN -> getBlock() == nullptr) continue;
        BasicBlock * curr_block = PDTN -> getBlock();
        if (curr_block == B0) {
            L1_postdom_L0 = true;
            break;
        }
    }

    return L0_dom_L1 && L1_postdom_L0;
}

// =========================== FINE CHECK 3 ===============================

// ========================= CHECK 2 (Stesso numero di iterazioni) =======================

/*
Check 2:
Questo check deve assicurasi che i due loop iterino lo stesso numero di volte
*/
bool same_number_of_iterations(Loop * L0, Loop * L1, ScalarEvolution & SE) {
    const SCEV * TripCount0 = SE.getBackedgeTakenCount(L0);
    const SCEV * TripCount1 = SE.getBackedgeTakenCount(L1);

    outs() << "\tTC0: " << * TripCount0 << "\n";
    outs() << "\tTC1: " << * TripCount1 << "\n";

    // Uguaglianza semantica
    if (SE.isKnownPredicate(ICmpInst::ICMP_EQ, TripCount0, TripCount1))
        return true;

    // Caso particolare: TC0 = smax(0, %n), TC1 = %n
    if (const auto * SMax = dyn_cast < SCEVSMaxExpr > (TripCount0)) {
        if (SMax -> getNumOperands() == 2) {
            if (SMax -> getOperand(0) -> isZero() && SMax -> getOperand(1) == TripCount1)
                return true;
            if (SMax -> getOperand(1) -> isZero() && SMax -> getOperand(0) == TripCount1)
                return true;
        }
    }

    // Simmetrico
    if (const auto * SMax = dyn_cast < SCEVSMaxExpr > (TripCount1)) {
        if (SMax -> getNumOperands() == 2) {
            if (SMax -> getOperand(0) -> isZero() && SMax -> getOperand(1) == TripCount0)
                return true;
            if (SMax -> getOperand(1) -> isZero() && SMax -> getOperand(0) == TripCount0)
                return true;
        }
    }

    return false;
}

// =========================== FINE CHECK 2 ===============================

// =========================== CHECK 4 (No dipendenze negative) ============================

/*
E' la funzione usata dal check4 per controllare eventuali dipendenze negative
nelle istruzioni, in maniera "incrociata" Il parametro direction serve proprio a
questo, per capire se stiamo lavorando con store loop 1 e load loop 0 o
viceversa (NOTA: questo ci e' utile solo per prendre l'operando giusto, si
poteva mettere un if) Ma come funziona il controllo?? Innanzitutto, chiamiamo la
funzione depends che ritorna una eventuale dipendenza; se potrebbe esserci e
quindi dep e' a true, allora controlliamo se e' a distanza negativa Per fare
cio', partiamo facendoci dare il puntatore all'elemento dell'array corrente, per
poi ricavarne, con una serie di trasformazioni, l'operando effettivo che ci dice
quale posizione dell'array vogliamo consultare, per le due istruzioni.
Ora che abbiamo le posizioni di accesso andiamo a calcolarci gli scalar
evolution e su di quelli facciamo i controlli:
- Se lo start dello SE degli accessi nel loop 1 parte piu' avanti del loop 0...
CONTROLLO NON PASSATO
- Se l'incremento dello SE degli accessi nel loop 1 cresce piu' velocemente (e
quindi e' maggiore) del loop 0... CONTROLLO NON PASSATO
*/

bool check_neg_dep(std::vector < Instruction * > L0_instr,
    std::vector < Instruction * > L1_instr, DependenceInfo & DI,
    ScalarEvolution & SE, int direction) {
    for (auto * I0: L0_instr) {
        for (auto * I1: L1_instr) {
            // Guardiamo se intanto c'e' il rischio di una dipendenza
            std::unique_ptr < Dependence > dep = DI.depends(I0, I1, true);
            if (dep) {
                // Visto che il rischio c'e', controlliamo se effettivamente siamo nel
                // caso di una dipendenza a distanza negativa
                outs() << "[X] Trovata possibile dipendenza tra " << * I0 << " e " << * I1 <<
                    "\n";

                // Ci facciamo dare il calcolatore del puntatore...
                GetElementPtrInst * ptr0 =
                    dyn_cast < GetElementPtrInst > (I0 -> getOperand(1 - direction));
                GetElementPtrInst * ptr1 =
                    dyn_cast < GetElementPtrInst > (I1 -> getOperand(direction));
                outs() << "ptr0: " << * ptr0 << "\n... e ptr1: " << * ptr1 << "\n";

                // ... cosi' da poter ragionare sugli accessi
                auto DepOp0 = dyn_cast < Instruction > (ptr0 -> getOperand(1)) -> getOperand(0);
                auto DepOp1 = dyn_cast < Instruction > (ptr1 -> getOperand(1)) -> getOperand(0);

                outs() << "Operandi...\n\t\t" << * DepOp0 << "\n\t\t" << * DepOp1 << "\n";
                printSeparator();

                const SCEVAddRecExpr * Trip0 =
                    dyn_cast < SCEVAddRecExpr > (SE.getSCEV(DepOp0));
                const SCEVAddRecExpr * Trip1 =
                    dyn_cast < SCEVAddRecExpr > (SE.getSCEV(DepOp1));
                // Una volta ricavate le triple, con start, operatore e incremento,
                // possiamo fare i nostri controlli...
                if (Trip0 && Trip1) {
                    const SCEV * Start0 = Trip0 -> getStart();
                    const SCEV * Start1 = Trip1 -> getStart();

                    outs() << "Tripla 0: " << * Trip0 << "\n";
                    outs() << "Tripla 1: " << * Trip1 << "\n";

                    outs() << "Start 0: " << * Start0 << "\n";
                    outs() << "Start 1: " << * Start1 << "\n";

                    const SCEVConstant * StartConst0 = dyn_cast < SCEVConstant > (Start0);
                    const SCEVConstant * StartConst1 = dyn_cast < SCEVConstant > (Start1);

                    if (StartConst0 && StartConst1) {
                        const llvm::APInt & Val0 = StartConst0 -> getAPInt();
                        const llvm::APInt & Val1 = StartConst1 -> getAPInt();
                        // Controllo a. se il loop 1 cerca di accedere ad un elemento
                        // successivo a quello consultato da loop 0 non va bene
                        if (Val0.slt(Val1)) {
                            outs() << "Start del secondo loop maggiore del primo\n";
                            return false;
                        } else {
                            // Controllo b. se il loop 1 fa dei tentativi di accesso che a
                            // lungo andare crescono piu' velocemente
                            outs() << "Okay, start del secondo loop minore del secondo, "
                            "controlliamo il passo...\n";
                            const SCEV * Increment0 = Trip0 -> getStepRecurrence(SE);
                            const SCEV * Increment1 = Trip1 -> getStepRecurrence(SE);
                            outs() << "Increment 0: " << * Increment0 << "\n";
                            outs() << "Increment 1: " << * Increment1 << "\n";
                            const SCEVConstant * IncrementConst0 =
                                dyn_cast < SCEVConstant > (Increment0);
                            const SCEVConstant * IncrementConst1 =
                                dyn_cast < SCEVConstant > (Increment1);
                            if (IncrementConst0 && IncrementConst1) {
                                const llvm::APInt & Val0 = IncrementConst0 -> getAPInt();
                                const llvm::APInt & Val1 = IncrementConst1 -> getAPInt();
                                if (Val0.slt(Val1)) {
                                    outs() << "Increment del secondo loop maggiore del primo\n";
                                    return false;
                                } else {
                                    outs() << "anche controllo su incremento passato\n";
                                }
                            }
                        }
                    } else {
                        outs() << "Una delle start non è una costante SCEV\n";
                        return false;
                    }
                } else {
                    outs() << "Almeno una delle due non è una SCEVAddRecExpr\n";
                    return false;
                }
            } else {
                outs() << "\t[✓] Nessuna dipendenza negativa tra " << * I0 << " e " <<
                    *
                    I1 << "\n";
            }
        }
    }
    return true;
}

/*
Check 4: Negative Depentencies
Questo check richiede che non ci siano dipendenze a distanza negativa tra i due
loop I casi che ci dobbiamo assicurare di evitare sono:
- quando il primo loop accede successivamente a valori modificati nelle
iterazioni precedenti dal secondo loop es: loop1:
...
a = array[i]
...
loop2:
...
array[i+1] = b
...

- quando il secondo loop accede ad un valore che nel primo loop verrebbe
modificato in un'iterazione successiva es: loop1:
...
array[i] = a
...
loop2:
...
b = array[i+3]
...
Per occuparci di questi due casi dobbiamo trattare le istruzioni che accedono
alla memoria, che sono le load e le store ed in particolare fare un controllo
"incrociato":
- store nel loop 0 con load nel loop 1
- store nel loop 1 con load nel loop 0
e per farlo lavoriamo in due step:

1. Popoliamo 4 vettori con load e store per entrambi i loop
2. Facciamo il controllo incrociato, con logica realizzata dalla funzione
check_neg_dep
*/
bool no_negative_dependencies(Loop * L0, Loop * L1, DependenceInfo & DI,
    ScalarEvolution & SE) {
    // Innanzitutto, ci occupiamo di ricavare le istruzioni che ci servono dai due
    // loop
    std::vector < Instruction * > L0_store_instructions;
    std::vector < Instruction * > L1_load_instructions;

    std::vector < Instruction * > L1_store_instructions;
    std::vector < Instruction * > L0_load_instructions;

    outs() << "\tL0 instructions:\n";
    for (BasicBlock * BB: L0 -> getBlocks()) {
        for (Instruction & I: * BB) {
            if (isa < StoreInst > (I)) {
                L0_store_instructions.push_back( & I);
                outs() << "Store: " << I << "\n";
            }
            if (isa < LoadInst > (I)) {
                L0_load_instructions.push_back( & I);
                outs() << "Load: " << I << "\n";
            }
        }
    }

    outs() << "\tL1 instructions:\n";
    for (BasicBlock * BB: L1 -> getBlocks()) {
        for (Instruction & I: * BB) {
            if (isa < LoadInst > (I)) {
                L1_load_instructions.push_back( & I);
                outs() << "Load: " << I << "\n";
            }
            if (isa < StoreInst > (I)) {
                L1_store_instructions.push_back( & I);
                outs() << "Store: " << I << "\n";
            }
        }
    }

    outs() << "\tL0 store instructions: " << L0_store_instructions.size() << "\n";
    outs() << "\tL1 load instructions: " << L1_load_instructions.size() << "\n\n";

    outs() << "\tL0 load instructions: " << L0_load_instructions.size() << "\n";
    outs() << "\tL1 store instructions: " << L1_store_instructions.size() << "\n";

    outs() << "========= Fine individuazione load e store... ========\n\n";

    // Successivamente, controlliamo dipendenze negative "incrociate"

    bool neg_dep_store0_load1 = true;
    if (L0_store_instructions.size() && L1_load_instructions.size()) {
        neg_dep_store0_load1 =
            check_neg_dep(L0_store_instructions, L1_load_instructions, DI, SE, 0);
    }

    bool neg_dep_store1_load0 = true;
    if (L1_store_instructions.size() && L0_load_instructions.size()) {
        neg_dep_store1_load0 =
            check_neg_dep(L0_load_instructions, L1_store_instructions, DI, SE, 1);
    }

    return neg_dep_store0_load1 && neg_dep_store1_load0;
}

// =========================== FINE CHECK 4 ===============================

// =========================== FUSION effettiva ===============================

/*
Con questo controlliamo in che caso siamo, se ruotato o meno. 
Dato il BB di un latch, se la sua branch instruction e' condizionale vuol dire che siamo nel caso ruotato,
altrimenti nel caso non ruotato.
NOTA: forse c'erano altri metodi piu' eleganti, abbiamo constatato che questo sia comunque significativo.

*/
int checkLatchBranchType(BasicBlock * Latch) {
    if (!Latch) {
        errs() << "Loop has no latch!\n";
        return 0;
    }

    Instruction * Term = Latch -> getTerminator(); // Ultima istruzione del latch

    if (BranchInst * BI = dyn_cast < BranchInst > (Term)) {
        if (BI -> isConditional()) {
            errs() << "Latch has a conditional branch.\n";
            return 1;
        } else {
            errs() << "Latch has an unconditional branch.\n";
            return 2;
        }
    } else {
        errs() << "Latch terminator is not a BranchInst.\n";
        return 0;
    }
}

/*
Primo step della fusion, modifichiamo gli usi della induction variable nel body del loop 2
con quelli della induction variable del loop 1.
NOTA: usiamo solo nel caso di loops rotated.
*/
void update_iv(Loop * L0, Loop * L1, ScalarEvolution & SE) {
    PHINode * indVar0 = L0 -> getInductionVariable(SE);
    PHINode * indVar1 = L1 -> getInductionVariable(SE);

    if (!indVar0) {
        errs() << "Errore: induction variable 0 mancante\n";
    }
    if (!indVar1) {
        errs() << "Errore: induction variable 1 mancante\n";

    }
    outs() << "Ind var0 " << * indVar0 << "\n";
    outs() << "Ind var1 " << * indVar1 << "\n";

    // Debug: mostra gli usi
    for (auto * U: indVar1 -> users()) {
        outs() << "Uso di indVar1: " << * U << "\n";
    }

    indVar1 -> replaceAllUsesWith(indVar0);

    // Meglio spostare questo alla fine della trasformazione, non qui
    indVar1 -> eraseFromParent();
}

/*
Modifica tutte le phi contenute nel BB site, cambiandogli il predecessore previous_pred con new_pred
*/
void change_phi_incoming(BasicBlock * site, BasicBlock * previous_pred, BasicBlock * new_pred, std::string msg) {
    for (auto it = site -> begin(); it != site -> end();) {
        if (PHINode * PN = dyn_cast < PHINode > ( & * it)) {
            ++it;
            for (unsigned i = 0; i < PN -> getNumIncomingValues(); ++i) {
                if (PN -> getIncomingBlock(i) == previous_pred) {
                    PN -> setIncomingBlock(i, new_pred);
                    outs() << msg << * PN << "\n";
                }
            }
        } else {
            break;
        }
    }
}

/*
Sposta le phi dal BB from al BB to e gli mette come predecessore il BB pred
*/
void move_phi(BasicBlock * from, BasicBlock * to, BasicBlock * pred, std::string msg) {
    for (auto it = from -> begin(); it != from -> end();) {
        if (PHINode * PN = dyn_cast < PHINode > ( & * it)) {
            ++it;

            PN -> setIncomingBlock(0, pred);
            PN -> moveBefore( & * to -> getFirstInsertionPt());

            outs() << msg << * PN << "\n";
        } else {
            break;
        }
    }
}

/*
Funzione che si occupa di fondere loop di varie complessati, ovviamente dopo che hanno passato tutti
i controlli precedenti. 
Il workflow e' il seguente:

- Ricaviamo tutti i BB che ci interessanno e poi agiamo in maniera differente a seconda del tipo di loop
    + rotated -> aggiorniamo subito la IV e poi, visto che potrebbe esserci la guardia, la gestiamo se presente
                 Una volta che ci siamo ricondotti ad un caso "standard", procediamo con la fusion
    + non rotated -> 
                 */  
bool fuse_loop(Loop * L0, Loop * L1, ScalarEvolution & SE,
    AdjacencyStatus adj_status) {
    std::string msg = "";
    Function * F = L0 -> getHeader() -> getParent();

    dumpCFGToDotFile( * F, "dotfile/cfg_loop_NO_MOD.dot");

    // Ora ricaviamo tutti i blocchi che ci serviranno dopo per la modifica del cfg
    BasicBlock * BB_latch0 = L0 -> getLoopLatch();
    BasicBlock * BB_preheader0 = L0 -> getLoopPreheader();
    BasicBlock * BB_header0 = L0 -> getHeader();

    BasicBlock * BB_latch1 = L1 -> getLoopLatch();
    BasicBlock * BB_preheader1 = L1 -> getLoopPreheader();
    BasicBlock * BB_header1 = L1 -> getHeader();
    BasicBlock * BB_exit1 = L1 -> getExitBlock();

    outs() << "Preheader0: " << * BB_preheader0 << "\n";
    outs() << "Header0: " << * BB_header0 << "\n";
    outs() << "Latch0: " << * BB_latch0 << "\n";

    outs() << "Latch1: " << * BB_latch1 << "\n";

    int is_rotated = checkLatchBranchType(BB_latch0); // TO-DO: modificare ???

    outs() << "Is rotated: " << is_rotated << "\n";

    // Caso is_rotated
    if (is_rotated == 1) {
        update_iv(L0, L1, SE);

        // Se siamo nel caso di loop ruotati, dobbiamo distinguere i casi con guardia e senza
        if (adj_status == GuardedAdjacent) {
            // Questo e' il caso con guardia, che necessita di un trattamento speciale
            // che lo portera' ad una condizione simile a quella senza guardia e permettera'
            // dunque di eseguire la fusion successiva equivalente al caso senza guardia
            BasicBlock * BB_guard0 = L0 -> getLoopGuardBranch() -> getParent();
            BasicBlock * BB_guard1 = L1 -> getLoopGuardBranch() -> getParent();

            BranchInst * guard_term0 =
                dyn_cast < BranchInst > (BB_guard0 -> getTerminator());
            BranchInst * guard_term1 =
                dyn_cast < BranchInst > (BB_guard1 -> getTerminator());

            outs() << "Guard0 before: " << * guard_term0 << "\n";
            outs() << "Guard1: " << * guard_term1 << "\n";

            // Dobbiamo far si che la prima guardia punti, come successore fuori dal loop, a quello
            // a cui punta la guardia 2, visto che dopo verra' eliminata.
            BasicBlock * BB_exit = guard_term1 -> getSuccessor(1);
            guard_term0 -> setSuccessor(1, BB_exit);
            outs() << "Guard0 after: " << * guard_term0 << "\n";

            // Ovviamente le PHI che sono nel BB di uscita devono essere modificate, se presenti,
            // visto che non avranno piu' come uno dei predecessori la seconda guardia, ma la prima
            msg = "Modificato BB di incoming da guard1 a guard0 per la PHI in BB_exit: ";
            change_phi_incoming(BB_exit, BB_guard1, BB_guard0, msg);

            // Dobbiamo gestire anche le PHI che sono nella seconda guardia, perche' essa verra' eliminata
            // Visto che erano quelle all'uscita del primo loop, le mettiamo all'uscita di tutto
            msg = "Spostata PHI da BB_guard1 a BB_exit: ";
            move_phi(BB_guard1, BB_exit, BB_exit1, msg);

            // Ora puliamo il CFG dai blocchi non piu' utilizzati

            BasicBlock * BB_pred_guard1 = * pred_begin(BB_guard1);
            outs() << "BB prima di guard1: " << * BB_pred_guard1 << "\n";
            outs() << "BB guard1: " << * BB_guard1 << "\n";
            
            BranchInst * latch_term0 = dyn_cast < BranchInst > (BB_latch0 -> getTerminator());
            latch_term0 -> setSuccessor(1, guard_term1 -> getSuccessor(0));

            BB_guard1 -> dropAllReferences();
            BB_pred_guard1 -> dropAllReferences();

            BB_guard1 -> eraseFromParent();
            BB_pred_guard1 -> eraseFromParent();
        }

        // In ogni caso (guarded o meno), ora entriamo nel merito della trasformazione
        
        // Essendo che il corpo puo' essere complesso e formato da piu' blocchi, ci prendiamo
        // l'inizio e la fine dei due body (nota: potrebbero coincidere)
        BasicBlock * BB_body_start0 = L0 -> getHeader();
        BasicBlock * BB_body_end0 = * pred_begin(BB_latch0);

        BasicBlock * BB_body_start1 = L1 -> getHeader();
        BasicBlock * BB_body_end1 = * pred_begin(BB_latch1);

        // Modifica la terminazione del body_end0 per puntare a body_start1 anziche a latch0
        BranchInst * body_term0 = dyn_cast < BranchInst > (BB_body_end0 -> getTerminator());
        outs() << "BB terminator body_end0: " << * body_term0 << "\n";
        body_term0 -> setSuccessor(0, BB_body_start1);
        outs() << "Modificato il branch incondizionato di BB_body_end0: ora punta a "
        "BB_body_start1.\n";

        // Modifica latch1 per farlo puntare a BB_body_start0
        BranchInst * latch_term1 = dyn_cast < BranchInst > (BB_latch1 -> getTerminator());
        latch_term1 -> setSuccessor(0, BB_body_start0);
        outs() << "Modificato il branch incondizionato di BB_latch1: ora punta a "
        "BB_body_start0.\n";

        // Ora bisogna gestire le phi, che devono cambiare
        // Ci occupiamo prima di quelle nel secondo body
        // Le phi all'inizio del body del secondo loop devono essere spostate
        // all'inzio del body del primo loop.
        // Bisogna anche cambiare un predecessore, perche' il primo predecessore non e' 
        // piu' il secondo preheader, ma il primo.
        msg = "Spostata PHI da BB_body_start1 a BB_body_start0: ";
        move_phi(BB_body_start1, BB_body_start0, BB_preheader0, msg);

        // Ora ci occupiamo di quelle all'inzio del primo body, il cui predecessore deve
        // cambiare
        // Invertiamo il predecessore, dove prima era il BB_latch0 (che ora non
        // e' piu' un blocco sensato nel CFG) con il BB_latch1
        msg = "Modificata PHI da latch0 a latch1: ";
        change_phi_incoming(BB_body_start0, BB_latch0, BB_latch1, msg);

        outs() << "Latch0 : " << * BB_latch0 << "\n";
        outs() << "Preheader1 : " << * BB_preheader1 << "\n";

        // Ora puliamo il CFG dai blocchi non piu' utilizzati
        BB_latch0 -> dropAllReferences();
        BB_latch0 -> eraseFromParent();

        BB_preheader1 -> dropAllReferences();
        BB_preheader1 -> eraseFromParent();

    }

    // Caso in cui non e' rotated
    else if (is_rotated == 2) {
        // Il latch0 non deve piu' semplicemente tornare indietro, ma andare all'inizio del secondo body
        BranchInst * body_term0 = dyn_cast < BranchInst > (BB_latch0 -> getTerminator());
        body_term0 -> setSuccessor(0, BB_header1 -> getTerminator() -> getSuccessor(0));

        BranchInst * body_term1 = dyn_cast < BranchInst > (BB_latch1 -> getTerminator());
        body_term1 -> setSuccessor(0, BB_header0);

        BranchInst * header_term0 =
            dyn_cast < BranchInst > (BB_header0 -> getTerminator());
        header_term0 -> setSuccessor(1, BB_exit1);

        // Invertiamo il predecessore, dove prima era il BB_latch0 che ora non
        // sara' mai predecessore di BB_header0, con il BB_latch1
        msg = "Modificata PHI da latch0 a latch1: ";
        change_phi_incoming(BB_header0, BB_latch0, BB_latch1, msg);

        // Le phi dentro all'header del secondo loop devono essere spostate
        // all'header del primo loop, perche' e' diventato anche l'header del
        // secondo. Dunque bisogna, oltre che appunto spostarle, cambiare un
        // predecessore, perche' il primo predecessore non e' piu' il secondo
        // preheader, ma il primo.
        msg = "Spostata PHI da BB_header1 a BB_header0: ";
        move_phi(BB_header1, BB_header0, BB_preheader0, msg);

        BB_header1 -> dropAllReferences();
        BB_header1 -> eraseFromParent();

        BB_preheader1 -> dropAllReferences();
        BB_preheader1 -> eraseFromParent();

        outs() << "\n\n\n\n\n\n";
        F -> print(outs());
        outs() << "\n\n\n\n\n\n";
        dumpCFGToDotFile( * F, "dotfile/A_cfg_loop_MOD.dot");

    } else {
        return false;
    }

    dumpCFGToDotFile( * F, "dotfile/cfg_loop_MOD.dot");

    return true;
}
// =========================== Fine fusion ===============================

bool printCheckResult(bool condition,
    const std::string & message,
        int checkNumber) {
    if (condition) {
        outs() << "[✓] Check " << checkNumber << " superato: " << message << "\n";
        return true;
    } else {
        outs() << "[X] Check " << checkNumber << " non superato: " << message <<
            "\n";
        return false;
    }
}

/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task
e passi dell'algoritmo.
*/
bool analyze_loop(Function & F, FunctionAnalysisManager & AM,
    LoopInfo & LI, DominatorTree & DT,
    PostDominatorTree & PDT, ScalarEvolution & SE, DependenceInfo & DI) {

    bool modified_any = false;
    SmallVector < Loop * , 8 > Worklist;

    while (true) {
        bool modified = false;
        Worklist.clear();

        printSeparator("Ricalcolo dei loop");
        for (Loop * TopLevelLoop: LI) {
            for (Loop * L: depth_first(TopLevelLoop)) {
                if (L -> isInnermost() && L -> isLoopSimplifyForm()) {
                    Worklist.push_back(L);
                    outs() << "L: " << * (L -> getHeader()) << "\n";
                }
            }
        }

        printSeparator("Inizio iterazione ottimizzazione Loop Fusion");

        for (int i = Worklist.size() - 1; i >= 1; --i) {
            Loop * L0 = Worklist[i];
            Loop * L1 = Worklist[i - 1];

            printSeparator("Check 1: Adiacenza");
            AdjacencyStatus adj_status = are_adjacent(L0, L1);
            if (!printCheckResult(adj_status != NotAdjacent, "loop adiacenti", 1))
                continue;

            printSeparator("Check 3: Equivalenza di controllo di flusso");
            if (!printCheckResult(are_cf_equivalent(L0, L1, DT, PDT, adj_status),
                    "equivalenza CF", 3))
                continue;

            printSeparator("Check 2: Uguaglianza del numero di iterazioni");
            if (!printCheckResult(same_number_of_iterations(L0, L1, SE),
                    "numero di iterazioni uguale", 2))
                continue;

            printSeparator("Check 4: Controllo dipendenze negative");
            if (!printCheckResult(no_negative_dependencies(L0, L1, DI, SE),
                    "assenza dipendenze negative", 4))
                continue;

            printSeparator("Tutti i check superati, procedo alla fusion");

            fuse_loop(L0, L1, SE, adj_status);

            modified = true;
            modified_any = true;
            break;
        }

        if (!modified)
            break;
            
        // Invalida tutto il resto
        const auto & PA = PreservedAnalyses::none();
        AM.invalidate(F, PA);
    }

    printSeparator("Fine ottimizzazione globale Loop Fusion");
    return modified_any;
}