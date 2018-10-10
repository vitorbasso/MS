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

#include <time.h>

//define MINIMIUM 20                       /* 's' inventory policy parameter */
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
    arq = fopen("arquivo", "w");
    long index     = 0;                      /* time interval index     */
    long s = 15;                             /* iniciando com s=15*/
    long inventory = MAXIMUM;                /* current inventory level */
    long demand;                             /* amount of demand        */
    long order;
    double csetup = 1000;
    double cholding = 25;
    double cshortage = 700;                              /* amount of order         */
    struct                                   /* sum of ...              */
    {
        double setup;                          /*   setup instances       */
        double holding;                        /*   inventory held (+)    */
        double shortage;                       /*   inventory short (-)   */
        double order;                          /*   orders                */
        double demand;                         /*   demands               */
    } sum = {0.0, 0.0, 0.0, 0.0, 0.0};
    long x;
    PutSeed(-1);
    GetSeed(&x);
    printf("Clock: %ld\n", x);
    // s de 15 a 35
    while(s<36)
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
        /* o custo total por intervalo é a soma dos 4 custos:
        citem= custo (unit) de um novo item
        csetup = o custo de instalaçao associado a colocação de um pedido
        cholding = custo para manter um item por um intervalo de tempo
        cshortage = custo pela falta de um item
        */

        fprintf(arq, "%ld %f\n", s, 1000*(sum.setup / index)+25*(sum.holding / index)+700*(sum.shortage / index));

        sum.order = 0;
        sum.demand = 0;
        sum.holding = 0;
        sum.shortage = 0;
        sum.setup = 0;
        index = 0;
        s++;
    }
    fclose(arq);

    /*
      printf("\nfor %ld time intervals ", index);
      printf("with an average demand of %6.2f\n", sum.demand / index);
      printf("and policy parameters (s, S) = (%d, %d)\n\n", MINIMUM, MAXIMUM);
      printf("   average order ............ = %6.2f\n", sum.order / index);
      printf("   setup frequency .......... = %6.2f\n", sum.setup / index);
      printf("   average holding level .... = %6.2f\n", sum.holding / index);
      printf("   average shortage level ... = %6.2f\n", sum.shortage / index);
    */
    return (0);
}
