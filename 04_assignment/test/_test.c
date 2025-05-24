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

void process_arrays(int n) {
    int i = 0;
    int sum = 0;
    int prod = 1;
    int square = 1;
    int count = 0;
    int a;

    // Primo ciclo: somma e prodotto dei multipli di 3
    do {
        a = 3 * i;
        sum += a;
        if( a <= 12 ){
            a = 4*i;
        }
        prod *= (a + 1); // evito 0 per non azzerare il prodotto
        i++;
    } while (i < n);

    // Reset variabili per secondo ciclo
    i = 0;
    // Secondo ciclo: conteggio e somma dei quadrati
    do {
        a = 3 * i;
        square += a * a;
        i++;
    } while (i < n);

    // Valori computati (in un contesto reale sarebbero usati o stampati)
    // printf("sum=%d, prod=%d, square=%d, count=%d\n", sum, prod, square, count);
}


// void process_arrays(int n) {
//     int i = 0;
//     int sum = 0;
//     int prod = 1;
//     int a;

//     // Primo ciclo: somma e prodotto dei multipli di 3h
//     while(i < n){
//         a = 3 * i;
//         sum += a;
//         // if(a > 10){
//         //     a += 2;
//         // }
//         prod *= (a + 1); // evito 0 per non azzerare il prodotto
//         i++;
//     }

//     // Reset variabili per secondo ciclo
//     i = 0;
//     int count = 0;
//     int square = 0;

//     // Secondo ciclo: conteggio e somma dei quadrati
//     while (i< n) {
//         a = 3 * i;
//         square += a * a;
//         count++;
//         i++;
//     } 

//     // Valori computati (in un contesto reale sarebbero usati o stampati)
//     // printf("sum=%d, prod=%d, square=%d, count=%d\n", sum, prod, square, count);
// }

void main(){
    process_arrays(4);
}