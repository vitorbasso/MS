#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Random(void)
{
const long A = 48271; /* multiplier */
const long M = 2147483647; /* modulus */
const long Q = M / A; /* quotient */
const long R = M % A; /* remainder */
static long state = 1;
long t = A * (state % Q) - R * (state / Q);
if (t > 0)
state = t;
else
state = t + M;
return ((double) state / M);
}

double Exponential(double x)
{
    return (-x * log(1 - Random()));
}

int main()
{
    int n = 1;
    double sample;
    double x = 0;
    double samples[100];
    double ss = 0;
    double s;
    double prop2 = 0;
    double prop3 = 0;
    int count = 0;

    while (count < 10){
    while (n <= 100){
    sample = Exponential(9);
    //printf("%f\n", sample);
    samples[n] = sample;
    x = x + sample;
    n++;
    }
    x = x/n;
    printf("\n Sample Mean 'x' = %f", x);
    for (n = 0; n < 100; n++)
        {
            ss = ss + ((samples[n] - x) * (samples[n] - x));
        }
    ss = ss/100;
    s = sqrt(ss);
    printf("\nStandard deviation 's' = %f", s);

   for (n = 0; n < 100; n++)
        {
            if (samples[n] < (x + (2 * s)) && samples[n] > (x - (2 * s)))
                {
                    prop2++;
                }
        }

    printf("\nProporcao 'prop2' com k == 2 : %.2f por cento", prop2);

    for (n = 0; n < 100; n++)
        {
            if (samples[n] < (x + (3 * s)) && samples[n] > (x - (3 * s)))
                {
                    prop3++;
                }
        }
    printf("\nProporcao 'prop3' com k == 3 : %.2f por cento\n\n\n", prop3);
    n = 1;
    x = 0;
    ss = 0;
    s = 0;
    prop2 = 0;
    prop3 = 0;
    count++;
    }


    return 0;
}
