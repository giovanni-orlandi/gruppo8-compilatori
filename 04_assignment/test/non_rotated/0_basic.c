#include <stdio.h>

void test(int n){
    int i = 0;
    int j = 0;
    int z = 0;
    int somma = 0;
    int prodotto = 1;
    int gugu = 0;

    while(i < n){
        i++;
        somma +=i;
    };

    while(j< n){
        j++;
    prodotto *= j;
    };

    // while(z < n){
    //     z++;
    //     gugu -= z;
    // };

    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
     printf("Gugu: %d\n", gugu);
}


void main(){
    test(4);
    return;
}