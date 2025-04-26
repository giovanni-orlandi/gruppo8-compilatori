/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/test.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli  test/test.m2r.ll -S -o test/test.optimized.ll

*/



int foo() {
    int a = 2;
    int b = 3;
    int a1, a2, a3;
    for(int i = 0; i < a; i++){
        a1 = a+b;
        for(int j = 0; j < b; i++){
            for(int q = 0; q < 100; q++){
                a3 = a + 2;
            }
        }
        for(int z = 0; z < 100; z++){
            a2 = b + 2;
        }
        int a4 = a1 + 3;
    }
    return a;
}
