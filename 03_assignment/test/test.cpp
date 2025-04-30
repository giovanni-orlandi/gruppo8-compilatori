/* 
    COPY-PASTE BASH:
    clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/test.cpp -o test/test.ll && \
    opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
    opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli  test/test.m2r.ll -S -o test/test.optimized.ll

*/



int foo(int a, int b, int x, int y) {
    int a1, a2, a3, a4;
    a4 = 0;
//     // a3 = a;
//     // while (true){
//     //     a1 = a+b;
//     //     if(a2 > 0){
//     //         a3 = a * b;
//     //         break;
//     //     }
//     //     else{
//     //         a2 = b + 2;
//     //     }
//     // }
//     // a4 = a1 * 100;
//     // a1 = 2;
//     // a2 = 4;
int i = 0;

    while(true){
        i++;
        if(y < 10){
            if(b < 5){
                break;
            }
        }
        else{
            a1 = a+b;
            y = a1 / i;

            x = a1+310;
            a4 = a3 + 3;

        }
    }
    // for(int i = 0;i>50;i++){
        // a1 = a + b;
        // if(y < 10){
        //     a2 = b/5;
        // }
        // else{
        //     a1 = a+b;
        //     x = a1+310;
        //     a4 = a3 + 3;
        // }
    // }
    //  a1 = a2*4;
    // a = a1;
    return a4;
    // a = a1 * 4;
//     // // a2 = a1 * 100;
//     // return a;

//     // while (true){
//     //     a1 = a + b;
//     //     if(a1 > 0){
//     //         a2 = a1+b;
//     //         if(a2 > 0){
//     //             break;
//     //         }
//     //     }
//     //     else{
//     //         int a3 = a*b;
//     //     }
//     // }
}

// void foo(int a, int b, int c, int e, int f, int d){
//     for(int i = 0; i <5; i++){
//         a=b+c;
//         if(i==3){
//             e=3;
//         }
//         else{
//             e=5;
//         }
//         d=a+1;
//         f=e+2;
//     }
// }