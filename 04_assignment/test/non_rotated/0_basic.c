#include <stdio.h>

void test(int n){
    int i = 0;
    int j = 0;
    int somma = 0;
    int prodotto = 1;

    while(i < n){
        i++;
        somma +=i;
    };

    while(j< n){
        j++;
    prodotto *= j;
    };

    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}


void main(){
    test(4);
    return;
}