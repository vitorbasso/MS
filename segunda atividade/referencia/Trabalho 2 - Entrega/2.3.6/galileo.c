/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of Galileo's three dice experiment.
 *
 * Name              : galileo.c
 * Author            : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-11-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include "rng.h"

#define N 1001L                          /* number of replications */

double chance;


long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
  return (a + (long) ((b - a + 1) * Random()));
}

int main(void)
{
    long   i;                               /* replication index      */
    long   x;                               /* sum of three dice      */
    long   count[19] = {0};                 /* histogram              */
    double p[19]     = {0.0};               /* probability estimates  */

    double prob = 0;
    FILE *arq;

    PutSeed(0);

    arq = fopen("arquivo.txt", "w");
    for (i = 0; i < N; i++)
    {
        x = Equilikely(1, 6) + Equilikely(1, 6) + Equilikely(1, 6); // Três dados buscando o resultado 9
        if(x == 9)
        {
            prob++;
        }
        if(i % 20 == 0)
        {
            if(i != 0)
            {
                chance = prob/i;
                printf("\n %d %5.3f",i, chance);
                fprintf(arq, "\n%5.3f", chance);
            }
        }
        count[x]++;
    }


    for (x = 3; x < 19; x++)   //3 dados             /* estimate probabilities */
    p[x] = (double) count[x] / N;

    printf("\nbased on %ld replications ", N);
    printf("the estimated probabilities are:\n\n");
    for (x = 3; x < 19; x++)
    printf("p[%2ld] = %5.3f\n", x, p[x]);
    printf("\n");
    fclose(arq);

    return (0);
}

