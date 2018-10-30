#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#define n 100
#define st 10
#include "rngs.h"

double Exponential(double m)
{
  return (-m * log(1.0 - Random()));
}

double sampleMean(double *sample)
{
    double mean = 0;
    int i;

    for(i=0; i<n; i++)
        mean+= sample[i];

    return mean/n;
}

double sampleStandartDeviation(double *sample, double mean)
{
    double variance = 0;
    int i;

    for(i=0; i<n; i++)
        variance+= pow(sample[i] - mean, 2);

    variance = variance/n;
    return sqrt(variance);
}
int main()
{
    setlocale(LC_ALL, "Portuguese");

    double sample[n], mean, variance;
    int i, aux = 0, count2s = 0, count3s = 0;

    printf("Proporção de amostras em:\n\ntype\tmédia+-2*s\tmédia+-3*s\n");
    while(aux < 10)
    {
        SelectStream(aux);
        for(i=0; i<n; i++)
        {
            sample[i] = Exponential(9);
        }

        mean = sampleMean(sample);
        variance = sampleStandartDeviation(sample, mean);

        for(i=0; i<n; i++)
        {
            if(sample[i] >= (mean - 2*variance) && sample[i] <= (mean + 2*variance))
                count2s++;
            if(sample[i] >= (mean - 3*variance) && sample[i] <= (mean + 3*variance))
                count3s++;
        }

        printf("%d\t%.2f\t\t%.2f\n", aux, (double)count2s/n, (double)count3s/n);
        aux++;
        count2s = 0;
        count3s = 0;
    }

    printf("\n\nChebyshev’s inequality para k=2: pk >= %.2f\nChebyshev’s inequality para k=3: pk >= %.2f\n", 1.0-1.0/4.0, 1.0-1.0/9.0);
    return 0;
}
