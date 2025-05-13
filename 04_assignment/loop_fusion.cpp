using namespace llvm;

Loop *L = nullptr;

// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}


/*
Funzione da cui parte l'analisi, chiama le varie funzioni ausiliarie per i task e passi dell'algoritmo.
*/
bool analyze_loop(FunctionAnalysisManager &AM, LoopInfo &LI) {
  bool modified = false;


  SmallVector<Loop *, 8> Worklist;
  for (Loop *TopLevelLoop : LI){
    for (Loop *L : depth_first(TopLevelLoop)){
      if (L->isInnermost()){ 
      Worklist.push_back(L);
      }
    }
  }

  outs() << Worklist.size() << "\n";
  return modified;  // Restituisci false se la funzione non ha modificato IR
}
