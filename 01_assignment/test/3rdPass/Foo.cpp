/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/3rdPass/Foo.cpp -o test/3rdPass/Foo.ll && \
    opt -S -p mem2reg test/3rdPass/Foo.ll -o test/3rdPass/Foo.m2r.ll && \
    opt -load-pass-plugin ./build/libLocalOpts.so -passes=multi-inst  test/3rdPass/Foo.m2r.ll -S -o test/3rdPass/Foo.optimized.ll
*/

int foo(int a, int b) {
    int temp1 = a - 16;
    int temp2 = 16 * b;

    int temp3 = temp1 + 16; // a + 16 - 16 = a
    int temp4 = temp2 / 16; // (16 * b) / 16 = b

    // temp3 e temp 4 sostituite con a e b quindi non "srotolate"
    int temp5 = temp3 * 15;
    int temp6 = 15 * temp4;

    //Caso problematico.
    int temp7 = 15 / temp5; // sbagliato --> 15 / (15 * a) = 1/a != a 
    int temp8 = temp5 / 15; // corretto --> (15 * a) / 15 = a

    return temp8;
}

