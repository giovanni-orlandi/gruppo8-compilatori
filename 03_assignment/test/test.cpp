void foo(int a, int b){
    int x = 0;
    while(true){
        if(x < 10){
            a = 2;
        }
        x = 3*b;
        if(b == 0){
            break;
        }
    }
    return;
}