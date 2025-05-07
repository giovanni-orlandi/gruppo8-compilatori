// void foo(int a, int b){
//     int x = 0;
//     while(true){
//         if(x < 10){
//             a = 2;
//         }
//         x = 3*b;
//         if(b == 0){
//             break;
//         }
//     }
//     return;
// }

int foo2(int a, int b){
    int z, x;
    while(1){
        if(a != 0){
            x = 5*b;
            if(b!=1){
               z = x +2;
            //    z = a +2;
               return z; 
            }
        }
        else if(a != 1){
            return x;
        }
    }
}