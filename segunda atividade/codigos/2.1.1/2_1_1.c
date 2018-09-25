#include <stdio.h>
#include <stdlib.h>

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

    int a = 1, m = 127;
    while(!isFullPeriod(a, m)){
        a++;
    }
    int x = a;
    int minimo = a;

    printf("O valor minimo para um full period multplier com m = %d e de %d\n", m, minimo);
    printf("Todos os valores que sao full period multiplier:\n");
    int i = 1, count = 0;
    while( x != 1){ //enquanto x nao voltar a valer 1 ( que e o valor de x0)
        if(greaterCommonDivisor(i, m - 1) == 1){
            printf("%d ", x);
            count ++;
        }
        i++;
        x = (a * x) % m;
    }
    printf("\n\nFor a total of %d\n", count);

    return 0;
}
