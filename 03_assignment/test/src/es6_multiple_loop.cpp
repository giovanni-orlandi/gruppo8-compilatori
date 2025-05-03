/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es6_multiple_loop.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

*/


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