using namespace llvm;

bool algebric_id_opt(Instruction &I, int neu_el){  

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
        return true;  // Esci subito, I non è più valido

      }
    } 
    if (ConstantInt *C = dyn_cast<ConstantInt>(operand2)) {
      APInt Val = C->getValue();
      uint64_t IntVal = Val.getZExtValue(); 
      if(IntVal == neu_el){
        I.replaceAllUsesWith(operand1);
        I.eraseFromParent();
        outs() << "Eliminata istruzione\n";
        return true;
      }
    } 
  
  return false;
}