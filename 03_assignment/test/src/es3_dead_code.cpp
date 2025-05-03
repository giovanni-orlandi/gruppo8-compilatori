/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es3_dead_code.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Terzo esempio: Riprendendo il secondo esempio notiamo che, rimuovendo gli usi di c dopo il ciclo, la variabile diventa valida per la code motion nel pre-header.
Infatti, una delle condizioni che ci permette di spostare una istruzione ettichettata come LI è che questa risulti dead nei BB che seguono al loop.
*/
int foo3(int a, int b) {
    int c;
    for(int i = 0; i < 10; i++){
        c = 1 + b;  
    }
    return 0;
}