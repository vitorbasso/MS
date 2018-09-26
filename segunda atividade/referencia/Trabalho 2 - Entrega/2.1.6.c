#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int primo(int x)
{
    int i;

    if(x == 1)
        return 0;

    if(x == 2)
        return 1;

    for(i=2; i<x; i++)
    {
        if(x%i == 0)
            return 0;
    }
    return 1;
}

int gcd(int a, int b) //retorna o maximo divisor comum, se for igual a 1, siginifica que não há
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

    int i, a, x, m, count = 0, min;

    i = 1;
    a = 1;
    m = pow(2, 15) - 1;

    //maior primo menor que (2^15)-
    while(primo(m) == 0)
        m--;
    printf("Maior primo no intervalo [-(2^15)+1, (2^15)-1] é %d\n", m);

    //procurando o primeiro full-period multipler
    while(full_period(a, m) == 0)
        a++;
    x = a;

    min = a;

    //achando todos os full-period multipliers
    while (x != 1)
    {
        if (gcd(i, m - 1) == 1)/* x is a full-period multiplier equal to ai mod m |
        gcd é a função que verifica se 2 números são primos relativos */
        {
              count++;
              if(x < min)
                min = x;
        }
        i++;
        x = (a * x) % m;
    }
    printf("Há %d full-period multipliers quando m = %d\n", count, m);
    printf("%d é o menor full-period multiplier quando m = %d\n", min, m);
    return 0;
}
