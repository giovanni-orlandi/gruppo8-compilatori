
using namespace llvm;

bool isAddOrSub(unsigned op) {
    return op == Instruction::Add || op == Instruction::Sub;
}
bool isMulOrSDiv(unsigned op) {
    return op == Instruction::Mul || op == Instruction::SDiv;
}

/*
    Funzione principale dell'ottimizzazione. Il ragionamento e' questo: 
    abbiamo un'istruzione (I_main) che stiamo valutando che contiene al suo interno il riferimento ad una variabile che rappresenta
    un'altra istruzione (I_srot) che stiamo srotolando.
    Es: a = b + 2 e c = a + 1
    stiamo lavorando su c (I_main), srotolando a (I_srot), verificando che 1 e 2 siano effettivamente costanti.
    Se tutti i controlli vanno a buon fine, allora valutiamo una possibile sostituzione.
    Per permettere una valutazione finale semplice scegliamo di lavorare con gli offset, che sono le costanti. 
    In particolare lavoriamo a coppie, valutando le seguenti casistiche: 
    - I_main add e I_srot add 
    - I_main add e I_srot sub
    - I_main sub e I_srot add
    - I_main sub e I_srot sub
        Tutte queste casistiche vengono poi controllate con una semplice verifica: 
            offset_srot + offset_full == 0
        e l'unificazione di tutti questi casi in un unico controllo ci e' permesso grazie al fatto che abbiamo 
        invertito il segno dell'offset nel caso di sottrazione.
    - I_main mul e I_srot mul
    - I_main mul e I_srot sdiv
    - I_main sdiv e I_srot mul
    - I_main sdiv e I_srot sdiv
        Tutte queste casistiche vengono poi controllate con una semplice verifica: 
            offset_srot * offset_full == 1
        e l'unificazione di tutti questi casi in un unico controllo ci e' permesso grazie al fatto che abbiamo 
        invertito l'offset nel caso di divisione.

    NOTA: NON IMPLEMENTATO PER NIENTE CON:
        (2.) Istruzione da srotolare con due variabili, serve almeno una costante!!!
        (3.) Sub con costante al primo operando e quindi variabile al secondo
        (4.) Istruzione di partenza con due variabili, serve almeno una costante!!!!
*/
bool match_op(Instruction* I_main, Value* op_full, Instruction* I_srot) {
    
    unsigned main_opcode = I_main->getOpcode();

    // NOTA: qua rifacciamo il controllo anche su main_opcode per verificare non solo che
    // entrambe le istruzioni (sia quella che stiamo valutando e quella che stiamo srotolando)
    // siano una delle 4, ma anche che lo siano con la giusta accoppiata quindi
    // se I_main e' un Add, allora I_srot deve essere un Add o un Sub e cosi' via
    if ((!isAddOrSub(main_opcode) || !isAddOrSub(I_srot->getOpcode())) &&
        (!isMulOrSDiv(main_opcode) || !isMulOrSDiv(I_srot->getOpcode())))
        return false;

    // (4.) Qui contolliamo che l'operando dell'istruzione originale che non andiamo a srotolare sia una costante
    // Es: a = b + 1 e c = a + 1
    // stiamo lavorando su c, srotolando a, verifichiamo che 1 sia effettivamente una costante.
    ConstantInt* C_full = dyn_cast<ConstantInt>(op_full);
    if (!C_full) {
        outs()
            << "op_full non è una costante, non possiamo confrontare offset\n";
        return false;
    }
    float offset_full = static_cast<float>(C_full->getSExtValue());

    // Come fatto per l'istruzione srotolata, se l'istruzione originale che stiamo valutando e' una sottrazione invertiamo il segno dell'offset
    if (main_opcode == Instruction::Sub) offset_full = -offset_full;
    // Come fatto per l'istruzione srotolata, se l'istruzione originale che stiamo valutando e' una divisione invertiamo l'offset
    if (main_opcode == Instruction::SDiv) offset_full = 1.0 / offset_full;


    Value* I_srot_a = I_srot->getOperand(0);
    Value* I_srot_b = I_srot->getOperand(1);

    // Abbiamo fatto l'assunzione che uno dei due operandi della istruzione che stiamo srotolando sia per forza 
    // una costante e quindi adesso implementiamo tutta la logica per ricavare la costante (offset_srot) e la variabile (base_srot)
    Value* base_srot = nullptr;
    float offset_srot = 0;

    // Costante al secondo operando, posso lavorare su tutte e 4 le operazioni.
    if (ConstantInt* C = dyn_cast<ConstantInt>(I_srot_b)) {
        offset_srot = static_cast<float>(C->getSExtValue());

        // La variabile e' il primo operando
        base_srot = I_srot_a;

        // Se l'istruzione che stiamo srotolando e' una sottrazione, allora invertiamo il segno dell'offset perche' cosi' ci riconduciamo
        // al caso della somma (es. a = b - 2 = b + (-2)) e dopo possiamo semplicemente sommare gli offset.
        if (I_srot->getOpcode() == Instruction::Sub) 
            offset_srot = -offset_srot;

        // Se l'istruzione che stiamo srotolando e' una divisione, allora invertiamo l'offset perche' cosi' ci riconduciamo
        // al caso del prodotto (es. a = b / 2 = b * (1/2)) e dopo possiamo semplicemente moltiplicare gli offset.
        // QUESTO E' IL MOTIVO PER CUI USIAMO DEI FLOAT.
        if (I_srot->getOpcode() == Instruction::SDiv)
            offset_srot = 1.0 / offset_srot;
    }

    // Costante al primo operando (solo per add e mul) (3.)
    else if (I_srot->getOpcode() == Instruction::Add || I_srot->getOpcode() == Instruction::Mul) {
        if (ConstantInt* C = dyn_cast<ConstantInt>(I_srot_a)) {
            offset_srot = C->getSExtValue();
            base_srot = I_srot_b;
        }
    }

    // (2.) Questo controllo funziona perche' se nessuno dei due operandi e' una costante non siamo entrati in nessun ramo
    // dell'if precedente e quindi base_srot e' rimasto nullptr. 
    // Specifico perche' puo' confondere il fatto di controllare base_srot anche se la costante e' offset_srot.
    if (!base_srot) {
        outs() << "Pattern non riconosciuto: nessuna costante trovata\n";
        return false;
    }

    outs() << "Offset srot: " << offset_srot << "\n";
    outs() << "Offset full: " << offset_full << "\n";

    // Il cambio dell'offset fatto nei due casi speciali di divisione e sottrazione ci permette di rendere semplice il confronto
    // tra i due offset. Se i due offset sono opposti, allora possiamo sostituire l'istruzione originale con l'istruzione srotolata.
    // Ovviamente il concetto di offset opposti varia in base all'operazione che stiamo facendo.
    if (offset_srot + offset_full == 0 || offset_srot * offset_full == 1) {
        outs() << "Match trovato! Possiamo sostituire con base_srot: "
               << *base_srot << "\n";
        I_main->replaceAllUsesWith(base_srot);
        return true;
        /* NOTA:
        quello che stiamo facendo e'
        a = b + 1
        c = a - 1
        allora sostituiamo tutti i riferimenti a c con riferimenti a b
        */
    }
    outs() << "Pattern non compatibile o offset non opposti.\n";
    return false;
}


/*
    Funzione che fa partire la logica specifica per l'ottimizzazione.
    Ritorna true se l'ottimizzazione è possibile e viene applicata, cambiando i riferimenti e slinkando operazioni inutili 
    (WIP: ELIMINAZIONE), altrimenti false.
*/
bool multi_inst_opt(Instruction& I) {

    // Se non e' un istruzione Add, Sub, Mul o SDiv non possiamo fare nulla
    // Controllo ridondante ma utile per evitare di proseguire inutilmente
    if (!isAddOrSub(I.getOpcode()) && !isMulOrSDiv(I.getOpcode())) return false;

    Value* op1 = I.getOperand(0);
    Value* op2 = I.getOperand(1);
    Instruction* Iop1 = dyn_cast<Instruction>(op1);
    Instruction* Iop2 = dyn_cast<Instruction>(op2);

    outs() << "\nISTRUZIONE: " << I << "\n";

    if (Iop1) {
        outs() << "Srotolo prima\n";
        if (match_op(&I, op2, Iop1)) return true;
    }

    if (Iop2 && I.getOpcode() != Instruction::SDiv) {
        outs() << "Srotolo seconda\n";
        if (match_op(&I, op1, Iop2)) return true;
    }

    // if (Iop1 && Iop2) {
    //     outs() << "Srotolo entrambe\n";
    //     if (match_op(I.getOpcode(), Iop1, Iop2, true))
    //         return true;
    // }

    return false;
}

bool runOnBasicBlock(BasicBlock& B) {
    bool changed = false;
    for (auto it = B.begin(); it != B.end();) {
        Instruction& I = *it++;
        changed |= multi_inst_opt(I);
    }
    return changed;
}

bool runOnFunction_MIO(Function& F) {
    bool changed = false;

    for (auto& B : F) {
        changed |= runOnBasicBlock(B);
    }
    return changed;
}