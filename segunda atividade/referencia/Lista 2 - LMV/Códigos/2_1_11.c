#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////
// código elaborado em ANSI C               //
// para compilar.: gcc 2_1_11.c -o a.out     //
// para execultar: ./a.out                  //
//                                          //
// AUTORES:                                 //
//      Lucas Felipe                        //
//      Marcus Adriano                      //
//      Vitor Hugo                          //
//////////////////////////////////////////////

int lehmerGenerator(int a, int x, int m){
    return (a * x) % m;
}

int prime(int a){
    int b = 0, i;
    for (i = 1; i <= a; i++)
    {
        if ((a % i) == 0)
            b++;
        if (b == 3) {
            return 0;
        }
    }
    return 1;
}

int verifyFullPeriod(int a, int m){
    int x = a;
    int p = 1;
    
    while (x != 1){
        p++;
        x = lehmerGenerator(a, x, m);
        if (p > m) {
            break;
        }
    }
    if (p == (m - 1)){
        return a;
    } else {
        return 0;
    }
}

int main(){
    int i, m, mult;
    int vector[] = { 17, 19, 23, 29, 31, 37, 41, 43, 47, 53 };

    for(i = 0; i < 10; i++) {
        for (mult = 1; mult < m; mult++){
            if (verifyFullPeriod(mult, vector[i]) != 0){
                printf("smallest multiplier of prime module %d is %d\n", vector[i], mult);
                break;
            }
        }
    }
    return 0;
}