using namespace llvm;

void algebric_id_opt(Instruction &I, int neu_el){
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

}

bool runOnBasicBlock(BasicBlock &B) {
  bool transformed=false;

  for (auto &I: B){
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