using namespace llvm;

/*
 * Ottimizzazione algebrica: eliminazione di operazioni con elementi neutri.
 *
 * Supporta le seguenti ottimizzazioni:
 * - Addizione con 0:      x + 0 => x e 0 + x => x
 * - Moltiplicazione con 1: x * 1 => x e 1 * x => x
 * - Sottrazione con 0:    x - 0 => x
 * - Divisione per 1:      x / 1 => x
 *
 * Nota: per operazioni non commutative (SUB, DIV), l'elemento neutro deve essere il secondo operando.
 *
 * Parametri:
 * - I: istruzione da analizzare
 * - neu_el: elemento neutro da confrontare (0 per +, -, 1 per *, /)
 *
 * Restituisce true se l'istruzione è stata eliminata, false altrimenti.
 */
bool algebric_id_opt(Instruction &I, int neu_el) {
    Value *op1 = I.getOperand(0);
    Value *op2 = I.getOperand(1);
    unsigned opcode = I.getOpcode();

    // Caso in cui il primo operando è una costante
    // NOTA: solo per ADD e MUL (commutative), possiamo sostituire l'istruzione con il secondo operando
    if (ConstantInt *C1 = dyn_cast<ConstantInt>(op1)) {
        if ((opcode == Instruction::Add || opcode == Instruction::Mul) &&
            C1->getZExtValue() == neu_el) {
            I.replaceAllUsesWith(op2);
            I.eraseFromParent();
            outs() << "Istruzione eliminata (commutativa, costante a sinistra)\n";
            return true;
        }
    }

    // Caso in cui il secondo operando è una costante
    // Se l'elemento neutro è a destra, possiamo sostituire l'istruzione con il primo operando (in tutte le operazioni)
    if (ConstantInt *C2 = dyn_cast<ConstantInt>(op2)) {
        if (C2->getZExtValue() == neu_el) {
            I.replaceAllUsesWith(op1);
            I.eraseFromParent();
            outs() << "Istruzione eliminata (costante a destra)\n";
            return true;
        }
    }

    return false;
}