#include <cmath>

using namespace llvm;

bool strenght_reduction_opt(Instruction &I) {
    LLVMContext &Context = I.getContext();

    for (int i = 0; i < 2; ++i) {
        Value *op = I.getOperand(i);
        ConstantInt *C = dyn_cast<ConstantInt>(op);

        if (C && C->getZExtValue() != 0) {
            uint64_t val = C->getZExtValue();
            Value *nonConstOp = I.getOperand(1 - i);

            // n e' potenza esatta di 2
            if ((val & (val - 1)) == 0) {
                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val));
                Instruction *NewInst = nullptr;

                if (I.getOpcode() == Instruction::Mul) {
                    NewInst = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                } else if (I.getOpcode() == Instruction::SDiv && !i) {
                    NewInst = BinaryOperator::Create(Instruction::AShr, nonConstOp, Power);
                }

                if (NewInst) {
                    NewInst->insertAfter(&I);
                    I.replaceAllUsesWith(NewInst);
                    outs() << "Strength reduction applicata (potenza esatta 2): " << val << "\n";
                    return true;
                }
            }

            // n-1 e' potenza di 2
            else if ((val > 1) && ((val - 1) & (val - 2)) == 0) {
                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val - 1));
                if (I.getOpcode() == Instruction::Mul) {
                    Instruction *Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                    Shift->insertAfter(&I);
                    Instruction *Add = BinaryOperator::Create(Instruction::Add, Shift, nonConstOp);
                    Add->insertAfter(Shift);
                    I.replaceAllUsesWith(Add);
                    outs() << "Strength reduction applicata (2^n + 1): " << val << "\n";
                    return true;
                }
            }

            // n+1 e' potenza di 2
            else if (((val + 1) & val) == 0) {
                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val + 1));
                if (I.getOpcode() == Instruction::Mul) {
                    Instruction *Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                    Shift->insertAfter(&I);
                    Instruction *Sub = BinaryOperator::Create(Instruction::Sub, Shift, nonConstOp);
                    Sub->insertAfter(Shift);
                    I.replaceAllUsesWith(Sub);
                    outs() << "Strength reduction applicata (2^n - 1): " << val << "\n";
                    return true;
                }
            }
        }
    }

    return false;
}
