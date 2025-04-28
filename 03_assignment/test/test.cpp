/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/test.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli  test/test.m2r.ll -S -o test/test.optimized.ll

*/



int foo(int a, int b) {
    int a1, a2, a3, a4;
    a3 = a;
    while (true){
        a1 = a+b;
        if(a2 > 0){
            a3 = a * b;
            break;
        }
        else{
            a2 = b + 2;
        }
    }
    a4 = a1 * 100;
    // a1 = 2;
    // for(int i = 0; i < a; i++){
    //     a1 = a+b;
    //     a4 = a3 + 3;
    // }
    // a3 = a * 100;
    // a2 = a1 * 100;
    return a;
}
