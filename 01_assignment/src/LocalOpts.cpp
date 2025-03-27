//=============================================================================
// FILE:
//    LocalOpts.cpp
//
// DESCRIPTION:
//    Plugin LLVM che implementa tre passi di ottimizzazione locali.
//    Ogni pass effettua un'ottimizzazione sulle istruzioni.
// 
// Si rimanda al README.md della cartella 01_assignment per la descrizione su come usarlo e sui comandi da eseguire.
// Qui sotto si ha una descrizione dettagliata della "logica algoritmica" con cui abbiamo implementato i tre passi.
//
//=============================================================================

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/InstVisitor.h"

#include "StrRed.cpp"
#include "AlgIdRem.cpp"
#include "MultiInstOpt.cpp"

using namespace llvm;

namespace {

/* 
* Passo 1: Algebraic Identity Remove

  Questo passo, cosi' come il secondo, e' un passo di ottimizzazione che si concentra su singole istruzioni. 
  Proprio per questo, estendiamo InstVisitor per visitare le istruzioni e applicare le ottimizzazioni, 
  senza dover implementare noi il codice per iterare su tutti i basic block e le istruzioni.
  Nel file AlgIdRem.cpp, abbiamo implementato la funzione algebric_id_opt che si occupa di fare l'ottimizzazione e
  offre un interfaccia che, prendendo in input sia l'istruzione ma anche qual e' l'elemento neutro dell'operazione
  che stiamo ottimizzando riesce ad essere abbastanza generica.

*/

struct AlgebraicIdentityRem : PassInfoMixin<AlgebraicIdentityRem>,
                              InstVisitor<AlgebraicIdentityRem> {


  // Flag che usiamo per tenere traccia delle modifiche e per
  // fare il return della cosa giusta
  bool modified = false;

  void visitAdd(BinaryOperator &I) {
    outs() << "Visiting Add\n";
    if (algebric_id_opt(I, 0)) {
      modified = true;
    }
  }

  void visitMul(BinaryOperator &I) {
    outs() << "Visiting Mul\n";
    if (algebric_id_opt(I, 1)) {
      modified = true;
    }
  }

  void visitSub(BinaryOperator &I) {
    outs() << "Visiting Sub\n";
    if (algebric_id_opt(I, 0)) {
      modified = true;
    }
  }

  void visitSDiv(BinaryOperator &I) {
    outs() << "Visiting Div\n";
    if (algebric_id_opt(I, 1)) {
      modified = true;
    }
  }

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    outs() << "1. Algebraic Identity remove\n";

    modified = false; // Reset prima delle visite
    visit(F);

    // Ritorna ...none() se codice IR e' stato modificato, ...all() se codice IR
    // non e' stato modificato
    return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};


// **Passo 2: advanced Strenght Reduction**
struct StrengthReduction : PassInfoMixin<StrengthReduction>,
                           InstVisitor<StrengthReduction> {

  // Flag che usiamo per tenere traccia delle modifiche e per
  // fare il return della cosa giusta
  bool modified = false;

  void visitMul(BinaryOperator &I) {
    if (strenght_reduction_opt(I)) {
      modified = true;
    }
  }

  void visitSDiv(BinaryOperator &I) {
    if (strenght_reduction_opt(I)) {
      modified = true;
    }
  }

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    outs() << "2. StrengthReduction\n";

    modified = false;
    visit(F);

    return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

// **Passo 3: Multi Instruction Optimization**
struct MultiInstOpt : PassInfoMixin<MultiInstOpt> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    outs() << "3. MultiInstOpt\n";

    runOnFunction_MIO(F);

    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

}

// **Registrazione dei tre passi**
llvm::PassPluginLibraryInfo getLocalOptsPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LocalOpts", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "alg-id-rem") {
                    FPM.addPass(AlgebraicIdentityRem());
                    return true;
                  }
                  if (Name == "str-red") {
                    FPM.addPass(StrengthReduction());
                    return true;
                  }
                  if (Name == "multi-inst") {
                    FPM.addPass(MultiInstOpt());
                    return true;
                  }
                  return false;
                });
          }};
}

// Esportazione del plugin per LLVM
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLocalOptsPluginInfo();
}