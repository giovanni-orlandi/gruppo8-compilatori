/* 
    COPY-PASTE BASH:
    clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es1_domina_uscite.c -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Primo esempio: l'istruzione che definisce la variabile c è valida per la code motion nel pre-header, infatti:
- è loop indipendent siccome entrambi i suoi operandi sono definiti fuori dal loop
- il ciclo compie ameno una iterazione, garantendo cosi che la variabile c domini tutte le uscite del loop
*/
int foo1(int a, int b) {
    int c;
    while(1){
        c = 1 + b;
        if(a == 0){
            break;
        }
        a--;    
    }
    while(1){
        c = 1 + b;
        if(a == 0){
            break;
        }
        a--;    
    }
    int a1 = c + 2;
    return 0;
}