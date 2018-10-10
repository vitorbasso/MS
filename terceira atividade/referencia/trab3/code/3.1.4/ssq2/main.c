/* -------------------------------------------------------------------------
 * This program - an extension of program ssq1.c - simulates a single-server
 * FIFO service node using Exponentially distributed interarrival times and
 * Uniformly distributed service times (i.e. a M/U/1 queue).
 *
 * Name              : ssq2.c  (Single Server Queue, version 2)
 * Author            : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-11-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define LAST         2154200L                   /* number of jobs processed */
#define START        0.0                      /* initial time             */
#define interarrivalRate 0.56



double Exponential(double m)
/* ---------------------------------------------------
 * generate an Exponential random variate, use m > 0.0
 * ---------------------------------------------------
 */
{
    return (-m * log(1.0 - Random()));
}


double Uniform(double a, double b)
/* --------------------------------------------
 * generate a Uniform random variate, use a < b
 * --------------------------------------------
 */
{
    return (a + (b - a) * Random());
}


double GetArrival(void)
/* ------------------------------
 * generate the next arrival time
 * ------------------------------
 */
{
    static double arrival = START;

    arrival += Exponential(2.0);
    return (arrival);
}


double GetService(void)
/* ------------------------------
 * generate the next service time
 * ------------------------------
 */
{
    return (Uniform(1.3, 2.3));
}


int main(void)
{
    FILE *arq;
    arq = fopen("seed54321.txt", "w+");
    long   index     = 0;                         /* job index            */
    double arrival   = START;                     /* time of arrival      */
    double delay;                                 /* delay in queue       */
    double service;                               /* service time         */
    double wait;                                  /* delay + service      */
    double departure = START;                     /* time of departure    */
    struct                                        /* sum of ...           */
    {
        double delay;                               /*   delay times        */
        double wait;                                /*   wait times         */
        double service;                             /*   service times      */
        double interarrival;                        /*   interarrival times */
    } sum = {0.0, 0.0, 0.0};

    PutSeed(54321);
    int aux=0;

    if(arq==NULL){
        printf("Erro ao abrir\n");
        exit(1);
    }

    //double arredondado = (float)round((2/(1.3+2.3))*100)/100.0, teste,teste2;


    while (index < LAST)
    {
        index++;
        aux++;
        arrival      = GetArrival();
        if (arrival < departure)
            delay      = departure - arrival;         /* delay in queue    */
        else
            delay      = 0.0;                         /* no delay          */
        service      = GetService();
        wait         = delay + service;
        departure    = arrival + wait;              /* time of departure */
        sum.delay   += delay;
        sum.wait    += wait;
        sum.service += service;
        if(aux==20){
            fprintf(arq, "%d %.2f\n ",index, sum.wait / index);
            aux=0;
//            sum.interarrival = arrival - START;
//            teste = (float)round((1/(sum.service / index))*100)/100.0;
//            teste2 = (float)round((1/(sum.interarrival / index))*100)/100.0;
//            if(arredondado == teste&&0.5 == teste2)
//                flag = 0;

        }

    }
    sum.interarrival = arrival - START;

    printf("\nfor %ld jobs\n", index);
    printf("   average interarrival time = %6.2f\n", sum.interarrival / index);
    printf("   average wait ............ = %6.2f\n", sum.wait / index);
    printf("   average delay ........... = %6.2f\n", sum.delay / index);
    printf("   average service time .... = %6.2f\n", sum.service / index);
    printf("   average # in the node ... = %6.2f\n", sum.wait / departure);
    printf("   average # in the queue .. = %6.2f\n", sum.delay / departure);
    printf("   utilization ............. = %6.2f\n", sum.service / departure);
    fprintf(arq, "The min number of jobs to entry in a steady-state is: %d\n", index);
    fclose(arq);
    return (0);
}
