#include <stdio.h>

int test(int n){
    int i = 0;
    int a = 0;
    int somma = 0;
    int b = 0;
    int prodotto = 1;
    int x,y,z;

    if(n > 0){
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
    }
    i = 0;

    if(n > 0){

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
    }
    
    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}

void main(){
    test(4);
    return;
}