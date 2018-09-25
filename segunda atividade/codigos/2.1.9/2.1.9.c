#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int x){
    int i;

    if(x == 1){
        return 0;
    }else if (x == 2){
        return 1;
    }
    for (i = 2; i < x; i ++){
        if(x%i == 0)
            return 0;
    }
    return 1;
}

int greaterCommonDivisor(int x, int y){
    int gcd = 0, i = 0;
    for(i = 1; i <= x && i <= y; ++i){
        if(x % i == 0 && y % i == 0){
            gcd = i;
        }
    }
    return gcd;
}

int isFullPeriod(int a, int m){
    int p = 1, x = a;
    while (x != 1){
        p++;
        x = (a * x) % m;
    }
    if(p == m - 1)
        return 1;
    else
        return 0;
}

int middle(int a, int i, int m){
    return (int)pow(a, i) % m;
}

void doIt(int a, int m){
    int i = 1;
    printf("For %d^%d mod %d = %d\n", a, i, m, middle(a, i, m));
    i = 5;
    printf("For %d^%d mod %d = %d\n", a, i, m, middle(a, i, m));
    i = 7;
    printf("For %d^%d mod %d = %d\n", a, i, m, middle(a, i, m));
    i = 11;
    printf("For %d^%d mod %d = %d\n", a, i, m, (long int)pow(a, i) % m);
}

int lehmer(int a, int x, int m){
    return (a * x) % m;
}

int main(){
    int i = 1, a = 7, m = pow(2, 31) -1, count = 1;
    long long x = a;

     printf("Verifying the first 5 numbers:\n");
     while(count<11){
        if (greaterCommonDivisor(i, m - 1) == 1)/* x is a full-period multiplier equal to ai mod m |   gcd й a funзгo que verifica se 2 nъmeros sгo primos relativos */
        {
            printf("7^%d mod %d = %d\n", i, m, x);
            if(count == 5)
                printf("\n\nNext 5 full period multiplier values:\n");
            count++;

        }
        i++;
        x = (a*x) % m;
    }

    return 0;
}
