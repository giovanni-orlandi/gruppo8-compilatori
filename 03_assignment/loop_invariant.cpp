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
// bool is_operand_invariant(std::vector<Instruction*>& LI_instructions, Loop *L, Value *op) {
//   if (Instruction *op_inst = dyn_cast<Instruction>(op)) {
//       bool OpInside = false;
//       if (L->contains(op_inst->getParent()))
//           OpInside = true;

//       if (is_in_vector(LI_instructions, op_inst))
//           OpInside = false;

//       return !OpInside;
//   }

//   // Se non è un'istruzione (tipo costante o argomento), è invariabile
//   return false;
// }

// // Dato un singolo Loop, ritorna una lista con tutte le istruzioni Loop-Invariant contenute nel loop
// std::vector<Instruction*> get_LI_inst(Loop *L) {

//   std::vector<Instruction*> LI_instructions;

//   // Visita in profondità partendo dall'header
//   for (auto *BB : depth_first(L->getHeader())) {
//       if (!L->contains(BB))
//           continue;

//       for (auto &I : *BB) {
//           if (isa<BinaryOperator>(&I)) {
//               auto *BO = cast<BinaryOperator>(&I);
//               auto op1 = BO->getOperand(0);
//               auto op2 = BO->getOperand(1);

//               // bool op1_is_invariant = is_operand_invariant(LI_instructions, L, op1);
//               // bool op2_is_invariant = is_operand_invariant(LI_instructions, L, op2);
//               bool Op1Inside = false;
//               bool Op2Inside = true;
//               if (Instruction *Op1Inst = dyn_cast<Instruction>(op1)) {
//                 if (L->contains(Op1Inst->getParent()))
//                   Op1Inside = true;
//                 if (std::find(LI_instructions.begin(), LI_instructions.end(), Op1Inst) != LI_instructions.end())
//                   {
//                   outs() << "1 " << Op1Inst << "\n";  
//                   Op1Inside = false;}
//               }

//               if (Instruction *Op2Inst = dyn_cast<Instruction>(op2)) {
//                   if (L->contains(Op2Inst->getParent()))
//                     Op2Inside = true;
//                   if (std::find(LI_instructions.begin(), LI_instructions.end(), Op2Inst) != LI_instructions.end())
//                     {
//                     Op2Inside = false;}
//               }

//               if (!Op1Inside && !Op2Inside) {
//                   outs() << "Istruzione " << I << " è LI\n";
//                   LI_instructions.push_back(&I);
//               }

//               // outs() << op1_is_invariant << " " << op2_is_invariant << "\n";
//               // if (op1_is_invariant && op2_is_invariant) {
//               //     outs() << "Istruzione " << I << " è loop-invariant\n";
//               //     LI_instructions.push_back(&I);
//               // }
//           }
//       }
//   }

//   return LI_instructions;
// }

// bool analyze_loop(LoopInfo &LI) {
//   for (Loop *TopLoop : LI) {
//       std::vector<Loop*> stack;
//       stack.push_back(TopLoop);

//       while (!stack.empty()) {
//           Loop *L = stack.back();
//           stack.pop_back();

//           outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";
//           std::vector<Instruction*> LI_instructions = get_LI_inst(L);

//           for (Loop *SubLoop : L->getSubLoops()) {
//               stack.push_back(SubLoop);
//           }
//       }
//   }
//   return false;
// }

bool analyze_loop(LoopInfo &LI) {

  for (Loop *TopLoop : LI) {
    std::vector<Loop *> stack;
    stack.push_back(TopLoop);

    while (!stack.empty()) {
        std::vector<Instruction *> LI_instructions;
        Loop *L = stack.back();
        stack.pop_back();

        outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";
        int count = 0;
        for(auto *BB : depth_first(L->getHeader())) {
          if (!L->contains(BB)) {
            //outs() << "Scartato Basic Block " << count++ << " perché non fa parte del loop\n";
            continue;
          }
            //outs() << "Visiting Basic Block " << count++ << "\n";
            for (auto &I : *BB) {
                //outs() << "Istruzione Nel loop "<< count++ <<": " << I << "\n";
                if(isa<BinaryOperator>(&I)) {
                    auto *BO = cast<BinaryOperator>(&I);
                    auto op1 = BO->getOperand(0);
                    auto op2 = BO->getOperand(1);

                    bool Op1Inside = false;
                    bool Op2Inside = false;


                    if (Instruction *Op1Inst = dyn_cast<Instruction>(op1)) {
                      if (L->contains(Op1Inst->getParent()))
                        Op1Inside = true;
                      if (is_in_vector(LI_instructions, Op1Inst))
                        {
                        Op1Inside = false;}
                    }

                    if (Instruction *Op2Inst = dyn_cast<Instruction>(op2)) {
                        if (L->contains(Op2Inst->getParent()))
                          Op2Inside = true;
                        if (is_in_vector(LI_instructions, Op2Inst))
                          {
                          Op2Inside = false;}
                    }

                    if (!Op1Inside && !Op2Inside) {
                      outs() << "Istruzione " << I << " è LI\n";
                      LI_instructions.push_back(&I);
                  }

            }
        }

        
    }

    for (Loop *SubLoop : L->getSubLoops()) {
      stack.push_back(SubLoop);
  }
  }
}

  return false;
}