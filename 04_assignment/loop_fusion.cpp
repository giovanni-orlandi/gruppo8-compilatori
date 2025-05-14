using namespace llvm;

Loop *L = nullptr;

// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}

/*
Controllo 1: adiacenza
*/
bool are_adjacent(Loop* L0, Loop* L1){
  outs() << "qua\n";
  bool L0_guarded = L0->isGuarded();
  outs() << "L0: " << L0_guarded << "\n";
  bool L1_guarded = L1->isGuarded();
  outs() << "L1: " << L1_guarded << "\n";
  
  if (L0_guarded && L1_guarded){
    outs() << "L0 and L1 guarded\n";

    BranchInst* guard0 = L0->getLoopGuardBranch();
    BranchInst* guard1 = L1->getLoopGuardBranch();
    
    outs() << "Guard0" << *guard0 << "\n";
    outs() << "Guard1" << *guard1 << "\n";

    BasicBlock* Entry1 = guard1->getParent();

    BasicBlock* trueDest0 = guard0->getSuccessor(0);
    BasicBlock* falseDest0 = guard0->getSuccessor(1);
    
    BasicBlock* out_guard0 = nullptr;

    bool is_out_first0 = false;

    if (L0->contains(trueDest0)){
      out_guard0 = falseDest0;

    }
    else if(L0->contains(falseDest0)){
      out_guard0 = trueDest0;
      is_out_first0 = true;
    }
    Value* expr0 = guard0->getCondition();
    Value* expr1 = guard1->getCondition();
    outs() << "Condizione 0: " << *expr0 << "\n";
    outs() << "Condizione 1: " << *expr1 << "\n";

    if(out_guard0 == Entry1){

      BasicBlock* trueDest1 = guard1->getSuccessor(0);
      BasicBlock* falseDest1 = guard1->getSuccessor(1);
      
      bool is_out_first1 = false;
      // if (L1->contains(trueDest1)){
        
      // }
      if(L1->contains(falseDest1)){
        is_out_first1 = true;
      }
      bool inverted = true;
      if (is_out_first1 == is_out_first0){
          inverted = false;
      }
      outs() << "here\n";





    }
    return false;

  }
  else if(!L0_guarded && !L1_guarded){
    outs() << "L0 and L1 NOT guarded\n";
    BasicBlock* ExitL0 = L0->getExitBlock();
    BasicBlock* PreHeaderL1 = L1->getLoopPreheader();
    outs() << *ExitL0 << "\n";
    outs() << *PreHeaderL1 << "\n";
    if (ExitL0 == PreHeaderL1){
      return true;
    }
    return false;
  }
  return false;
}


/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task e passi dell'algoritmo.
*/
bool analyze_loop(FunctionAnalysisManager &AM, LoopInfo &LI) {
  bool modified = false;


  SmallVector<Loop *, 8> Worklist;
  for (Loop *TopLevelLoop : LI){
    outs() << "L: " << *(TopLevelLoop->getHeader()) << "\n";

    for (Loop *L : depth_first(TopLevelLoop)){
      if (L->isInnermost()){ 
        Worklist.push_back(L);
      }
    }
  }
  for(int i = Worklist.size() - 1; i >= 1; i--){
    Loop* L0 = Worklist[i];
    Loop* L1 = Worklist[i-1];  
    bool res = are_adjacent(L0, L1);
    if(res){
      outs() << "Check 1 passato per i due loop L" << i << " e L" << i+1 << "\n"; 
    }
  }
  return modified;  // Restituisci false se la funzione non ha modificato IR
}
