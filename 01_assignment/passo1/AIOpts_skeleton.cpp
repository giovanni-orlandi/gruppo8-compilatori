using namespace llvm;

void algebric_id_opt(Instruction &I, int neu_el){
  //Ha senso scorrere gli operandi se la istruzione è binaria?
  /*
  for (auto *Iter = I.op_begin(); Iter != I.op_end(); ++Iter) {
    Value *operand = *Iter;
    if (ConstantInt *C = dyn_cast<ConstantInt>(operand)) {
      APInt Val = C->getValue();
      uint64_t IntVal = Val.getZExtValue(); 
      if(IntVal == neu_el){
        I.replaceAllUsesWith();
      }
    } 
  }
  */
  
  //Operazione binaria prendiamo solamente i due operandi SENZA il for.
  if(I.isBinaryOp()){
    Value *operand1 = I.getOperand(0);
    Value *operand2 = I.getOperand(1);
    //Questo bordello qua sotto è da rivedere
    //SE IL PRIMO OPERANDO E' UGUALE A NEU_EL POSSIAMO ELIMINARE LISTRUZIONE SOLAMENTE NEL CASO DI ADD E MUL (SUB E DIV NON SONO COMMUTATIVI).
    ConstantInt *C = dyn_cast<ConstantInt>(operand1);
    if (C && (I.getOpcode() == Instruction::Add || I.getOpcode() == Instruction::Mul)) {
      APInt Val = C->getValue();
      uint64_t IntVal = Val.getZExtValue(); 
      if(IntVal == neu_el){
        I.replaceAllUsesWith(operand2);
        I.eraseFromParent();
        outs() << "Eliminata istruzione\n";
        return;  // Esci subito, I non è più valido

      }
    } 
    if (ConstantInt *C = dyn_cast<ConstantInt>(operand2)) {
      APInt Val = C->getValue();
      uint64_t IntVal = Val.getZExtValue(); 
      if(IntVal == neu_el){
        I.replaceAllUsesWith(operand1);
        I.eraseFromParent();
        outs() << "Eliminata istruzione\n";
        return;
      }
    } 
  }
  
}

bool runOnBasicBlock(BasicBlock &B) {
  bool transformed=false;

  //For cambiato perche quello di prima esplodeva nel momento in caso di cancellazione di un'istruzione.
  //Incremento l'iteratore PRIMA di eseguire i controlli cosi in caso di eliminazione di un'istruzione non si va in errore.
  for (auto Iter = B.begin(); Iter != B.end();) {
    Instruction &I = *Iter;  
    ++Iter;

    uint opcode = I.getOpcode();

    switch (opcode)
    {
        case Instruction::Add:
            outs() << "Add\n";
            algebric_id_opt(I, 0);
            break;
        case Instruction::Sub:
            outs() << "Sub\n";
            algebric_id_opt(I, 0);
            break;
        case Instruction::Mul:
            outs() << "Mul\n";
            algebric_id_opt(I, 1);
            break;
        case Instruction::SDiv:
            outs() << "Div\n";
            algebric_id_opt(I, 1);
            break;
          }
  }
  return transformed;
}

bool runOnFunction(Function &F) {
  bool transformed = false;

  for (auto &B : F) {
    if (runOnBasicBlock(B)) {
      transformed = true;
    }
  }

  return transformed;
}