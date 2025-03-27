
using namespace llvm;

// Funzione di controllo utile
bool isAddOrSub(unsigned op) {
  return op == Instruction::Add || op == Instruction::Sub;
}

bool isMulOrSDiv(unsigned op) {
    return op == Instruction::Mul || op == Instruction::SDiv;
  }
/*  NON IMPLEMENTATO PER NIENTE CON :
(2.) Istruzione da srotolare con due variabili, serve almeno una costante!!!
(3.) Sub con costante al primo operando e quindi variabile al secondo
(4.) Istruzione di partenza con due variabili, serve almeno una costante!!!!
*/
bool match_op(Instruction* I_main, Value* I_full, Instruction* I_srot, bool entrambe = false) {
  unsigned main_opcode = I_main->getOpcode();

  if ((!isAddOrSub(main_opcode) || !isAddOrSub(I_srot->getOpcode())) && (!isMulOrSDiv(main_opcode) || !isMulOrSDiv(I_srot->getOpcode())))
      return false;

  Value* I_srot_a = I_srot->getOperand(0);
  Value* I_srot_b = I_srot->getOperand(1);

  // outs() << *I_full << " Srot op0: " << *I_srot_a << " Srot op1: " << *I_srot_b << "\n";


  Value* base_srot = nullptr;
  float offset_srot = 0;

  // Costante al secondo operando
  if (ConstantInt* C = dyn_cast<ConstantInt>(I_srot_b)) {
      offset_srot = static_cast<float>(C->getSExtValue());
      base_srot = I_srot_a;

      if (I_srot->getOpcode() == Instruction::Sub)
          offset_srot = -offset_srot;
     if(I_srot->getOpcode() == Instruction::SDiv)
          offset_srot = 1.0 / offset_srot;
  }

  // Costante al primo operando (solo per add  div) (3.)
  else if (I_srot->getOpcode() == Instruction::Add || I_srot->getOpcode() == Instruction::Mul) {
      if (ConstantInt* C = dyn_cast<ConstantInt>(I_srot_a)) {
          offset_srot = C->getSExtValue();
          base_srot = I_srot_b;
      }
  }

  // (2.)
  if (!base_srot) {
      outs() << "Pattern non riconosciuto: nessuna costante trovata\n";
      return false;
  }

  // outs() << "Base srotolata: " << *base_srot << ", offset: " << offset_srot << "\n";

  // (4.)
  ConstantInt* C_full = dyn_cast<ConstantInt>(I_full);
  if (!C_full) {
      outs() << "I_full non è una costante, non possiamo confrontare offset\n";
      return false;
  }

  float offset_full = static_cast<float>(C_full->getSExtValue());

  if(main_opcode == Instruction::Sub)
    offset_full = -offset_full;

if(main_opcode == Instruction::SDiv)
    offset_full = 1.0 / offset_full;
outs() << "Offset srot: " << offset_srot << "\n";
outs() << "Offset full: " << offset_full << "\n";

    if (offset_srot + offset_full == 0 || offset_srot * offset_full == 1) {
        outs() << "Match trovato! Possiamo sostituire con base_srot: " << *base_srot << "\n";
        I_main->replaceAllUsesWith(base_srot);
        return true;
        /* NOTA: 
        quello che stiamo facendo e'
        a = b + 1
        c = a - 1
        allora sostituiamo tutti i riferimenti a c con riferimenti a b
        */
    }
  outs() << "Pattern non compatibile o offset non opposti.\n";
  return false;
}



// Ottimizzazione locale
bool ottimizzazione(Instruction &I){
  Value* op1 = I.getOperand(0);
  Value* op2 = I.getOperand(1);
  Instruction* Iop1 = dyn_cast<Instruction>(op1);
  Instruction* Iop2 = dyn_cast<Instruction>(op2);

  outs() << "\nISTRUZIONE: " << I << "\n";
  if (Iop1) {
      outs() << "Srotolo prima\n";
      if (match_op(&I, op2, Iop1))
          return true;
  }

  if (Iop2) {
      outs() << "Srotolo seconda\n";
      if (match_op(&I, op1, Iop2))
          return true;
  }

  // if (Iop1 && Iop2) {
  //     outs() << "Srotolo entrambe\n";
  //     if (match_op(I.getOpcode(), Iop1, Iop2, true))
  //         return true;
  // }

  return false;
}

bool runOnBasicBlock(BasicBlock &B) {
  bool Changed = false;
  for (auto it = B.begin(); it != B.end(); ) {
      Instruction &I = *it++;
      if (isa<BinaryOperator>(&I)) {
          if (ottimizzazione(I)) {
              Changed = true;
          }
      }
  }
  return Changed;
}

// Impleme
bool multi_inst_opt(Function &F) {
  bool Transformed = false;

  for (auto &B : F) {
      if (runOnBasicBlock(B)) {
          Transformed = true;
      }
  }

  return Transformed;
}