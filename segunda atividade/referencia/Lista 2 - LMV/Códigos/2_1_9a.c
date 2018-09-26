#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////
// código elaborado em ANSI C               //
// para compilar.: gcc 2_1_9a.c -o a.out    //
// para execultar: ./a.out                  //
//                                          //
// AUTORES:                                 //
//      Lucas Felipe                        //
//      Marcus Adriano                      //
//      Vitor Hugo                          //
//////////////////////////////////////////////

long lehmerGenerator(long a, long x, long m){
    return (a * x) % m;
}

long verifyFullPeriod(long a, long m){
    long x = a;
    long p = 1;

    while (x != 1) {
        p++;
        x = lehmerGenerator(a, x, m);
    }
    
    if (p == (m - 1)){
        return a;
    } else {
        return 0;
    }
}

int main(){
    long i = 0;
    long m = 2147483647;
    long vector[] = {7, 16807, 252246292, 52958638, 447489615};
    
    for (i = 0; i < 5; i++){
        if (verifyFullPeriod(vector[i], m) != 0)
            printf("%ld is full-period multiplier relative to %ld\n", vector[i], m);
        else
            printf("%ld is not full-period multiplier relative to %ld\n", vector[i], m);
    }

    return 0;
}