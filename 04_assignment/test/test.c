#include <stdio.h>

// void test(int n){
//     int i = 0;
//     int somma = 0;
//     int prodotto = 1;
//     do {
//         i+=2;
//         somma +=i;
//     } while(i < n);

//     i = 0;
//     do {
//         // if(i != 0){
//             prodotto *= i+3;
//         // }
//         i+=2;
//     } while(i < n);

//     printf("Somma: %d\n", somma);
//     printf("Prodotto: %d\n", prodotto);
// }

void test_arr(int n){
    int i = 0;
    int somma = 0;
    int prodotto = 1;
    int arr[2*n];
    do {
        // somma = arr[i];
        arr[i] = i;

        i++;
        somma +=i;
    } while(i < n);

    i = 0;
    do {
        // if(i != 0){s
            somma = arr[i+1];

        // arr[i] = i;
            prodotto *= i+3;
        // }
        i++;
    } while(i < n);

    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}

// int main(){
//     int n = 5;
//     test(n);
//     return 0;
// }
