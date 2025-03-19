#include <cmath>

using namespace llvm;

// Primo passo solo di prova, poco significativo
void first_pass(Instruction &Inst1st) {
  // Manipolazione delle istruzioni
  // Creo istruzione di add facendo (pseudocode):
  //    (istruzione1.operandi)[0] + (istruzione1.operandi)[0]
  Instruction *NewInst = BinaryOperator::Create(
      Instruction::Add, Inst1st.getOperand(0), Inst1st.getOperand(0));

  // Inserisco la nuova istruzione dopo la prima
  NewInst->insertAfter(&Inst1st);

  // Si possono aggiornare le singole references separatamente?
  // Controlla la documentazione e prova a rispondere.
  // Direi di si, con un iteratore

  // Aggiorno tutti i riferimenti alla prima istruzione con la nuova istruzione
  Inst1st.replaceAllUsesWith(NewInst);
}

bool runOnBasicBlock(BasicBlock &B) {

  // Preleviamo le prime due istruzioni del BB
  Instruction &Inst1st = *B.begin();
  Instruction &Inst2nd = *(++B.begin());

  // L'indirizzo della prima istruzione deve essere uguale a quello del
  // primo operando della seconda istruzione (per costruzione dell'esempio)
  assert(&Inst1st == Inst2nd.getOperand(0));

  // // Stampa la prima istruzione
  // outs() << "PRIMA ISTRUZIONE: " << Inst1st << "\n";

  // // Stampa la prima istruzione come operando
  // outs() << "COME OPERANDO: ";
  // Inst1st.printAsOperand(outs(), false);
  // outs() << "\n";

  // // User-->Use-->Value
  // outs() << "I MIEI OPERANDI SONO:\n";
  // for (auto *Iter = Inst1st.op_begin(); Iter != Inst1st.op_end(); ++Iter) {
  //   Value *Operand = *Iter;

  //   if (Argument *Arg = dyn_cast<Argument>(Operand)) {
  //     outs() << "\t" << *Arg << ": SONO L'ARGOMENTO N. " << Arg->getArgNo()
  //      <<" DELLA FUNZIONE " << Arg->getParent()->getName()
  //            << "\n";
  //   }
  //   if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
  //     outs() << "\t" << *C << ": SONO UNA COSTANTE INTERA DI VALORE " <<
  //     C->getValue()
  //            << "\n";
  //   }
  // }

  // outs() << "LA LISTA DEI MIEI USERS:\n";
  // for (auto Iter = Inst1st.user_begin(); Iter != Inst1st.user_end(); ++Iter)
  // {
  //   outs() << "\t" << *(dyn_cast<Instruction>(*Iter)) << "\n";
  // }

  // outs() << "E DEI MIEI USI (CHE E' LA STESSA):\n";
  // for (auto Iter = Inst1st.use_begin(); Iter != Inst1st.use_end(); ++Iter) {
  //   outs() << "\t" << *(dyn_cast<Instruction>(Iter->getUser())) << "\n";
  // }

  // first_pass(Inst1st);

  // Ottieni il contesto una sola volta, che ci serve poi per generare Constant da usare come operandi di Shl
  LLVMContext &Context = B.getContext();  

  for (auto &I : B) {
      if (I.getOpcode() == Instruction::Mul) {  // Controlliamo se è una moltiplicazione
          outs() << I << "\n";

            for (auto *Iter = I.op_begin(); Iter != I.op_end(); ++Iter) {
            Value *Operand = *Iter;


            if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
              APInt Val = C->getValue();
              uint64_t IntVal = Val.getZExtValue();  // Converti in uint64_t (evita problemi con negativi)

              // Controlliamo se è una potenza di 2
              if ((IntVal & (IntVal - 1)) == 0 && IntVal != 0) {

                  ConstantInt *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(IntVal));

                  Instruction *NewInst = BinaryOperator::Create(
                      Instruction::Shl, I.getOperand(0), Power);

                  NewInst->insertAfter(&I);
                  I.replaceAllUsesWith(NewInst);
              }
            }
          }
      }
  }
  

  return true;
}

bool runOnFunction(Function &F) {
  bool Transformed = false;

  for (auto &B : F) {
    if (runOnBasicBlock(B)) {
      Transformed = true;
    }
  }

  return Transformed;
}
