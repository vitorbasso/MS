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
void alg222(m,a)
{
    int i = 1;
    int x = a,q,r;
    while (x != 1)
    {
        if (((m%x)<(m/x)) && (gcd(i, (m-1)) == 1))
        {
            printf("%d is a full-period modulus-compatible multiplier with i equal %d\n", x, i);
            getchar();
        }


        //printf("PROCESSING%d\n", i);
        i++;
        q = m/a;
        r = m%a;
        if(((a*q+r)==m)&&r<q&&x<m)
        {
            x = alg221(m,a,q,r,x);
            //printf("Valor de x atual eh %d\n", x);
        }

    }
}
//t = gama(x) e
int alg221(int m, int a, int q, int r, int x)
{
    int t = a*(x%q) - r *(x/q);
    if(t>0)//delta(x)=0
        return t;
    else //delta(x)=1
        return (t+m);
}
void alg211(int m, int a)
{
    int p =1;
    int x = a;
    while(x!=1)
    {
        p++;
        x=(a*x)%m;
    }
    if(p==m-1)
        printf("%d is a full-period multiplier\n", a);
    else
        printf("%d isn't a full-period multiplier\n", a);
}
int main()
{
    int a[6]= {630360016,742938285,950706376,1226874159,62089911,1343714438}, m = 2147483647;
    int q,r,i;
    for(i=0; i<6; i++)
    {
        q= m/a[i];
        r = m%a[i];
        if(r<q)
            printf("%d is module compatible with %d\n",a[i],m);
        else
            printf("%d isn't module compatible with %d\n",a[i],m);

    }

    return 0;
}
