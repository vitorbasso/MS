
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service
 * node.
 *
 * Name              : ssq1.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-01-98
 * Compile with      : gcc ssq1.c
 * -------------------------------------------------------------------------
 */

#include <stdio.h>

#define FILENAME   "ssq1.dat"                  /* input data file */
#define START      0.0
#define SERVICE_MUL     1.0          /* Multiplier for service --  increase and decrease the traffic ratio*/
#define DEBUG 1.0                           /* When SERVICE_MUL == 1.0  -- use this number to determine the SERVICE_MUL value necessery for a traffic intensity equal to DEBUG*/
#define DEBUGGING 1.0

/* =========================== */
   double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

/* =========================== */
   double GetService(FILE *fp)                 /* read a service time */
/* =========================== */
{
  double s;

  fscanf(fp, "%lf\n", &s);
  return (s);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE   *fp;                                  /* input data file      */
  long   index     = 0;                        /* job index            */
  double arrival   = START;                    /* arrival time         */
  double delay;                                /* delay in queue       */
  double service;                              /* service time         */
  double wait;                                 /* delay + service      */
  double departure = START;                    /* departure time       */
  double interarrival_mean;
  double delay_mean;
  double service_mean;
  double wait_mean;
  double time_Node;                              /* Time average number in node*/
  double time_Queue;                             /* Time average number in queue*/
  double time_Service;                           /* Time average number in service*/
  double arrival_rate;                           /* Arrival rate = 1/rbarra*/
  double service_rate;                           /* Service rate = 1/sbarra*/
  double traffic_intensity;                      /* Traffic intensity = arrival_rate / service_rate*/
  double service_multiplier_info;                /* Info only*/
  struct {                                     /* sum of ...           */
    double delay;                              /*   delay times        */
    double wait;                               /*   wait times         */
    double service;                            /*   service times      */
    double interarrival;                       /*   interarrival times */
  } sum = {0.0, 0.0, 0.0};

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  while (!feof(fp)) {
    index++;
    arrival      = GetArrival(fp);
    if (arrival < departure)
      delay      = departure - arrival;        /* delay in queue    */
    else
      delay      = 0.0;                        /* no delay          */
    service      = GetService(fp) * SERVICE_MUL;
    wait         = delay + service;
    departure    = arrival + wait;             /* time of departure */
    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
  }
  sum.interarrival = arrival - START;

  interarrival_mean = sum.interarrival / index;
  service_mean = sum.service / index;
  delay_mean = sum.delay / index;
  wait_mean = sum.wait / index;

  time_Node = sum.wait / (sum.interarrival + wait);
  time_Queue = sum.delay / (sum.interarrival + wait);
  time_Service = sum.service / (sum.interarrival + wait);


  arrival_rate = 1 / interarrival_mean;
  service_rate = 1 / service_mean;


  traffic_intensity = arrival_rate / service_rate;



  //printf("tanNode: %lf -- tanQueue: %lf -- tanService: %lf", tanNode, tanQueue, tanService);  -- debug

  printf("\nfor %ld jobs\n", index);
  printf("   average interarrival time = %6.2f\n", interarrival_mean);
  printf("   average service time .... = %6.2f\n", service_mean);
  printf("   average delay ........... = %6.2f\n", delay_mean);
  printf("   average wait ............ = %6.2f\n", wait_mean);
  printf("   Time average figures --\n");
  printf("   Time average number in node .. = %6.2lf\n", time_Node);
  printf("   Time average number in Queue . = %6.2lf\n", time_Queue);
  printf("   Time average number in Service = %lf\n", time_Service);
  printf("   ------------------------------------\n");
  printf("   arrival rate = %6.2lf\n", arrival_rate);
  printf("   service rate = %6.2lf\n", service_rate);
  printf("   Traffic intensity = %6.2lf\n" , traffic_intensity);


  if(DEBUGGING){
    service_multiplier_info = (interarrival_mean * DEBUG) / service_mean;
    printf("\n\n   -----------------------\n");
    printf("   mult info = %lf -- for traffic = %lf\n", service_multiplier_info, DEBUG);
  }

  fclose(fp);
  return (0);
}
