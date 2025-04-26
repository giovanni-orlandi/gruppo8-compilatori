/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/test.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli  test/test.m2r.ll -S -o test/test.optimized.ll

*/

// int g(int a){
//     // Sottrazione con elemento neutro (0)
//     int sub1 = 0 - a;
//     int b = a - 0; // = a
//     return b;
// }


int foo() {
    int a = 2;
    int b = 3;
    for(int i = 0; i < a; i++){
        int a1 = a+b;
        for(int j = 0; j < b; i++){
            for(int q = 0; q < 100; q++){
                int a3 = 2;
            }
        }
        for(int z = 0; z < 100; z++){
            int a2 = b + 2;
        }
        
    }
    return a;
}
