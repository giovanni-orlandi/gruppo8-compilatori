using namespace llvm;

// Variabili globali
std::vector<Instruction *> LI_instructions;
std::vector<Instruction *> CMLI_instructions;
Loop *L = nullptr;
SmallVector<BasicBlock *, 4> ExitBlocks;

// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}


/* 
Dato un operando, controlla se e' invariant per il loop corrente (variabile globale L)
Ritorna true se:
1. operando e' definito in un blocco fuori dal loop
2. operando e' definito da un'istruzione dentro il loop ma che e' gia' stata taggata come loop-invariant (e' dentro vettore LI_instructions)
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
  // Se è una costante o qualcosa che non è un'istruzione, è invariant
  return true;
}

/*
Funzione che popola il vettore globale LI_instructions con le istruzioni LI, 
facendo una visita depth_first
*/
int populate_LI_instructions() {
  if (!L) return 0;  
  int count = 0;

  // Visita depth_first del CFG del loop, per mantenere l'ordine corretto e lavorare in maniera incrementale
  for (auto *BB : depth_first(L->getHeader())) {
    if(!L->contains(BB)){
      continue;
    }
    for (auto &I : *BB) {
      // Lavoriamo solo con operazioni binarie!
      if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
        auto *op1 = BO->getOperand(0);
        auto *op2 = BO->getOperand(1);
      // Un operazione e' LI se i suoi due operandi sono invariant
        if (is_operand_invariant(op1) && is_operand_invariant(op2)) {
          outs() << "Istruzione " << I << " è LI\n";
          LI_instructions.push_back(&I);
          count++;
        }
      }
    }
  }
  return count;
}

bool does_I_dominate_exit(FunctionAnalysisManager &AM, Instruction *I){
  int n = ExitBlocks.size();
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
  return count == n;

}

/*
RICORDA: non controlla solo che sia DCE ma anche che non sia una phi,
perche' spostare un'istruzione che dopo e' DCE ma che ha un uso dentro una phi
cambierebbe la semantica, visto che e' il caso in cui si potrebbe usare la variabile prima
di eseguire l'istruzione, proprio dentro il loop
es:
int foo(int a, int b, int c, int e, int f, int d){
  while(true){
    if(y < 10){
      break;
    }
    else{
      y = a*b;
    }
  }
  return 0;
}
non posso spostare y = a*b anche se e' DCE perche' appunto il loop usa il valore di y prima.
*/
bool is_dce_after_loop(Instruction *I){
  for (Use &U : I->uses()) {
    User *user = U.getUser(); // User è una Instruction o altro che usa il valore I
    Instruction *userInst = dyn_cast<Instruction>(user);
    BasicBlock *userBB = userInst->getParent();
    // Condizione azzurra: sto controllando che non sia usata dopo
    if(!L->contains(userBB) || isa<PHINode>(userInst)){ 
      return false;
    }
  }
  return true;
}

// Verifica se un'istruzione soddisfa tutte le code motion condition e ritorna true in caso affermativo.
bool verify_cm_on_instr(FunctionAnalysisManager &AM, Instruction *I){
  bool code_motion_condition = true;

  if(!does_I_dominate_exit(AM, I) && !is_dce_after_loop(I)){
      code_motion_condition = false;
  }
  return code_motion_condition;
}

void populate_CM_instructions(FunctionAnalysisManager &AM){
  for (auto I: LI_instructions){
    bool code_motion_condition = verify_cm_on_instr(AM, I);

      if(code_motion_condition){
          outs() << "Posso spostare l'istruzione " << *I << " fuori dal loop\n";
          CMLI_instructions.push_back(I);
      }
  }
}

void execute_motion(){
  BasicBlock* loop_preheader_BB = L->getLoopPreheader();
  Instruction* lp_terminator = loop_preheader_BB->getTerminator();
  for (auto &I : CMLI_instructions) {
    Value *op1 = I->getOperand(0);
    Value *op2 = I->getOperand(1);
  
    bool op1_outside = true;
    bool op2_outside = true;
  
    if (Instruction *opInst1 = dyn_cast<Instruction>(op1)) {
      op1_outside = !L->contains(opInst1->getParent());
    }
  
    if (Instruction *opInst2 = dyn_cast<Instruction>(op2)) {
      op2_outside = !L->contains(opInst2->getParent());
    }
  
    if (op1_outside && op2_outside) {
      // outs() << " " << *I << "\n";
      outs() << *lp_terminator << "\n";
      I->moveBefore(lp_terminator); //TO-DO studia/sostituisci
    }
  }
}

/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task e passi dell'algoritmo.
*/
bool analyze_loop(FunctionAnalysisManager &AM, LoopInfo &LI) {

  // Scorro tutti i loop di primo livello
  for (Loop *TopLoop : LI) {

    // Coda per ogni loop di primo livello, lo popoleremo con eventuali sub-loops
    std::vector<Loop *> stack;
    stack.push_back(TopLoop);

    while (!stack.empty()) {
      L = stack.back();
      stack.pop_back();

      // Verifichiamo che loop sia in forma naturale
     if(L->isLoopSimplifyForm()){ 

      outs() << "Trovato loop con profondità: " << L->getLoopDepth() << "\n";

      // Resetta liste globali per ogni nuovo loop
      LI_instructions.clear();
      ExitBlocks.clear();
      CMLI_instructions.clear();

      // Trova i blocchi di uscita del loop
      L->getUniqueExitBlocks(ExitBlocks);

      // Individuazione LI e popolazione vettore LI_instructions
      int count = populate_LI_instructions();
      outs() << "Sono state trovate " << count << " istruzioni LI.\n";
      
      // Code motion
      populate_CM_instructions(AM);

      // Compi lo spostamento su tutte quelle CMLI, ma controllando che anche gli operandi siano stati spostati
      execute_motion();
      
     }

      // Continua a visitare i loop figli
      for (Loop *SubLoop : L->getSubLoops()) {
        stack.push_back(SubLoop);
      }
    }
  }

  return false;  // Restituisci false se la funzione non ha modificato IR
}
