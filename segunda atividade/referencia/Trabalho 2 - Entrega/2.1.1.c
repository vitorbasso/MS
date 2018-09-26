#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int gcd(int a, int b) //retorna o maximo divisor comum, se for igual a 1, siginifica que n�o h�
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
    m = 127;
    a = 1;

    while(full_period(a, m) == 0)
        a++;
    x = a;

    min = a;
    printf("Todos os full-period multipliers s�o:\n");
	//achando todos os full-period multipliers
    while (x != 1)
    {
        if (gcd(i, m - 1) == 1)/* x is a full-period multiplier equal to ai mod m |
		gcd � a fun��o que verifica se 2 n�meros s�o primos relativos */
        {
              printf("%d ", x);
              count++;
              if(x < min)
                min = x;
        }
        i++;
        x = (a * x) % m;
    }
    printf("\n\n\n");
    printf("H� %d full-period multipliers quando m = %d\n", count, m);
    printf("%d � o menor full-period multiplier quando m = %d\n", min, m);
    return 0;
}
