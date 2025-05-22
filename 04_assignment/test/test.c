// /* 
//     COPY-PASTE BASH:
//     clang -Xclang -disable-O0-optnone -O0 -S -emit-llvm test/src/es1_domina_uscite.c -o test/test.ll && \
//     opt -S -p mem2reg test/test.ll -o test/test.m2r.ll && \
//     opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli test/test.m2r.ll -S -o test/test.optimized.ll

// */


// // /*
// // Primo esempio: l'istruzione che definisce la variabile c è valida per la code motion nel pre-header, infatti:
// // - è loop indipendent siccome entrambi i suoi operandi sono definiti fuori dal loop
// // - il ciclo compie ameno una iterazione, garantendo cosi che la variabile c domini tutte le uscite del loop
// // */
// int foo1(int a, int b) {
//     int c;
//     // if(a > 3){
//     // for(int i = 0; i < a; i++){
//     //     c = a +3;
//     // }
//     // }
//     // else{
//     // for(int i = 0; i < a; i++){
//     //     a = a +3;
//     // }
//     // }
// // }
//     // a = 10;
//     // b = 10;
//     // if(b > 10){
//         while(b > 5){
//         c = 1+a;
//         a = b*3;
//         b--;
//         }
//         // for(int i = 0; i < a; i++){
//         //     b * 5;
//         // }
//     // }
//     // if(a > 0){
//         while(a > 0){
//             c = 1+a;
//             a = b*3;
//             b--;
//             }
//     // }
//     return 0;
// }

// void test(int n, int x){
//     int i = 0;
//     int j = 0;
//     if (5<n){
//     do {
//         j +=1;
//     } while(i<n);
//      }
//     // x +=1;
//     if (n>5){
//     do {
//         x +=1;
//     } while(i<n);
//     }
// }


// void test2(int n){
//     int x = 2;
//     int i = 0;
//     while(i < 50){
//         x++;
//         i++;
//     }
//     int j = 0;
//     while(j < 50){
//         x++;
//         j++;
//     }
// }

void testarray(int n){
    // int arr[2*n];
    // int arr1[2*n];
    int a1,a2,a3;
    int i = 0;  
    int j = 0;
    do{
        // a1 = arr[i];
        a1 = 3*i;
        i++;

    } while(i<n);
    i = 0;
    do{
        a2 = 3*i;
        // arr[i] = 2;
        i++;


    } while(i<n);
}