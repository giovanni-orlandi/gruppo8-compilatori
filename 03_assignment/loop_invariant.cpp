using namespace llvm;

// Variabili globali
std::vector<Instruction *> LI_instructions;
Loop *L = nullptr;
SmallVector<BasicBlock *, 4> ExitBlocks;

// Funzione ausiliaria: controlla se un elemento è nel vettore
bool is_in_vector(const std::vector<Instruction*>& vec, const Instruction* elem) {
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

bool is_in_small_vector(const SmallVector<BasicBlock *, 4>& vec, const BasicBlock* elem) {
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

/* 
Funzione ausiliaria: ci serve per controllare che l'operando di un'istruzione, che stiamo controllando se puo' essere
loop invariant, e' loop invariant. Ritorna true in uno dei seguenti due casi:
1. operando e' definito in un blocco fuori dal loop
2. operando e' definito da un'istruzione dentro il loop ma che e' gia' stata taggata come loop-invariant
*/ 

bool is_operand_invariant(Value *op) {
  if (Instruction *op_inst = dyn_cast<Instruction>(op)) {
  
    if (!L->contains(op_inst->getParent())) // 1. 
      return true;

      if (is_in_vector(LI_instructions, op_inst)) //2.
      return true;

    // Altrimenti, è dentro il loop e non ancora LI
    return false;
  }
  // Se è una costante o qualcosa che non è un'istruzione, è invariabile
  return true;
}

// Funzione principale: trova tutte le loop-invariant instructions
int get_LI_instructions() {
  if (!L) return 0;  
  int count = 0;

  for (auto *BB : depth_first(L->getHeader())) {
    if(!L->contains(BB)){
      if(!is_in_small_vector(ExitBlocks, BB)){
        continue;
      }
    }
    for (auto &I : *BB) {
      // outs() << "Istruzione: " << I << "\n";
      if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
        auto *op1 = BO->getOperand(0);
        auto *op2 = BO->getOperand(1);

        if (is_operand_invariant(op1) && is_operand_invariant(op2)) {
          // outs() << "Istruzione " << I << " è LI\n";
          LI_instructions.push_back(&I);
          count++;
        }
      }
    }
  }
  return count;
}

// Analisi dei loop
bool analyze_loop(FunctionAnalysisManager &AM, LoopInfo &LI) {
  for (Loop *TopLoop : LI) {
    std::vector<Loop *> stack;
    stack.push_back(TopLoop);

    while (!stack.empty()) {
      L = stack.back();
      stack.pop_back();

      outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";

      // Resetta lista LI per ogni nuovo loop
      LI_instructions.clear();
      ExitBlocks.clear();

      // Trova i blocchi di uscita del loop
      L->getUniqueExitBlocks(ExitBlocks);

      // LI check
      int count = get_LI_instructions();
      outs() << "Sono state trovate " << count << " istruzioni LI.\n";
      
      // Code motion
      
      int n = ExitBlocks.size();
      
      for (auto I: LI_instructions){
        bool code_motion_condition = false;
        BasicBlock *BB = I->getParent();
        DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(*BB->getParent()); 
        DomTreeNode *LI_Node = DT.getNode(BB);
            int count = 0;
            for (auto *DTN : breadth_first(LI_Node)) {
              if (DTN->getBlock() == nullptr) continue;
                if(is_in_small_vector(ExitBlocks, DTN->getBlock())){
                  outs() << "Istruzione " << *I << " domina l'uscita " << count << "\n";
                  count++;
                }
            }
            if (count == n){
              code_motion_condition = true;
            }
            else{
              for (Use &U : I->uses()) {
                User *user = U.getUser(); // User è una Instruction o altro che usa il valore I
                Instruction *userInst = dyn_cast<Instruction>(user);
                BasicBlock *userBB = userInst->getParent();
                if(!L->contains(userBB) || isa<PHINode>(userInst)){
                  code_motion_condition = false;
                  break;
                }
                else{
                  code_motion_condition = true;
                }
            }
            }

            if(code_motion_condition){
              outs() << "Posso spostare l'istruzione " << *I << " fuori dal loop\n";
            }
      }


      // Continua a visitare i loop figli
      for (Loop *SubLoop : L->getSubLoops()) {
        stack.push_back(SubLoop);
      }
    }
  }

  return false;  // Restituisci false se la funzione non ha modificato IR
}
