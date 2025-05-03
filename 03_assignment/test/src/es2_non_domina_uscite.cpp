/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es2_non_domina_uscite.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Secondo esempio: A differenza del primo esempio, in questo caso la variabile c (pur essendo LI) non domina tutte le uscite, infatti semplicemente guardando il cfg non
abbiamo la certezza che il ciclo compia almeno una iterazione, quindi non possiamo spostare la definizione di c nel pre-header.
*/
int foo2(int a, int b) {
    int c;
    for(int i = 0; i < 10; i++){
        c = 1 + b;  
    }
    int a1 = c + 2;
    return 0;
}