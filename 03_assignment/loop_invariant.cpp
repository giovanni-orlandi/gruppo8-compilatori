using namespace llvm;

// Funzione ausiliaria: ci serve per controllare che un'istruzione e' dentro la lista delle istruzioni
// loop-invariant trovate 
bool is_in_vector(const std::vector<Instruction*>& vec, const Instruction* elem) {
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

/* 
Funzione ausiliaria: ci serve per controllare che l'operando di un'istruzione, che stiamo controllando se puo' essere
loop invariant, e' loop invariant. Ritorna true in uno dei seguenti due casi:
1. operando e' definito in un blocco fuori dal loop
2. operando e' definito da un'istruzione dentro il loop ma che e' gia' stata taggata come loop-invariant
*/ 
bool is_operand_invariant(const std::vector<Instruction*>& LI_instructions, const Loop *L, Value *op) {
  if (Instruction *op_inst = dyn_cast<Instruction>(op)) {
    outs() <<(L->contains(op_inst->getParent())) << " here\n";
      if (!(L->contains(op_inst->getParent()))) // 1.
          return true;
      if (is_in_vector(LI_instructions, op_inst)) // 2.
          return true;
  }
  return false;
}

// Dato un singolo Loop, ritorna una lista con tutte le istruzioni Loop-Invariant contenute nel loop
std::vector<Instruction*> get_LI_inst(Loop *L) {

  std::vector<Instruction*> LI_instructions;

  // Visita in profondità partendo dall'header
  for (auto *BB : depth_first(L->getHeader())) {
      if (!L->contains(BB))
          continue;

      for (auto &I : *BB) {
          if (isa<BinaryOperator>(&I)) {
              auto *BO = cast<BinaryOperator>(&I);
              auto *op1 = BO->getOperand(0);
              auto *op2 = BO->getOperand(1);

              bool op1_is_invariant = is_operand_invariant(LI_instructions, L, op1);
              bool op2_is_invariant = is_operand_invariant(LI_instructions, L, op2);

              outs() << op1_is_invariant << " " << op2_is_invariant << "\n";
              if (op1_is_invariant && op2_is_invariant) {
                  outs() << "Istruzione " << I << " è loop-invariant\n";
                  LI_instructions.push_back(&I);
              }
          }
      }
  }

  return LI_instructions;
}

bool analyze_loop(LoopInfo &LI) {
  for (Loop *TopLoop : LI) {
      std::vector<Loop*> stack;
      stack.push_back(TopLoop);

      while (!stack.empty()) {
          Loop *L = stack.back();
          stack.pop_back();

          outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";
          std::vector<Instruction*> LI_instructions = get_LI_inst(L);

          for (Loop *SubLoop : L->getSubLoops()) {
              stack.push_back(SubLoop);
          }
      }
  }
  return false;
}