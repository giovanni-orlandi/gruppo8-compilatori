#include <stdio.h>

int test(int n){
    int i = 0;
    int somma = 0;
    int prodotto = 1;
    int a = 0;

    do {
        somma +=i;
        i++;
    } while(i < n);
    i = 0;

    do {
        i++;
        prodotto *= i;

    } while(i < n);
    i = 0;
    do {
        i++;
        a -= i;

    } while(i < n);
    
    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
    printf("a: %d\n", a);
}

void main(){
    test(4);
    return;
}