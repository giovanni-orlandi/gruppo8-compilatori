#include <stdio.h>

void test_arrays(int n){

    int i = 0;
    int a = 0;
    int arr1[2*n];

    for(i = 0; i < n; i++){
        arr1[i] = i;
    }   
    for(i = 0; i < n; i++){
        a += arr1[i+1];
    }   

    printf("Valore di a: %d\n", a);

}

void main(){
    test_arrays(4);
    return;
}