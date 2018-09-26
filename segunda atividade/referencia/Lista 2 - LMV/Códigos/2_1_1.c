#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////
// código elaborado em ANSI C               //
// para compilar.: gcc 2_1_1.c -o a.out     //
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
    int i, m = 127, seed, a = 2, mult;
    for (mult = 1; mult < m; mult++){
        if (verifyFullPeriod(mult, m) != 0)
            break;
    }
    printf("smallest multiplier is %d\n", mult);
    return 0;
}