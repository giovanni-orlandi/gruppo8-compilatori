/* 
    COPY-PASTE BASH:
    clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es5_loop_anidati_2.c -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Quinto esempio: In questo caso invece la istruzione che definisce la variabile y è valida per la code motion rispetto al loop più esterno e quindi viene spostata nel 
suo pre-header. Ovviamente la variabile y non verrà ottimizzata risepetto al loop piu interno perche già ottimizzata rispetto al loop piu esterno.
*/
int foo5(int a, int b, int c) {
    while(true){
        if(a == 0){
            break;
        } else {
            while(true){
                int y = 1 + c;
                if(b == 0){
                    break;
                }
                b--;
            }
        }
        a--;    
    }
    return 0;
}
