/* -------------------------------------------------------------------------
 * This program - an extension of program sis1.c - simulates a simple (s,S)
 * inventory system using Equilikely distributed demands.
 *
 * Name              : sis2.c  (Simple Inventory System, version 2)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 8-28-97
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include "rng.h"
#include "rng.c"

#include <time.h>

#define MINIMIUM 20                       /* 's' inventory policy parameter */
#define MAXIMUM  80                        /* 'S' inventory policy parameter */
#define STOP     1000                       /* number of time intervals       */
#define sqr(x)   ((x) * (x))


long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
    return (a + (long) ((b - a + 1) * Random()));
}


long GetDemand(void)
/* ------------------------
 * generate the next demand
 * ------------------------
 */
{
    return (Equilikely(10, 50));
}


int main(void)
{
    FILE *arq;
    arq = fopen("outputsPGrafico.dat", "w");
    long index     = 0;                      /* time interval index     */
    long inventory = MAXIMUM;                /* current inventory level */
    long demand;                             /* amount of demand        */
    long order;

    int i = 0;
    long s = 15;  // VALOR INICIAL DE 15 ATÉ 35

    struct
    {
        double setup;                          /*   setup instances       */
        double holding;                        /*   inventory held (+)    */
        double shortage;                       /*   inventory short (-)   */
        double order;                          /*   orders                */
        double demand;                         /*   demands               */
    } sum = {0.0, 0.0, 0.0, 0.0, 0.0};
    long x;

    PutSeed(-1);

    GetSeed(&x); /*system clock gera uma seed*/

    printf("Seed fornecida pelo system clock: %ld\n", x);


       for (s=15;s<36; s++)
    {
        while (index < STOP)
        {
            index++;
            if (inventory < s)               /* place an order */
            {
                order         = MAXIMUM - inventory;
                sum.setup++;
                sum.order    += order;
            }
            else                                   /* no order       */
                order         = 0;
            inventory      += order;               /* there is no delivery lag */
            demand          = GetDemand();
            sum.demand     += demand;
            if (inventory > demand)
                sum.holding  += (inventory - 0.5 * demand);
            else
            {
                sum.holding  += sqr(inventory) / (2.0 * demand);
                sum.shortage += sqr(demand - inventory) / (2.0 * demand);
            }
            inventory     -= demand;
        }

        if (inventory < MAXIMUM)                 /* force the final inventory to */
        {
            order      = MAXIMUM - inventory;      /* match the initial inventory  */
            sum.setup++;
            sum.order += order;
            inventory += order;
        }

        fprintf(arq, "\n%ld %f\n", s, 10000 * (sum.setup / index) + 500 *(sum.holding / index)+ 5000 *(sum.shortage / index));

        sum.order = 0;

        sum.demand = 0;

        sum.holding = 0;

        sum.shortage = 0;

        sum.setup = 0;

        index = 0;


    }
    fclose(arq);
    return (0);
}
