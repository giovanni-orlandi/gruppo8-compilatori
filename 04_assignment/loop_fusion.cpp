#include "llvm/Support/GraphWriter.h"
namespace llvm {
template <>
struct DOTGraphTraits<const llvm::Function*> : public DefaultDOTGraphTraits {
  DOTGraphTraits(bool isSimple = false) : DefaultDOTGraphTraits(isSimple) {}

  static std::string getNodeLabel(const llvm::BasicBlock *Node, const llvm::Function *Graph) {
    std::string Label;
    raw_string_ostream OS(Label);

    // if (!Node->getName().empty())
    //   OS << Node->getName() << ":\l";
    // else
    //   OS << "<anon>:\l";

    for (const auto &Inst : *Node) {

      OS << Inst << "\n";
    }

    return OS.str();
  }
};
} // namespace llvm

//dot -Tpng dotfile/cfg_loop.dot -o dotfile/cfg_loop.png
void dumpCFGToDotFile(llvm::Function &F, const std::string &Filename) {
  std::error_code EC;
  llvm::raw_fd_ostream File(Filename, EC, llvm::sys::fs::OF_Text);

  if (EC) {
    llvm::outs() << "Errore nell'apertura del file " << Filename << ": " << EC.message() << "\n";
    return;
  }

  llvm::WriteGraph(File, (const llvm::Function *)&F);
  llvm::outs() << "CFG scritto su: " << Filename << "\n";
}





using namespace llvm;

enum AdjacencyStatus {
  NotAdjacent = 0,
  GuardedAdjacent = 1,
  UnguardedAdjacent = 2
};

Loop *L = nullptr;

// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}

// Utility: serve per stampare delle linee separatrici
void printSeparator(StringRef label="", unsigned width = 60) {
  outs().changeColor(raw_ostream::YELLOW, true);
  if (label.empty()) {
      outs() << std::string(width, '-') << "\n";
  } else {
      unsigned pad = (width > label.size()) ? (width - label.size()) / 2 : 0;
      outs() << std::string(pad, '-') << label << std::string(pad, '-') << "\n";
  }
  outs().resetColor();
}

/*
Funzione che usiamo nel check1 per controllare l'uguaglianza delle due
espressioni nel caso di due loop guarded
*/
bool AreEquivalentComparisons(Value* expr0, Value* expr1) {
  ICmpInst* cmp1 = dyn_cast<ICmpInst>(expr0);
  ICmpInst* cmp2 = dyn_cast<ICmpInst>(expr1);
  // Check that both are comparisons
  if (!cmp1 || !cmp2) {
    return false;
  }
  // Types must match
  if (cmp1->getOperand(0)->getType() != cmp2->getOperand(0)->getType())
      return false;

  // Normalize first: get opcode, operands
  ICmpInst::Predicate pred1 = cmp1->getPredicate();
  Value* lhs1 = cmp1->getOperand(0);
  Value* rhs1 = cmp1->getOperand(1);

  ICmpInst::Predicate pred2 = cmp2->getPredicate();
  Value* lhs2 = cmp2->getOperand(0);
  Value* rhs2 = cmp2->getOperand(1);

  // Check direct match
  if (pred1 == pred2 && lhs1 == lhs2 && rhs1 == rhs2)
      return true;

  // Check swapped equivalent (e.g., x < 0 == 0 > x)
  if (lhs1 == rhs2 && rhs1 == lhs2) {
      // Use LLVM's getSwappedPredicate to reverse direction
      auto swapped = ICmpInst::getSwappedPredicate(pred2);
      if (pred1 == swapped)
          return true;
  }

  return false;
}

/**
Funzione che controlla che, il blocco che collega i due loop non contenga in mezzo altre istruzioni. 
Distinguiamo due casi: 
- Se stiamo parlando di due loop guarded dobbiamo avere esattamente 1 branch e 1 compare
- In caso di due loop non guarded dobbiamo avere esattamente 1 branch
 */
bool clear_intermediate_bb(BasicBlock* bb, bool is_guarded) {
  int branch_count = 0;
  int icmp_count = 0;

  for (Instruction &I : *bb) {
    if (isa<BranchInst>(I)) {
      branch_count++;
    } else if (isa<ICmpInst>(I)) {
      icmp_count++;
    } else{
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
Ritorna 0 se non sono adiacenti, 1 se sono adiacenti caso guarded, 2 se sono adiacenti caso non guarded
*/
AdjacencyStatus are_adjacent(Loop* L0, Loop* L1) {
  bool L0_guarded = L0->isGuarded();
  bool L1_guarded = L1->isGuarded();

  outs() << "\tL0_guarded: " << L0_guarded << "\n";
  outs() << "\tL1_guarded: " << L1_guarded << "\n";

  // --- CASO 1: Entrambi guarded ---
  if (L0_guarded && L1_guarded) {
    outs() << "\t[✓] Entrambi i loop sono guarded\n";

    BranchInst* guard0 = L0->getLoopGuardBranch();
    BranchInst* guard1 = L1->getLoopGuardBranch();

    if (!guard0 || !guard1) {
      outs() << "\t[X] Una delle guardie è null\n";
      return NotAdjacent;
    }

    BasicBlock* entry1 = guard1->getParent();
    BasicBlock* out_guard0 = guard0->getSuccessor(1); // ipotizziamo true = dentro, false = fuori


    if (out_guard0 != entry1) {
      outs() << "\t[X] La guardia di L0 non punta all'entry di L1\n";
      return NotAdjacent;
    }
    outs() << "\t[✓] La guardia di L0 punta all'entry di L1\n";
    bool is_guarded = true;
    if (!clear_intermediate_bb(out_guard0, is_guarded)) {
      outs() << "\t[X] Il blocco intermedio non è pulito\n";
      return NotAdjacent;
    }

    Value* expr0 = guard0->getCondition();
    Value* expr1 = guard1->getCondition();

    outs() << "\tCondizione guard0: " << *expr0 << "\n";
    outs() << "\tCondizione guard1: " << *expr1 << "\n";

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

    BasicBlock* exitL0 = L0->getExitBlock();
    BasicBlock* preheaderL1 = L1->getLoopPreheader();

    if (!exitL0 || !preheaderL1) {
      outs() << "\t[X] Exit o preheader è null\n";
      return NotAdjacent;
    }

    outs() << "\tExit L0: " << exitL0->getName() << "\n";
    outs() << "\tPreheader L1: " << preheaderL1->getName() << "\n";

    bool is_guarded = false;
    if (exitL0 == preheaderL1 && clear_intermediate_bb(preheaderL1, is_guarded)) {
      return UnguardedAdjacent;
    }

    outs() << "\t[X] I blocchi non coincidono o contengono istruzioni non valide\n";
    return NotAdjacent;
  }

  // --- CASO 3: Uno guarded, l’altro no ---
  outs() << "\t[X] Un solo loop è guarded: caso non valido per adiacenza\n";
  return NotAdjacent;
}

/*
Check 3: cf equivalenza
Prima ricaviamo i due BB su cui verificare la condizione in questi due casi: 
- se stiamo facendo i controlli con due loop guarded allora le condizioni di dom e postdom le controllo
  su i BB che contengono le guard
- se siamo nel caso di due loop non guarded, le condizioni di dom e postdom le controllo sui Preheader
Successivamente, controlliamo che il blocco selezionato del loop0 domini il loop1 e viceversa per la postdominanza.
*/
bool are_cf_equivalent(Loop* L0, Loop* L1, DominatorTree& DT, PostDominatorTree& PDT, AdjacencyStatus status){
  BasicBlock *B0 = nullptr;
  BasicBlock *B1 = nullptr;
  
  if(status == UnguardedAdjacent){ 
    B0 = L0->getLoopPreheader();
    B1 = L1->getLoopPreheader();
  }
  else if(status == GuardedAdjacent){ // Caso in cui devo controllare se sono cf equivalenti e sono guarded
    B0 = L0->getLoopGuardBranch()->getParent();
    B1 = L1->getLoopGuardBranch()->getParent();
  }

  // Controllo per sicurezza
  if(!B0 || !B1) return false;

  //Check sulla dominanza L0->L1
  bool L0_dom_L1 = false;
  DomTreeNode *LI_Node = DT.getNode(B0);
  for (auto *DTN : breadth_first(LI_Node)) {
    if (DTN->getBlock() == nullptr) continue;
    BasicBlock* curr_block = DTN->getBlock();
    if (curr_block == B1){
      L0_dom_L1 = true;
      break;
    }
  }

  bool L1_postdom_L0 = false;
  //Check sulla postdominanza L1->L0
  auto* LI1_Node = PDT.getNode(B1);
  for (auto *PDTN : breadth_first(LI1_Node)) {
    if (PDTN->getBlock() == nullptr) continue;
    BasicBlock* curr_block = PDTN->getBlock();
    if (curr_block == B0){
      L1_postdom_L0 = true;
      break;
    }
  }
  return L0_dom_L1 && L1_postdom_L0;

}


/*
Check 2: WIP
*/
bool same_number_of_iterations(Loop* L0, Loop *L1, ScalarEvolution &SE){
  auto *TripCount0 = SE.getBackedgeTakenCount(L0);
  auto *TripCount1 = SE.getBackedgeTakenCount(L1);
  outs() << "\tTC0: " << *TripCount0 << "\n";
  outs() << "\tTC1: " << *TripCount1 << "\n";
  if(TripCount0 == TripCount1){
    return true;
  }
  return false;
}


bool check_neg_dep(std::vector<Instruction*> L0_instr, std::vector<Instruction*> L1_instr, DependenceInfo &DI, ScalarEvolution &SE, int direction){
  for (auto *I0 : L0_instr) {
    for (auto *I1 : L1_instr) {
      // if(I0->getOperand(0) == I1->getOperand(0)){
        std::unique_ptr<Dependence> dep = DI.depends(I0, I1, true);
        if(dep){
            outs() << "[X] Trovata possibile dipendenza tra " << *I0 << " e " << *I1 << "\n";

            // outs() << *I0 << "\n";
            // outs() << *I1 << "\n";

            // outs() << *I0->getOperand(1) << "\n";
            // outs() << *I1->getOperand(0) << "\n";

            GetElementPtrInst *ptr0 = dyn_cast<GetElementPtrInst>(I0->getOperand(1-direction));
            GetElementPtrInst *ptr1 = dyn_cast<GetElementPtrInst>(I1->getOperand(direction));
            outs() << "ptr0: " << *ptr0 << "\n... e ptr1: " << *ptr1 << "\n";

            auto DepOp0 = dyn_cast<Instruction>(ptr0->getOperand(1))->getOperand(0);
            auto DepOp1 = dyn_cast<Instruction>(ptr1->getOperand(1))->getOperand(0);

            outs() << "Operandi...\n\t\t" << *DepOp0 << "\n\t\t" << *DepOp1 << "\n";
            printSeparator();

            const SCEVAddRecExpr *Trip0 = dyn_cast<SCEVAddRecExpr>(SE.getSCEV(DepOp0));
            const SCEVAddRecExpr *Trip1 = dyn_cast<SCEVAddRecExpr>(SE.getSCEV(DepOp1));

            if (Trip0 && Trip1) {
                const SCEV *Start0 = Trip0->getStart();
                const SCEV *Start1 = Trip1->getStart();

                outs() << "Tripla 1: " << *Trip0 << "\n";
                outs() << "Tripla 2: " << *Trip1 << "\n";

                outs() << "Start 1: " << *Start0 << "\n";
                outs() << "Start 2: " << *Start1 << "\n";


                const SCEVConstant *StartConst0 = dyn_cast<SCEVConstant>(Start0);
                const SCEVConstant *StartConst1 = dyn_cast<SCEVConstant>(Start1);

                if (StartConst0 && StartConst1) {
                    const llvm::APInt &Val0 = StartConst0->getAPInt();
                    const llvm::APInt &Val1 = StartConst1->getAPInt();

                    if (Val0.slt(Val1)) {
                        outs() << "Start del secondo loop maggiore del primo\n";
                        return false;
                    }
                    else{
                      outs() << "Okay, start del secondo loop minore del secondo, controlliamo il passo...\n";
                      const SCEV *Increment0 = Trip0->getStepRecurrence(SE);
                      const SCEV *Increment1 = Trip1->getStepRecurrence(SE);
                      outs() << "Increment 1: " << *Increment0 << "\n";
                      outs() << "Increment 2: " << *Increment1 << "\n";
                      const SCEVConstant *IncrementConst0 = dyn_cast<SCEVConstant>(Increment0);
                      const SCEVConstant *IncrementConst1 = dyn_cast<SCEVConstant>(Increment1);
                      if (IncrementConst0 && IncrementConst1) {
                        const llvm::APInt &Val0 = IncrementConst0->getAPInt();
                        const llvm::APInt &Val1 = IncrementConst1->getAPInt();
                        // outs() << "val0 " << Val0 << "\n";
                        // outs() << "val1 " << Val1 << "\n";
                        if (Val0.slt(Val1)) {
                            outs() << "Increment del secondo loop maggiore del primo\n";
                            return false;
                        }
                        else{
                          outs() << "anche controllo su incremento passato\n";
                          return true;
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
        }
        else{
          outs() << "\t[✓] Nessuna dipendenza negativa tra " << *I0 << " e " << *I1 << "\n";
          return true;
        }

    }
  }
  return false;
}

/*
Check 4: Negative Depentencies
*/
bool no_negative_dependencies(Loop* L0, Loop *L1, DependenceInfo &DI, ScalarEvolution &SE){
  std::vector<Instruction*> L0_store_instructions;
  std::vector<Instruction*> L1_load_instructions;


  std::vector<Instruction*> L1_store_instructions;
  std::vector<Instruction*> L0_load_instructions;

  outs() << "\tL0 instructions:\n";
  for (BasicBlock *BB : L0->getBlocks()) {
    for (Instruction &I : *BB) {
      if(isa<StoreInst>(I)){
        // GetElementPtrInst *ptr = dyn_cast<GetElementPtrInst>(I.getOperand(1));
        L0_store_instructions.push_back(&I);
        outs()<< "Store: " << I << "\n";
      }
      if(isa<LoadInst>(I)){
        // GetElementPtrInst *ptr = dyn_cast<GetElementPtrInst>(I.getOperand(0));
        L0_load_instructions.push_back(&I);
        outs()<< "Load: " << I << "\n";      
      }
    }
  }

  outs() << "\tL1 instructions:\n";
  for (BasicBlock *BB : L1->getBlocks()) {
    for (Instruction &I : *BB) {
      if(isa<LoadInst>(I)){
        // GetElementPtrInst *ptr = dyn_cast<GetElementPtrInst>(I.getOperand(0));
        L1_load_instructions.push_back(&I);
        outs()<< "Load: " << I << "\n";
      }
      if(isa<StoreInst>(I)){
        // GetElementPtrInst *ptr = dyn_cast<GetElementPtrInst>(I.getOperand(1));
        L1_store_instructions.push_back(&I);
        outs()<< "Store: " << I << "\n";
      }
    }
  }

  outs() << "\tL0 store instructions: " << L0_store_instructions.size() << "\n";
  outs() << "\tL1 load instructions: " << L1_load_instructions.size() << "\n\n";

  outs() << "\tL0 load instructions: " << L0_load_instructions.size() << "\n";
  outs() << "\tL1 store instructions: " << L1_store_instructions.size() << "\n";

  outs() << "========= Fine individuazione load e store... ========\n\n";

  bool neg_dep_store0_load1 = true;
  if(L0_store_instructions.size() && L1_load_instructions.size()){
    neg_dep_store0_load1 = check_neg_dep(L0_store_instructions, L1_load_instructions, DI, SE, 0);
  }

  bool neg_dep_store1_load0 = true;
  if(L1_store_instructions.size() && L0_load_instructions.size()){
    neg_dep_store1_load0 = check_neg_dep(L0_load_instructions, L1_store_instructions, DI, SE, 1);
  }

  return neg_dep_store0_load1 && neg_dep_store1_load0;

}


int checkLatchBranchType(BasicBlock *Latch) {
  if (!Latch) {
      errs() << "Loop has no latch!\n";
      return 0;
  }

  Instruction *Term = Latch->getTerminator(); // Ultima istruzione del latch

  if (BranchInst *BI = dyn_cast<BranchInst>(Term)) {
      if (BI->isConditional()) {
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



bool fuse_loop(Loop* L0, Loop* L1){
  PHINode* indVar0 = L0->getCanonicalInductionVariable();
  PHINode* indVar1 = L1->getCanonicalInductionVariable();
  outs() << "Ind var0 " << *indVar0 << "\n";
  outs() << "Ind var1 " << *indVar1 << "\n";
  indVar1->replaceAllUsesWith(indVar0);
  indVar1->eraseFromParent();



  BasicBlock* BB_latch0 = L0->getLoopLatch();
  BasicBlock* BB_body0 = *pred_begin(BB_latch0);  // assumendo un solo predecessore
  
  dumpCFGToDotFile(*BB_latch0->getParent(), "./dotfile/cfg_loop_fusion_m.dot");

  BasicBlock* BB_latch1 = L1->getLoopLatch();
  BasicBlock* BB_body1 = *pred_begin(BB_latch1);  // assumendo un solo predecessore
  
  BasicBlock* BB_header0 = L0->getHeader();
  BasicBlock* BB_preheader1 = L1->getLoopPreheader();
  
  outs() << "Pre-header0: " << *L0->getLoopPreheader();
  outs() << "\nHeader0: " << *BB_header0 << "\n";
  outs() << "Latch0: " << *BB_latch0 << "\n";
  outs() << "Latch2: " << *BB_latch1 << "\n";
  
  int branch_latch_0 = checkLatchBranchType(BB_latch0);
  
  if (branch_latch_0 == 1) {
      // Modifica la terminazione del body0 per puntare a body1
      BranchInst *BodyTerm0 = dyn_cast<BranchInst>(BB_body0->getTerminator());
      outs() << "BB terminator body0: " << *BodyTerm0 << "\n";
      outs() << "BB body1: " << *BB_body1 << "\n";
      
      BodyTerm0->setSuccessor(0, BB_body1);
      outs() << "Modificato il branch incondizionato: ora punta a BB_body1.\n";
  
      // Modifica latch1 per farlo puntare a header0
      BranchInst *LatchTerm1 = dyn_cast<BranchInst>(BB_latch1->getTerminator());
      LatchTerm1->setSuccessor(0, BB_header0);


      for (auto it = BB_body1->begin(); it != BB_body1->end(); ++it) {
        if (PHINode *PN = dyn_cast<PHINode>(&*it)) {
            bool related = false;
            outs() << "AAAAAAAAAa\n";
            outs() << *PN << "\n";
    
            for (unsigned i = 0; i < PN->getNumIncomingValues(); ++i) {
                if (PN->getIncomingValue(i) == indVar0) {
                    related = true;
                    break;
                }
            }
    
            if (related) {
                outs() << "PHI associata a indVar0 trovata in BB_body1: " << *PN << "\n";
            }
    
        } else {
            break; // fine delle PHI
        }
    }
    

    for (Instruction &I : *BB_header0) {
      if (PHINode *PN = dyn_cast<PHINode>(&I)) {
          for (unsigned i = 0; i < PN->getNumIncomingValues(); ++i) {
              if (PN->getIncomingBlock(i) == BB_latch0) {
                  PN->setIncomingBlock(i, BB_latch1);
                  outs() << "Modificata PHI da latch0 a latch1: " << *PN << "\n";
              }
          }
      } else {
          break;
      }

  }
  outs() << "Latch 0 : " << *BB_latch0 << "\n";
  outs() << "Preheader1 : " << *BB_preheader1 << "\n";

  BB_latch0->dropAllReferences(); 
  BB_latch0->eraseFromParent();
  // outs() << "here2\n";


  BB_preheader1->dropAllReferences(); 
  BB_preheader1->eraseFromParent();
  Function *F = BB_header0->getParent();
  outs() << "\n\n\n";
  F->print(llvm::outs());
  }
  

  else if(branch_latch_0 == 2){
    int a = 0;
  }
  else{
    return false;
  }

  return false;
}

/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task e passi dell'algoritmo.
*/
bool analyze_loop(LoopInfo &LI, DominatorTree& DT, PostDominatorTree& PDT, ScalarEvolution &SE, DependenceInfo &DI) {
  
  bool modified = false;
  SmallVector<Loop *, 8> Worklist;

  printSeparator("Stampa dei loop");
  for (Loop *TopLevelLoop : LI) {
    for (Loop *L : depth_first(TopLevelLoop)) {
      if (L->isInnermost() && L->isLoopSimplifyForm()) {
        Worklist.push_back(L);
        outs() << "L: " << *(L->getHeader()) << "\n";
      }
    }
  }

  printSeparator("Inizio ottimizzazione Loop Fusion");

  for (int i = Worklist.size() - 1; i >= 1; i--) {
    Loop* L0 = Worklist[i];
    Loop* L1 = Worklist[i - 1];

    outs() << "Analisi della coppia L" << i << " e L" << (i - 1) << "\n";

    printSeparator("Check 1: Adiacenza");
    AdjacencyStatus adj_status = are_adjacent(L0, L1);

    if (adj_status != NotAdjacent) {
      outs() << "[✓] Check 1 superato: loop adiacenti\n";

      printSeparator("Check 3: Equivalenza di controllo di flusso");
      if (are_cf_equivalent(L0, L1, DT, PDT, adj_status)) {
        outs() << "[✓] Check 3 superato: equivalenza CF\n";

        printSeparator("Check 2: Uguaglianza del numero di iterazioni");
        if (same_number_of_iterations(L0, L1, SE)) {
          outs() << "[✓] Check 2 superato: numero di iterazioni uguale\n";
        
          printSeparator("Check 4: Controllo dipendenze negative");
          if(no_negative_dependencies(L0, L1, DI, SE)){
            outs() << "[✓] Check 4 superato\n";
            printSeparator("Tutti i check superati, procedo alla fusion");

            fuse_loop(L0, L1);
            modified = true;
          } else {
            outs() << "[X] Check 4 non superato\n";
          }

        } else {
          outs() << "[X] Check 2 non superato\n";
        }

      } else {
        outs() << "[X] Check 3 non superato\n";
      }

    } else {
      outs() << "[X] Check 1 non superato: loop non adiacenti\n";
    }
  }
  printSeparator("Fine ottimizzazione Loop Fusion");
  return modified;
}
