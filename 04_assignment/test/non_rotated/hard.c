#include <stdio.h>

void test(int n){
    int i = 0;
    int j = 0;
    int b = 0;
    int a = 0;
    int somma = 0;
    int prodotto = 1;

    while(i < n){
        i++;
        somma +=i;

                if(somma > 0){
            a++;
        }
        else{
            a--;
        }
    };

    while(j< n){
        j++;

    prodotto *= j;
    
                if(prodotto > 0){
            b++;
        }
        else{
            b--;
        }
    };

    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("Somma: %d\n", somma);
    printf("Prodotto: %d\n", prodotto);
}

void main(){
    test(4);
    return;
}