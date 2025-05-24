using namespace llvm;

#include "llvm/Support/GraphWriter.h"

using namespace llvm;

template <>
struct DOTGraphTraits<const Function*> : public DefaultDOTGraphTraits {
  DOTGraphTraits(bool isSimple = false) : DefaultDOTGraphTraits(isSimple) {}

  static std::string getNodeLabel(const BasicBlock *Node, const Function *Graph) {
    std::string Label;
    raw_string_ostream OS(Label);

    for (const auto &Inst : *Node) {
      OS << Inst << "\n";
    }

    return OS.str();
  }
};

// Esempio di uso: dumpCFGToDotFile(F, "dotfile/cfg_loop.dot");
void dumpCFGToDotFile(Function &F, const std::string &Filename) {
  std::error_code EC;
  raw_fd_ostream File(Filename, EC, sys::fs::OF_Text);

  if (EC) {
    outs() << "Errore nell'apertura del file " << Filename << ": " << EC.message() << "\n";
    return;
  }

  WriteGraph(File, (const Function *)&F);
  outs() << "CFG scritto su: " << Filename << "\n";
}



// Utility: controlla se un elemento è nel vettore
template <typename Container, typename Element>
bool is_in_container(const Container& container, const Element& elem) {
    return std::find(container.begin(), container.end(), elem) != container.end();
}

// Utility: serve per stampare delle linee separatrici
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
