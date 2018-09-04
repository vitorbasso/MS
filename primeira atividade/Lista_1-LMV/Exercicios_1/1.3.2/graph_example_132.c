
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

/*
* This code is used for question 1.3.4 too and you need change MAXIMUM value to
* 60 and 100 to produce the output used to build table life Figure 1.3.7
*/

#include <stdio.h>                        

#define FILENAME  "sis1.dat"            /* input data file                */
#define MINIMUM   20                        /* 's' inventory policy parameter */
#define MAXIMUM   100                        /* 'S' inventory policy parameter */

#define C_ITEM    8000
#define C_SETUP   1000
#define C_HOLD      25
#define C_SHORT    700

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
  double cItemTotalCost     = 0;
  double cSetupTotalCost    = 0;
  double cHoldTotalCost     = 0;
  double cShortageTotalCost = 0;
  struct {                                 /* sum of ...              */
    double setup;                          /*   setup instances       */
    double holding;                        /*   inventory held (+)    */
    double shortage;                       /*   inventory short (-)   */
    double order;                          /*   orders                */
    double demand;                         /*   demands               */
  } sum = { 0.0, 0.0, 0.0, 0.0, 0.0 };

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  printf("\n\nThis code is used for question 1.3.4 too and you need change MAXIMUM \n value to 60 and 100 to produce the output used to build table life Figure 1.3.7\n\n");

  int i = 0;
  for ( i = 1; i < 41; i++) {
	  index     = 0;                      /* time interval index     */
	  inventory = MAXIMUM;                /* current inventory level */
	  demand = 0;                             /* amount of demand        */
	  order = 0;                              /* amount of order         */

	  while (!feof(fp)) {
	    index++;
	    if (inventory < i) {             /* place an order          */
	      order         = MAXIMUM - inventory;
	      sum.setup++;
	      sum.order    += order;
	    }
	    else                                   /* no order                 */
	      order         = 0;                   
	    inventory      += order;               /* there is no delivery lag */
	    demand          = GetDemand(fp);
	    sum.demand     += demand;
	    if (inventory > demand) 
	      sum.holding  += (inventory - 0.5 * demand);
	    else {
	      sum.holding  += sqr(inventory) / (2.0 * demand);
	      sum.shortage += sqr(demand - inventory) / (2.0 * demand);
	    }
	    inventory      -= demand;
	  }

	  if (inventory < MAXIMUM) {               /* force the final inventory to */
	    order           = MAXIMUM - inventory; /* match the initial inventory  */
	    sum.setup++;
	    sum.order      += order;
	    inventory      += order;
	  }

	  cSetupTotalCost = (sum.setup / index) * C_SETUP;
  	  cHoldTotalCost = (sum.holding / index) * C_HOLD;
  	  cShortageTotalCost = (sum.shortage / index) * C_SHORT;
	  
          printf(" == %d == \n", i);
	  printf("%6.2f\n", cSetupTotalCost);
	  printf("%6.2f\n", cHoldTotalCost);
	  printf("%6.2f\n", cShortageTotalCost);
	  printf("%6.2f\n\n", cSetupTotalCost + cHoldTotalCost + cShortageTotalCost);
		
	  sum.demand = 0.0;
	  sum.order = 0.0;
	  sum.setup = 0.0;
	  sum.holding = 0.0;
	  sum.shortage = 0.0;
	  fseek(fp, 0, SEEK_SET);
  }

  	

  if (inventory < MAXIMUM) {               /* force the final inventory to */
    order           = MAXIMUM - inventory; /* match the initial inventory  */
    sum.setup++;
    sum.order      += order;
    inventory      += order;
  }

  printf("\nfor %ld time intervals ", index);
  printf("with an average demand of %6.2f\n", sum.demand / index);
  printf("and policy parameters (s, S) = (%d, %d)\n\n", MINIMUM, MAXIMUM);
  printf("   average order ............ = %6.2f\n", sum.order / index);
  printf("   setup frequency .......... = %6.2f\n", sum.setup / index);
  printf("   average holding level .... = %6.2f\n", sum.holding / index);
  printf("   average shortage level ... = %6.2f\n", sum.shortage / index);

  fclose(fp);
  return (0);
}
