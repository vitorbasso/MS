#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int gcd(int a, int b) //retorna o maximo divisor comum, se for igual a 1, siginifica que nгo hб
{
    int r;
    r = a % b;
    while (r > 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int full_period(int a, int m)
{
    int p, x;
    p = 1;
    x = a;
    while (x != 1)
    {
        p++;
        x = (a * x) % m; /* beware of a * x overflow */
    }
    if (p == m - 1) /* a is a full-period multiplier */
        return 1;
    else /* a is not a full-period multiplier */
        return 0;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int i, a, m, count = 0, min;
    long long x;
    a = 7;
    i = 1;
    m = pow(2,31)-1;
    x = a;

    //achando os cinco primeiros full-period multipliers
        while(count<10){
        if (gcd(i, m - 1) == 1)/* x is a full-period multiplier equal to ai mod m |   gcd й a funзгo que verifica se 2 nъmeros sгo primos relativos */
        {
            printf("7^%d mod %d = %d\n", i, m, x);
            count++;

        }
        i++;
        x = (a*x) % m;
    }

        //achando os proximos 5 elementos da lista quesstãob
    return 0;
}
