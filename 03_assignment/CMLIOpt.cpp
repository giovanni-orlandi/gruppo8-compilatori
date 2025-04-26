#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/BreadthFirstIterator.h"

#include "loop_invariant.cpp"

using namespace llvm;


namespace {
 
struct CMLIOpt : PassInfoMixin<CMLIOpt> {
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)

  bool modified = false;

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {

    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    modified = analyze_loop(LI);

    return modified ? PreservedAnalyses::none() : PreservedAnalyses::all();
    
  }

  // Without isRequired returning true, this pass will be skipped for functions
  // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
  // all functions with optnone.
  static bool isRequired() { return true; }
};
} // namespace

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLoopOptsPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CMLIOpt", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "cmli") {
                    FPM.addPass(CMLIOpt());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize LoopOpts when added to the pass pipeline on the
// command line, i.e. via '-passes=local-opts'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLoopOptsPluginInfo();
}
