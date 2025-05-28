#include <stdio.h>

// void test(int n){
//     int i = 0;
//     int somma = 0;
//     int prodotto = 1;
//     while(i < n){
//         i++;
//         somma +=i;
//     };

//     i = 0;
//     while(i < n){
//         i++;

//     prodotto *= i;
//         // }
//     };
//     i = 0;
//     while(i < n){
//         i++;
//         somma+=i;
//     }

//     printf("Somma: %d\n", somma);
//     printf("Prodotto: %d\n", prodotto);
// }

int test(int n){
    int i = 0;
    int a = 0;
    int somma = 0;
    int b = 0;
    int prodotto = 1;
    int x,y,z;

    // if(n > 0){
    do {
        somma +=i;
        i++;
            
        if(somma > 0){
            a++;
        }
        else{
            a--;
        }

    } while(i < n);
    // }
    i = 0;

    // if(n > 0){

    do {
        i++;
        prodotto *= i;

        if(prodotto > 0){
            b++;
        }
        else{
            b--;
        }
    } while(i < n);
    // }
    // i = 0;
    // do {
    //     x +=i;
    //     i++;
            
    //     if(x > 0){
    //         a++;
    //     }
    //     else{
    //         a--;
    //     }

    // } while(i < n);

    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}

void main(){
    test(4);
}