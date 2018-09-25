#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b)
{
    int r = a%b;
    while(r>0)
    {
        a=b;
        b=r;
        r = a%b;
    }
    return b;
}
void alg212(m,a)
{
    int i = 1;
    int x = a;
    while (x != 1)
    {
        if (gcd(i, (m-1)) == 1)
            printf("The a full-period is %d for i equals %d\n", x, i);

        i++;
        x = (a * x) % m; /* beware of a * x overflow */


    }
}
int main()
{
    int a, m;
    printf("For a full-period 7 and m modulus 13 we have:\n\n");
    alg212(13,7);
    printf("\n\nFor a full-period 11 and m modulus 13 we have:\n\n");
    alg212(13,11);

    return 0;
}
