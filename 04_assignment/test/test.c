#include <stdio.h>

void test(int n){
    int i = 0;
    int somma = 0;
    int prodotto = 1;
    while(i < n){
        i++;
        somma +=i;
    };

    i = 0;
    while(i < n){
        i++;

    prodotto *= i;
        // }
    };
    i = 0;
    while(i < n){
        i++;
        somma+=i;
    }

    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}

// int test_arr(int n){
//     int i = 0;
//     int somma = 0;
//     int prodotto = 1;

//     if(n > 0){
//     do {
//         somma +=i;
//         i++;

//     } while(i < n);
//     }
//     i = 0;

//     if(n > 0){

//     do {
//         i++;

//             prodotto *= i;
//     } while(i < n);
//     }
    
    
//     // if(somma > 0){
//     //     a++;
//     // }
//     printf("Somma: %d\n", somma);
//     printf("Prodotto: %d\n", prodotto);
// }

void main(){
    test(4);
}