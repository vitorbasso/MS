
/* -------------------------------------------------------------------------
 * This program simulates a simple (s,S) inventory system using demand read  
 * from a text file.  Backlogging is permitted and there is no delivery lag.
 * The output statistics are the average demand and order per time interval
 * (they should be equal), the relative frequency of setup and the time
 * averaged held (+) and short (-) inventory levels.
 *
 * NOTE: use 0 <= MINIMUM < MAXIMUM, i.e., 0 <= s < S.
 *
 * Name              : sis1.c  (Simple Inventory System, version 1)
 * Authors           : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 8-20-97 
 * Compile with      : gcc sis1.c
 * ------------------------------------------------------------------------- 
*/

#include <stdio.h>                        

#define FILENAME  "131.dat"            /* input data file                */
#define MINIMUM   20                    /* 's' inventory policy parameter */
#define MAXIMUM   60                    /* 'S' inventory policy parameter */
#define sqr(x)    ((x) * (x))

/* ======================== */
   long GetDemand(FILE *fp)            
/* ======================== */
{
  long d;

  fscanf(fp, "%ld\n", &d);
  return (d);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE *fp;                                /* input data file         */
  long index     = 0;                      /* time interval index     */
  long inventory = MAXIMUM;                /* current inventory level */
  long demand;                             /* amount of demand        */
  long order;                              /* amount of order         */
  struct {                                 /* sum of ...              */
    double setup;                          /*   setup instances       */
    double holding;                        /*   inventory held (+)    */
    double shortage;                       /*   inventory short (-)   */
    double order;                          /*   orders                */
    double demand;                         /*   demands               */
  } sum = { 0.0, 0.0, 0.0, 0.0, 0.0 };

  printf("\n\nThis code is used to test Example 1.3.1 for question 1.3.1!\n\n");

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }


  while (!feof(fp)) {
    index++;
    if (inventory < MINIMUM) {             /* place an order          */
      order         = MAXIMUM - inventory;
    }
    else                                   /* no order                 */
      order         = 0;                   
    demand          = GetDemand(fp);
    inventory      += order - demand;

    printf("\ntime inverval ... = %ld\n", index);
    printf("    order %ld  ....... = %ld\n", index, order);
    printf("    level %ld ........ = %ld\n", index, inventory);
  }

  fclose(fp);
  return (0);
}
