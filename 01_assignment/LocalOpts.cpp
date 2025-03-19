//=============================================================================
// FILE:
//    LocalOpts.cpp
//
// DESCRIPTION:
//    Visits all functions in a module and prints their names. Strictly
//    speaking, this is an analysis pass (i.e. //    the functions are not
//    modified). However, in order to keep things simple there's no 'print'
//    method here (every analysis pass should implement it).
//
// USAGE:
//    New PM
//      opt -load-pass-plugin=<path-to>libLocalOpts.so -passes="local-opts" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "LocalOpts_skeleton.cpp"

using namespace llvm;

//-----------------------------------------------------------------------------
// LocalOpts implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep
// everything in an anonymous namespace.
namespace {

// New PM implementation
struct LocalOpts : PassInfoMixin<LocalOpts> {
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
llvm::PassPluginLibraryInfo getLocalOptsPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LocalOpts", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "local-opts") {
                    FPM.addPass(LocalOpts());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize LocalOpts when added to the pass pipeline on the
// command line, i.e. via '-passes=local-opts'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLocalOptsPluginInfo();
}
