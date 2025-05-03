/* 
    COPY-PASTE BASH:
    clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es4_loop_anidati_1.c -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Quarto esempio: Nel caso di piu loop annidati questi vengono analizzati mouventosi da quelli piu esterni a quelli piu interni. Questo perchè la ottimizzazione
migliore è quella che ci permette di spostare la definizione di una variabile nel pre-header del loop piu esterno. Le istruzioni che non vengono spostate perchè non 
rispettano le condizioni di code motion riseptto al loop piu esterno, vengono analizzate rispetto al loop immediatamente più interno, e cosi via.
Prendendo la ottimizzazione di questo esempio, l'istruzione che definisce la variabile y non è valida per la code motion rispetto al loop piu esterno (siccome non LI per
la variabile a), ma lo è rispetto al loop piu interno.
*/
int foo4(int a, int b) {;
    while(1){
        if(a == 0){
            break;
        } else {
            while(1){
                int y = 1 + a;
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