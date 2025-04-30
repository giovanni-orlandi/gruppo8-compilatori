using namespace llvm;

// Variabili globali
std::vector<Instruction *> LI_instructions;
std::vector<Instruction *> CMLI_instructions;
Loop *L = nullptr;
SmallVector<BasicBlock *, 4> ExitBlocks;

// Funzione ausiliaria: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
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

      if (is_in_container(LI_instructions, op_inst)) //2.
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
      outs() << *L << "\n";
      // if(!is_in_container(ExitBlocks, BB)){
      continue;
      // }
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

// Verifica se un'istruzione soddisfa tutte le code motion condition e ritorna true in caso affermativo.
bool verify_cm_on_instr(FunctionAnalysisManager &AM, Instruction *I){
  int n = ExitBlocks.size();
  bool code_motion_condition = false;
  BasicBlock *BB = I->getParent();
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(*BB->getParent()); 
  DomTreeNode *LI_Node = DT.getNode(BB);
      int count = 0;
      for (auto *DTN : breadth_first(LI_Node)) {
        if (DTN->getBlock() == nullptr) continue;
          if(is_in_container(ExitBlocks, DTN->getBlock())){
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
          // Condizione azzurra: sto controllando che non sia usata dopo
          if(!L->contains(userBB) || isa<PHINode>(userInst)){ 
          // if(!L->contains(userBB)){
            code_motion_condition = false;
            break;
          }
          else{
            code_motion_condition = true;
          }
      }
      }
    return code_motion_condition;

}

// Analisi dei loop
bool analyze_loop(FunctionAnalysisManager &AM, LoopInfo &LI) {
  for (Loop *TopLoop : LI) {
    std::vector<Loop *> stack;
    stack.push_back(TopLoop);

    while (!stack.empty()) {
      L = stack.back();
      stack.pop_back();

     if(L->isLoopSimplifyForm()){ 

      outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";

      // Resetta lista LI per ogni nuovo loop
      LI_instructions.clear();
      ExitBlocks.clear();
      CMLI_instructions.clear();

      // Trova i blocchi di uscita del loop
      L->getUniqueExitBlocks(ExitBlocks);

      // LI check
      int count = get_LI_instructions();
      outs() << "Sono state trovate " << count << " istruzioni LI.\n";
      
      // Code motion
      for (auto I: LI_instructions){
        bool code_motion_condition = verify_cm_on_instr(AM, I);

            if(code_motion_condition){
              outs() << "Posso spostare l'istruzione " << *I << " fuori dal loop\n";

              // TO-DO: sposta istruzione se le altre da cui dipendeva sono state spostate.
              // Ci basta guardare che siano nel prehader: NO! Si rompe il loop.

              // BasicBlock *loop_preheader = L->getLoopPreheader();

            }
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
