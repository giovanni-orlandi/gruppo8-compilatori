/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/1stPass/Foo.cpp -o test/1stPass/Foo.ll && \
    opt -S -p mem2reg test/1stPass/Foo.ll -o test/1stPass/Foo.m2r.ll && \
    opt -load-pass-plugin ./build/libLocalOpts.so -passes=alg-id-rem  test/1stPass/Foo.m2r.ll -S -o test/1stPass/Foo.optimized.ll

*/

int g(int a){
    // Sottrazione con elemento neutro (0)
    int sub1 = 0 - a;
    int b = a - 0; // = a
    return b;
}


int foo(int a, int b) {
    // Somma con elemento neutro (0)
    int sum1 = 0 + b;    // = b
    int sum2 = a + 0;    // = a

    // Moltiplicazione con elemento neutro (1)
    int mul1 = 1 * sum2; // = sum2
    int mul2 = sum1 * 1; // = sum1

    int sub2 = g(mul2);


    // Divisione con elemento neutro (1)
    int div1 = 1 / sub2;  // 1 diviso qualcosa (attenzione a divisione per 0!)
    int div2 = sub2 / 1;  // qualcosa diviso 1 = se stesso

    return div2;
}
