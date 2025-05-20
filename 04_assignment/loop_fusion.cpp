
using namespace llvm;

Loop *L = nullptr;

// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}


void printSeparator(StringRef label="", unsigned width = 60) {
  outs().changeColor(raw_ostream::YELLOW, true);
  if (label.empty()) {
      outs() << std::string(width, '-') << "\n";
  } else {
      unsigned pad = (width > label.size()) ? (width - label.size()) / 2 : 0;
      outs() << std::string(pad, '-') << label << std::string(pad, '-') << "\n";
  }
  outs().resetColor();
}

bool AreEquivalentComparisons(Value* expr0, Value* expr1) {
  ICmpInst* cmp1 = dyn_cast<ICmpInst>(expr0);
  ICmpInst* cmp2 = dyn_cast<ICmpInst>(expr1);
  // Check that both are comparisons
  if (!cmp1 || !cmp2) {

    // BranchInst* b0 = dyn_cast<BranchInst>(expr0);
    // BranchInst* b1 = dyn_cast<BranchInst>(expr1);
    // if (b0 || b1){
    //   Value* expr0 = b0->getCondition();
    //   Value* expr1 = b1->getCondition();
    //   outs() << "QUA\n";
    //   if (AreEquivalentComparisons(expr0, expr1)){
    //     return true;
    //   }
    // }
    return false;
  }
  // Types must match
  if (cmp1->getOperand(0)->getType() != cmp2->getOperand(0)->getType())
      return false;

  // Normalize first: get opcode, operands
  ICmpInst::Predicate pred1 = cmp1->getPredicate();
  Value* lhs1 = cmp1->getOperand(0);
  Value* rhs1 = cmp1->getOperand(1);

  ICmpInst::Predicate pred2 = cmp2->getPredicate();
  Value* lhs2 = cmp2->getOperand(0);
  Value* rhs2 = cmp2->getOperand(1);

  // Check direct match
  if (pred1 == pred2 && lhs1 == lhs2 && rhs1 == rhs2)
      return true;

  // Check swapped equivalent (e.g., x < 0 == 0 > x)
  if (lhs1 == rhs2 && rhs1 == lhs2) {
      // Use LLVM's getSwappedPredicate to reverse direction
      auto swapped = ICmpInst::getSwappedPredicate(pred2);
      if (pred1 == swapped)
          return true;
  }

  return false;
}

bool clear_intermediate_bb(BasicBlock* bb){
  for (Instruction &I : *bb) {
    if (!(isa<ICmpInst>(&I) || isa<PHINode>(&I) || isa<BranchInst>(&I))) {
        return false; // c'è qualcosa di diverso
    }
}
return true;
}

/*
Controllo 1: adiacenza
*/
bool are_adjacent(Loop* L0, Loop* L1){
  bool L0_guarded = L0->isGuarded();
  bool L1_guarded = L1->isGuarded();

  
  printSeparator("CONTROLLO GUARDIE"); 
  outs() << "L0: " << L0_guarded << "\n";
  outs() << "L1: " << L1_guarded << "\n";
  
  // Caso in cui entrambi i loop sono guarded
  if (L0_guarded && L1_guarded){
    outs() << "L0 and L1 guarded\n";

    // Ricavo le istruzioni di guardia
    BranchInst* guard0 = L0->getLoopGuardBranch();
    BranchInst* guard1 = L1->getLoopGuardBranch();
    
    outs() << "Guard0 " << *guard0 << "\n";
    outs() << "Guard1 " << *guard1 << "\n";

    // Mi faccio ritornare l'entry bb del secondo loop (loop1)
    BasicBlock* entry1 = guard1->getParent();

    // BasicBlock* trueDest0 = guard0->getSuccessor(0);
    // BasicBlock* falseDest0 = guard0->getSuccessor(1);
    
    // BasicBlock* out_guard0 = nullptr;

    // Mi ricavo il basic block fuori dal loop 0 a cui punta la guard0
    BasicBlock* out_guard0 = guard0->getSuccessor(1);

    // bool is_out_first0 = false;

    // if (L0->contains(trueDest0)){
    //   out_guard0 = falseDest0;

    // }
    // else if(L0->contains(falseDest0)){
    //   out_guard0 = trueDest0;
    //   is_out_first0 = true;
    // }


    if(out_guard0 == entry1){
    printSeparator("EXIT DI GUARD0 FUORI DAL LOOP0 PUNTA ALL'ENTRY DEL LOOP1");
      if(!clear_intermediate_bb(out_guard0)){
        outs() << "Ci sono istruzioni in mezzo\n";
        return false;
      }
      outs() << "BB0: " << *out_guard0 << "\n";
      outs() << "BB1: " << *entry1 << "\n";
      // outs() << "Output block della guardia 0 e' l'entry block del loop 1\n";


      // Mi ricavo le due condizioni che controlla la guard
      Value* expr0 = guard0->getCondition();
      Value* expr1 = guard1->getCondition();

      outs() << "Condizione 0: " << *expr0 << "\n";
      outs() << "Condizione 1: " << *expr1 << "\n";

      bool same_expr = AreEquivalentComparisons(expr0,expr1);
      if(same_expr){
        outs() << "Le condizioni delle due guardie sono uguali\n";
      }
      else{
        outs() << "Le condizioni delle due guardie sono diverse\n";
        return false;
      }

      // Controllo condizione uguale

      // BasicBlock* trueDest1 = guard1->getSuccessor(0);
      // BasicBlock* falseDest1 = guard1->getSuccessor(1);
      
      // bool is_out_first1 = false;
      // if (L1->contains(trueDest1)){
        
      // }
      // if(L1->contains(falseDest1)){
        // is_out_first1 = true;
      // }
      // bool inverted = true;
      // if (is_out_first1 == is_out_first0){
          // inverted = false;
      // }
      return true;

    }
    return false;

  }

  else if(!L0_guarded && !L1_guarded){
    outs() << "L0 and L1 NOT guarded\n";
    BasicBlock* ExitL0 = L0->getExitBlock();
    BasicBlock* PreHeaderL1 = L1->getLoopPreheader();
    outs() << *ExitL0 << "\n";
    outs() << *PreHeaderL1 << "\n";
    if(clear_intermediate_bb(ExitL0)){
      return ExitL0 == PreHeaderL1;
    }
    return false;
  }
  return false;
}

bool are_cf_equivalent(Loop* L0, Loop* L1, DominatorTree& DT, PostDominatorTree& PDT){
  BasicBlock *B0 = L0->getHeader();
  BasicBlock *B1 = L1->getHeader();

  //Check sulla dominanza L0->L1
  bool L0_dom_L1 = false;
  DomTreeNode *LI_Node = DT.getNode(B0);
  for (auto *DTN : breadth_first(LI_Node)) {
    if (DTN->getBlock() == nullptr) continue;
    BasicBlock* curr_block = DTN->getBlock();
    if (curr_block == B1){
      L0_dom_L1 = true;
      break;
    }
  }
  bool L1_postdom_L0 = false;

  //Check sulla postdominanza L1->L0
  auto* LI1_Node = PDT.getNode(B1);
  for (auto *PDTN : breadth_first(LI1_Node)) {
    if (PDTN->getBlock() == nullptr) continue;
    BasicBlock* curr_block = PDTN->getBlock();
    if (curr_block == B0){
      L1_postdom_L0 = true;
      break;
    }
  }

  return L0_dom_L1 && L1_postdom_L0;

}

/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task e passi dell'algoritmo.
*/
bool analyze_loop(LoopInfo &LI, DominatorTree& DT, PostDominatorTree& PDT) {
  // outs() << "here2\n";
  bool modified = false;


  SmallVector<Loop *, 8> Worklist;
  for (Loop *TopLevelLoop : LI){
    printSeparator();
    outs() << "L: " << *(TopLevelLoop->getHeader()) << "\n";
    printSeparator();

    for (Loop *L : depth_first(TopLevelLoop)){
      if (L->isInnermost()){ 
        Worklist.push_back(L);
      }
    }
  }
  for(int i = Worklist.size() - 1; i >= 1; i--){
    Loop* L0 = Worklist[i];
    Loop* L1 = Worklist[i-1];  
    bool check1 = are_adjacent(L0, L1);
    if(check1){
      outs() << "Check 1 passato per i due loop L" << i << " e L" << i+1 << "\n"; 
      bool check3 = are_cf_equivalent(L0, L1, DT, PDT);
      if(check3){
        outs() << "Check 3 superato\n";
      }
      else{
        outs() << "Check 3 NON superato\n";
      }
    }
    else{
      outs() << "Check 1 non passato!\n";
    }
  }
  return modified;  // Restituisci false se la funzione non ha modificato IR
}

