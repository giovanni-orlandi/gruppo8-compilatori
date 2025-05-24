#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/ADT/BreadthFirstIterator.h"

#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/DependenceAnalysis.h"

#include "loop_fusion.cpp"

using namespace llvm;


// ----------------------------STAMPA GRAFO--------------------------------------------------
// #include "llvm/Support/GraphWriter.h"
// namespace llvm {
// template <>
// struct DOTGraphTraits<const llvm::Function*> : public DefaultDOTGraphTraits {
//   DOTGraphTraits(bool isSimple = false) : DefaultDOTGraphTraits(isSimple) {}

//   static std::string getNodeLabel(const llvm::BasicBlock *Node, const llvm::Function *Graph) {
//     std::string Label;
//     raw_string_ostream OS(Label);

//     // if (!Node->getName().empty())
//     //   OS << Node->getName() << ":\l";
//     // else
//     //   OS << "<anon>:\l";

//     for (const auto &Inst : *Node) {

//       OS << Inst << "\n";
//     }

//     return OS.str();
//   }
// };
// } // namespace llvm

// //dot -Tpng dotfile/cfg_loop.dot -o dotfile/cfg_loop.png
// void dumpCFGToDotFile(llvm::Function &F, const std::string &Filename) {
//   std::error_code EC;
//   llvm::raw_fd_ostream File(Filename, EC, llvm::sys::fs::OF_Text);

//   if (EC) {
//     llvm::outs() << "Errore nell'apertura del file " << Filename << ": " << EC.message() << "\n";
//     return;
//   }

//   llvm::WriteGraph(File, (const llvm::Function *)&F);
//   llvm::outs() << "CFG scritto su: " << Filename << "\n";
// }

//-----------------------------------------------------------------------------


namespace {
 
struct LFOpt : PassInfoMixin<LFOpt> {
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)

  bool modified = false;

  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);

    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    DependenceInfo &DI = AM.getResult<DependenceAnalysis>(F);

    dumpCFGToDotFile(F, "./dotfile/cfg_loop_fusion10.dot");

    modified = analyze_loop(LI, DT, PDT, SE, DI);


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
  return {LLVM_PLUGIN_API_VERSION, "LFOpt", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "loopfusion") {
                    FPM.addPass(LFOpt());
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
