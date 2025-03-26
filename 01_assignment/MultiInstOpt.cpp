using namespace llvm;

bool ottimizzazione(Instruction &I){
    Value* op1 = I.getOperand(0);
    Value* op2 = I.getOperand(1);
    Instruction* Iop1 = dyn_cast<Instruction>(op1);
    Instruction* Iop2 = dyn_cast<Instruction>(op2);
    if(Iop1){
        outs()<<"Srotolo prima\n";
        
        if(false)
            return true;
    }
    if(Iop2){
        outs()<<"Srotolo seconda\n";
        if(false)
            return true;
    }

    if(Iop1 && Iop2){
        outs()<<"Srotolo entrambe\n";
        if(true){
            return true;
        }
    }

    return false;
}

bool runOnBasicBlock(BasicBlock &B) {

  // Ottieni il contesto una sola volta, che ci serve poi per generare Constant da usare come operandi di Shl
  LLVMContext &Context = B.getContext();  

  for (auto &I : B) {
    outs() << "Instruction: " << I << "\n"; 
    if (isa<BinaryOperator>(&I)) {
        ottimizzazione(I);
  }
  }
  

  return true;
}

bool multi_inst_opt(Function &F) {
  bool Transformed = false;

  for (auto &B : F) {
    if (runOnBasicBlock(B)) {
      Transformed = true;
    }
  }

  return Transformed;
}
