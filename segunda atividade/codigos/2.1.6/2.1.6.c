#include <stdio.h>
#include <stdlib.h>

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

int main(){
    int i;
    for( i = 32767; i > 1; i--){
    if(isPrime(i))
        break;
    }
    printf("The largest prime modulus for 2^15 - 1 is %d\n", i);

    int a, m = i;

    for(a = 2; a < m; a++){
        if(isFullPeriod(a, m))
            break;
    }

    printf("The smallest multiplier in this case is %d\n", a);

    int count = 0;
    int x = a;
    i = 1;
    while (x != 1){
        if(greaterCommonDivisor(i, m - 1) == 1){
            count++;
        }
        i++;
        x = (a * x) % m;
    }

    printf("\nThere are %d full period multipliers for when m = %d\n\n", count, m);

    return 0;
}
