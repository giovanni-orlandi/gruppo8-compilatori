//=============================================================================
// FILE:
//    LocalOpts.cpp
//
// DESCRIPTION:
//    Plugin LLVM che implementa tre passi di ottimizzazione locali.
//    Ogni pass effettua un'analisi semplice sulle funzioni di un modulo.
//
// USAGE:
//    opt -load-pass-plugin=<path-to>/libLocalOpts.so
//    -passes="local-opts1,local-opts2,local-opts3" -disable-output
//    <input-llvm-file>
//
// License: MIT
//=============================================================================

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/InstVisitor.h"

#include "StrRed_skeleton.cpp"
#include "AlgIdRem_skeleton.cpp"

using namespace llvm;

namespace {

// **Pass 1: Algebraic Identity**
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


// **Secondo Passo: WIP**
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

// **Terzo Passo: WIP**
struct MultiInstOpt : PassInfoMixin<MultiInstOpt> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    outs() << "MultiInstOpt 3\n";
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

} // namespace

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

// **Esportazione del plugin per LLVM**
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLocalOptsPluginInfo();
}