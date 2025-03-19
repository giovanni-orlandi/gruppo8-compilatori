//=============================================================================
// FILE:
//    AIOpts.cpp
//
// DESCRIPTION:
//    Visits all functions in a module and prints their names. Strictly
//    speaking, this is an analysis pass (i.e. //    the functions are not
//    modified). However, in order to keep things simple there's no 'print'
//    method here (every analysis pass should implement it).
//
// USAGE:
//    New PM
//      opt -load-pass-plugin=<path-to>libAIOpts.so -passes="ai-opts" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "AIOpts_skeleton.cpp"

using namespace llvm;

//-----------------------------------------------------------------------------
// AIOpts implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep
// everything in an anonymous namespace.
namespace {

// New PM implementation
struct AIOpts : PassInfoMixin<AIOpts> {
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {

    runOnFunction(F);

    return PreservedAnalyses::all();
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
llvm::PassPluginLibraryInfo getAIOptsPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "AIOpts", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "ai-opts") {
                    FPM.addPass(AIOpts());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize AIOpts when added to the pass pipeline on the
// command line, i.e. via '-passes=ai-opts'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getAIOptsPluginInfo();
}
