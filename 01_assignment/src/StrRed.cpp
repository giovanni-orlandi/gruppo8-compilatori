#include <cmath>

using namespace llvm;


/**
 Implementazione della seconda ottimizzazione (Strenght reduction avanzata). 
 Data un'istruzione, ne scorre gli operatori e applica le seguenti ottimizzazioni, se possibili, eliminando l'istruzione
 corrente dopo averla sostituita nei seguenti modi (x e' la varaibile e n la costante): 
 - Moltiplicazione: 
    - n potenza esatta di 2 -> y = x << log(n)
    - n - 1 potenza esatta di 2 -> y = x << log(n-1); y+=x;
    - n + 1 potenza esatta di 2 -> y = x << log(n+1); y-=x;
    - n potenza di 2 ma negativa -> y = x << log(n); y = -y;
 - Divisione: 
    rispetto alla moltiplicazione, essendo non commutativa, vale sono nei casi di potenza esatta e
    solo se la costante e' al secondo operando.
    - n potenza esatta di 2 -> y = x >> log(n)
    - n potenza di 2 ma negativa -> y = x >> log(n); y = -y;

 */
bool strenght_reduction_opt(Instruction &I) {
    LLVMContext &Context = I.getContext();

    // Scorre gli operatori
    for (int i = 0; i < 2; i++) {
        Value *op = I.getOperand(i);
        ConstantInt *C = dyn_cast<ConstantInt>(op);

        if (C && C->getZExtValue() != 0) {
            int64_t val = C->getSExtValue(); // signed extension

            //altro operando (non costante)
            Value *nonConstOp = I.getOperand(1 - i);

            // n e' potenza esatta di 2
            if ((val & (val - 1)) == 0) {

                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(val));
                Instruction *NewInst = nullptr;
                // La moltiplicazione e' commutativa, non guardiamo dove e' la costante
                if (I.getOpcode() == Instruction::Mul) {
                    NewInst = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                // Con una divisione, la costante deve essere al secondo operando.
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
            
            // Altro caso particolare: numero moltiplicato per una potenza esatta di 2 ma negativa.
            else if (((-val) & ((-val) - 1)) == 0) {
                auto *Power = ConstantInt::get(Type::getInt32Ty(Context), log2(-val));
                Instruction *Shift = nullptr;

                // La moltiplicazione e' commutativa, non guardiamo dove e' la costante
                if (I.getOpcode() == Instruction::Mul) {
                    Shift = BinaryOperator::Create(Instruction::Shl, nonConstOp, Power);
                // Con una divisione, la costante deve essere al secondo operando.
                } else if (I.getOpcode() == Instruction::SDiv && i) {
                    Shift = BinaryOperator::Create(Instruction::AShr, nonConstOp, Power);
                }
                
                if(Shift) {
                    Instruction *Sub = BinaryOperator::Create(Instruction::Sub, ConstantInt::get(Type::getInt32Ty(Context), 0), Shift);
                    outs() << "Strength reduction applicata (potenza esatta di 2 ma negativa): " << val << "\n";
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
