/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/test.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli  test/test.m2r.ll -S -o test/test.optimized.ll

*/


/*
Primo esempio: In questo esempio la istruzione che definisce la variabile c è valida per la code motion nel pre-header, infatti:
- la variabile c è loop indipendent siccome entrambi i suoi operandi sono definiti fuori dal loop
- il ciclo compie ameno una iterazione, garantendo cosi che la variabile c domini tutte le uscite del loop
*/
int foo1(int a, int b) {
    int c;
    while(true){
        c = 1 + b;
        if(a == 0){
            break;
        }
        a--;    
    }
    int a1 = c + 2;
    return 0;
}

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

/*
Quarto esempio: Nel caso di piu loop annidati questi vengono analizzati mouventosi da quelli piu esterni a quelli piu interni. Questo perchè la ottimizzazione
migliore è quella che ci permette di spostare la definizione di una variabile nel pre-header del loop piu esterno. Le istruzioni che non vengono spostate perchè non 
rispettano le condizioni di code motion riseptto al loop piu esterno, vengono analizzate rispetto al loop immediatamente più interno, e cosi via.
Prendendo la ottimizzazione di questo esempio, l'istruzione che definisce la variabile y non è valida per la code motion rispetto al loop piu esterno (siccome non LI per
la variabile a), ma lo è rispetto al loop piu interno.
*/
int foo4(int a, int b) {;
    while(true){
        if(a == 0){
            break;
        } else {
            while(true){
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

/*
Sesto esempio: Caso con molti loop anidati.
*/
int foo6(int i1, int i2, int i3, int i4) {
    while(true){
        if(i1 == 0){
            break;
        } else {
            while(true){
                int x1 = i1 + 1;
                if(i2 == 0){
                    break;
                } else {
                    while(true){
                        int x2 = i2 + 2;
                        if(i3 == 0){
                            break;
                        } else {
                            while(true){
                                int x3 = i3 + 3;
                                if(i4 == 0){
                                    break;
                                }
                                i4--;
                            }
                        }
                        i3--;
                    }
                }
                i2--;
            }
        }
        i1--;
    }
}