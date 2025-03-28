#include <cmath>

using namespace llvm;

bool strenght_reduction_opt(Instruction &I) {
    LLVMContext &Context = I.getContext();

    // Scorre gli operatori (solo due?)
    for (int i = 0; i < 2; i++) {
        Value *op = I.getOperand(i);
        ConstantInt *C = dyn_cast<ConstantInt>(op);

        if (C && C->getZExtValue() != 0) {
            int64_t val = C->getSExtValue(); // signed extension

            //altro operando (non costante)
            Value *nonConstOp = I.getOperand(1 - i);

            // n e' potenza esatta di 2
            if ((val & (val - 1)) == 0) {
                outs() << "Entrata 1" << "\n";

                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val));
                Instruction *NewInst = nullptr;
                if (I.getOpcode() == Instruction::Mul) {
                    NewInst = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                // Deve essere ua division e il secondo operando e una costante.
                } else if (I.getOpcode() == Instruction::SDiv && i) {
                    NewInst = BinaryOperator::Create(Instruction::AShr, nonConstOp, Power);
                }

                if (NewInst) {
                    outs() << "Strength reduction applicata (potenza esatta 2): " << val << "\n";
                    outs() << I << " => sostituito da => " << *NewInst << "\n";
                    NewInst->insertAfter(&I);
                    I.replaceAllUsesWith(NewInst);
                    I.eraseFromParent();
                    return true;
                }
            }

            // n-1 e' potenza di 2
            else if ((val > 1) && ((val - 1) & (val - 2)) == 0) {
                outs() << "Entrata 2" << "\n";

                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val - 1));
                if (I.getOpcode() == Instruction::Mul) {
                    Instruction *Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                    Shift->insertAfter(&I);
                    Instruction *Add = BinaryOperator::Create(Instruction::Add, Shift, nonConstOp);
                    Add->insertAfter(Shift);
                    outs() << "Strength reduction applicata (2^n + 1): " << val << "\n";
                    outs() << I << " => sostituito da => " << *Shift << " AND " << *Add  << "\n";
                    I.replaceAllUsesWith(Add);
                    I.eraseFromParent();
                    return true;
                }
            }

            // n+1 e' potenza di 2
            else if (((val + 1) & val) == 0) {
                outs() << "Entrata 3" << "\n";

                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val + 1));
                if (I.getOpcode() == Instruction::Mul) {
                    Instruction *Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                    Shift->insertAfter(&I);
                    Instruction *Sub = BinaryOperator::Create(Instruction::Sub, Shift, nonConstOp);
                    Sub->insertAfter(Shift);
                    outs() << "Strength reduction applicata (2^n - 1): " << val << "\n";
                    outs() << I << " => sostituito da => " << *Shift << " AND " << *Sub  << "\n";
                    I.replaceAllUsesWith(Sub);
                    I.eraseFromParent();
                    return true;
                }
            }

            else if (((-val) & ((-val) - 1)) == 0) {
                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(-val));
                Instruction *Shift = nullptr;
                // outs() << "Entrata 4" << "\n";
                // outs() << "Valore costante negativo: " << *Power << "\n";

                if (I.getOpcode() == Instruction::Mul) {
                    Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                // Deve essere ua division e il secondo operando e una costante.
                } else if (I.getOpcode() == Instruction::SDiv && i) {
                    Shift = BinaryOperator::Create(Instruction::AShr, nonConstOp, Power);
                }
                
                if(Shift) {
                    Instruction *Sub = BinaryOperator::Create(Instruction::Sub, ConstantInt::get(Type::getInt32Ty(Context), 0), Shift);
                    outs() << "Strength reduction applicata (potenza negata 2): " << val << "\n";
                    outs() << I << " => sostituito da => " << *Shift << " AND " << *Sub << "\n";
                    Shift->insertAfter(&I);
                    Sub->insertAfter(Shift);
                    I.replaceAllUsesWith(Sub);
                    I.eraseFromParent();
                    return true;
                }
            }
        }
    }

    return false;
}
