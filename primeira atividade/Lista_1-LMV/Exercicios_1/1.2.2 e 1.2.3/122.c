#include <stdio.h>                              
#define FILENAME   "ssq1.dat"                  /* input data file */
#define START      0.0
#define TAX_ARRIVAL_INTENSITIES      1.00
#define SYSTEMATIC_INCREASE          1.18

double GetArrival(FILE *fp){ 
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

double GetService(FILE *fp){ 
  double s;

  fscanf(fp, "%lf\n", &s);
  return (s);
}

int main(void){
  FILE   *fp;                                  /* input data file      */
  long   index     = 0;                        /* job index            */
  double arrival   = START;                    /* arrival time         */
  double delay;                                /* delay in queue       */
  double service;                              /* service time         */
  double wait;                                 /* delay + service      */
  double departure = START;                    /* departure time       */
  double last_arrival = START;
  
  struct {                                     /* sum of ...           */
    double l_barra;
    double q_barra;
    double x_barra;
    double s_barra;                            /*   service times      */
    double d_barra;                            /*   delay times        */
    double w_barra;                            /*   wait times         */
    double r_barra;
    double interarrival;                       /*   interarrival times */
  } sum = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  while (!feof(fp)) {
    index++;
    last_arrival = arrival;
    arrival      = GetArrival(fp) * TAX_ARRIVAL_INTENSITIES;
    if (arrival < departure) {
      delay      = departure - arrival;        /* delay in queue    */
    } else {
      delay      = 0.0;                        /* no delay          */
    } 
    service      = GetService(fp) * SYSTEMATIC_INCREASE;
    wait         = delay + service;
    departure    = arrival + wait;             /* time of departure */
    sum.s_barra += service;
    sum.d_barra += delay;
    sum.w_barra += wait;
    sum.r_barra += (arrival - last_arrival);
  }
  sum.interarrival = arrival - START;
  sum.l_barra = (index/departure) * (sum.w_barra/ index);
  sum.q_barra = (index/departure) * (sum.d_barra/ index);
  sum.x_barra = (index/departure) * (sum.s_barra/ index);

  printf("\nvalor do trafico: %f\n", sum.s_barra/ sum.r_barra);

  // printf("\nfor %ld jobs\n", index);
  // printf("   average interarrival time = %6.2f\n", sum.interarrival / index);
  // printf("   s_barra ................. = %6.2f\n", sum.s_barra / index);
  // printf("   d_barra ................. = %6.2f\n", sum.d_barra / index);
  // printf("   w_barra ................. = %6.2f\n", sum.w_barra / index);
  // printf("   r_barra ................. = %6.2f\n", sum.r_barra / index);
  // printf("   l_barra.................. = %6.3f\n", sum.l_barra);
  // printf("   q_barra.................. = %6.3f\n", sum.q_barra);
  // printf("   x_barra.................. = %6.3f\n", sum.x_barra);

  // printf("%6.3f\n", sum.l_barra);
  printf("%6.2f\n", sum.q_barra);
  // printf("%6.3f\n", sum.x_barra);
  fclose(fp);
  return (0);
}
