/* ------------------------------------------------------------------------
 * This program illustrates an array-based algorithm for tallying a
 * continuous-data histogram for data read from standard input (stdin).
 * Like program uvs, a compiled version of this program supports file
 * redirection.
 *
 * The MIN, MAX, K parameters are "tuned" to the datafile uvs.dat.
 * For other datafiles these parameters must be adjusted -- you might
 * want to process the datafile with program uvs first to get a handle on
 * appropriate values for these three parameters.
 *
 * Name              : cdh.c  (Continuous Data Histogram)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 12-27-95
 * ------------------------------------------------------------------------
 */

#include <stdio.h>
#include <math.h>

#define n 500
#define  MIN     0.0
#define  MAX     16.0
#define  K       13                          /* number of histogram bins   */
#define  DELTA   ((MAX - MIN) / K)           /* histogram bin size (width) */
#define  sqr(x)  ((x) * (x))

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

int main(void)
{
    FILE *f;
    f = fopen("serviceT.txt", "r");
    double sample[n];
    double x;                                      /* data value          */
    long   j;                                      /* histogram bin index */
    long   index    = 0;                           /* sample size         */
    long   count[K] = {0.0};                       /* bin count           */
    double midpoint[K];                            /* bin midpoint        */
    struct
    {
        long lo;
        long hi;
    } outliers      = {0, 0};
    double sum      = 0.0;
    double sumsqr   = 0.0;
    double mean, sampleMean1;
    double stdev, sampleStdve;

    for (j = 0; j < K; j++)
        midpoint[j] = MIN + (j + 0.5) * DELTA;

    while (!feof(f))                           /* tally the data */
    {
        fscanf(f,"%lf\n", &x);
        sample[index] = x;
        index++;
        if ((x >= MIN) && (x < MAX))
        {
            j = (long) ((x - MIN) / DELTA);
            count[j]++;
        }
        else if (x < MIN)
            outliers.lo++;
        else
            outliers.hi++;
    }

    for (j = 0; j < K; j++)                        /* histogram mean */
        sum += midpoint[j] * count[j];
    mean   = sum / index;

    for (j = 0; j < K; j++)                        /* histogram stdev */
        sumsqr += sqr(midpoint[j] - mean) * count[j];
    stdev     = sqrt(sumsqr / index);

    printf("  bin     midpoint     count   proportion    density\n\n");
    for (j = 0; j < K; j++)
    {
        printf("%5ld", j + 1);                                    /* bin        */
        printf("%12.3f", midpoint[j]);                            /* midpoint   */
        printf("%10ld", count[j]);                                /* count      */
        printf("%12.3f", (double) count[j] / index);              /* proportion */
        printf("%12.3f\n", (double) count[j] / (index * DELTA));  /* density    */
    }
    printf("\nsample size .... = %7ld\n", index);
    printf("mean ........... = %7.3f\n", mean);
    printf("stdev .......... = %7.3f\n\n", stdev);
    if (outliers.lo > 0)
        printf("NOTE: there were %ld low outliers\n", outliers.lo);
    if (outliers.hi > 0)
        printf("NOTE: there were %ld high outliers\n", outliers.hi);

    sampleMean1 = sampleMean(sample);
    sampleStdve = sampleStandartDeviation(sample, mean);

    printf("Sample mean = %7.3lf\nSample stdve = %7.3lf\n", sampleMean1, sampleStdve);

    return (0);
}
