/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/2ndPass/Foo.cpp -o test/2ndPass/Foo.ll && \
    opt -S -p mem2reg test/2ndPass/Foo.ll -o test/2ndPass/Foo.m2r.ll && \
    opt -load-pass-plugin ./build/libLocalOpts.so -passes=str-red  test/2ndPass/Foo.m2r.ll -S -o test/2ndPass/Foo.optimized.ll

    Questa combo di comandi fa costant folding automaticamente --> risolvere.
*/

int foo(int a, int b) {
    // Moltiplicazine con potenza di due (16)
    int mul1 = a * 16;
    int mul2 = 16 * b;

    // Moltiplicazione con potenza di 2 + 1 (17)
    int mul3 = mul1 * 17;
    int mul4 = 17 * mul2;

    // Moltiplicazione con potenza di 2 - 1 (15)
    int mul5 = mul3 * 15;
    int mul6 = 15 * mul4;

    // Divisione con potenza di 2 (16)
    int div1 = mul6 / 16;

    // I seguenti casi non vengono ottimizzati, ma sono qui per completezza
   
    // Moltiplicazione per numero non ottimizzabile
    int mul7 = mul1 * 44;
   
    // Divisione con costante a sinistra
    int div2 = 16 / mul5; 
    
    // Divisione con potenza di 2 + 1 (17)
    int div3 = div1 / 17;
    
    // Dicisione con potenza di 2 - 1 (15)
    int div4 = div3 / 15;

    // Costante potenza di due ma negativa
    int mul8 = -16 * a;
    int div5 = a/-16;

    return div2;
}
