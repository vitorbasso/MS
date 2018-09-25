#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////
// código elaborado em ANSI C               //
// para compilar.: gcc 2_2_11.c -o a.out    //
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

long pot(long a, long b) {
    long c = 1;        
    long i = 0;
    for(i = 0; i < b; i++) {
      c = c * a;  
    }
    return c;
}

long gcd ( long a, long b ){
    long c;
    while ( a != 0 ) {
        c = a; 
        a = b%a;
        b = c;
    }
    return b;
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

long primeRelative ( long a, long b ) {
  if ( a == 0 ) 
    return b;
  return primeRelative ( b%a, a );
}

long verifyFullPeriod(long a, long m){
    long x = a;
    long p = 1;
    
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

long cria( long a, long i, long m){
    long x = pot(a,i) % m;
}

int main(){
    long i, mult, m = 32767, a = 0;

    for (i = m; i > 1; i--){
        if (prime(i))
            break;
    }
    printf("largest prime modulus is %ld\n", i);
    m = i;

    for (mult = 1; mult < m; mult++){
        if (verifyFullPeriod(mult, m))
            break;
    }
    a = mult;
    long count = 0;
    for (i = 2; i < m; i++){
        if (gcd(i, m) == 1)
            if (verifyFullPeriod(i, m)){
                //printf("%ld\n", i);
                count++;
            }   
    }

    printf("Quantidade de full-perioeds: %ld\n", count);
    return 0;
}