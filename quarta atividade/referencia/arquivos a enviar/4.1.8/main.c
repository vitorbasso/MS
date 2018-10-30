#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "rngs.h"
#define N 101

double Exponential(double m)
{
    return (-m * log(1.0 - Random()));
}

double sampleMean(double *sample, int j)
{
    double mean = 0;
    int i;

    for(i=0; i<j; i++)
        mean+= sample[i];

    return mean/j;
}

double sampleStandartDeviation(double *sample, double mean, int j)
{
    double variance = 0;
    int i;

    for(i=0; i<j; i++)
        variance+= pow(sample[i] - mean, 2);

    variance = variance/j;
    return sqrt(variance);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FILE *f;
    f = fopen("MEANANDSTDVE.txt", "w");

    double mean = 0, v = 0.0, s, x, d;
    int n = 0;

    PlantSeeds(12345);
    while(n <= 100)
    {
        x = Exponential(17);
        n++;
        d = x - mean;
        v = v + d * d * (n-1)/n;
        mean+= d/n;
        fprintf(f, "%d %.2lf %.2lf %.2lf\n", n, x, mean, sqrt(v/n));
    }
    s = sqrt(v / n);

    fclose(f);

    return 0;
}
