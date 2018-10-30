/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of Buffon's needle experiment. 
 * 
 * Name              : buffon.c 
 * Author            : Steve Park & Dave Geyer 
 * Language          : ANSI C
 * Latest Revision   : 9-11-98 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rng.h"

#define N       1000L                     /* number of replications */
#define HALF_PI (2.0 * atan(1.0))          /* 1.5707963...           */
#define R       2.0                        /* length of the needle   */


   double Uniform(double a, double b)      
/* --------------------------------------------
 * generate a Uniform random variate, use a < b 
 * --------------------------------------------
 */
{
  return (a + (b - a) * Random());
}


  int main(void)
{ 
  long   i;                                /* replication index     */
  long   crosses = 0;                      /* number of crosses     */
  double p;                                /* estimated probability */
  double u, v;                             /* endpoints             */
  double theta;                            /* angle                 */
  long   seed;                             /* the initial rng seed  */   

  PutSeed(1234);                 /* any negative integer will do      */
	FILE* fp = fopen("data.dat", "w");

  for (i = 0; i < N; i++) {                
    u     = Random();                                   
    theta = Uniform(-HALF_PI, HALF_PI);
    v     = u + R * cos(theta);
	fprintf(fp, "%lf\n", v);
    if (v > 1.0)
      crosses++;
  }

  p = (double) crosses / N;                /* estimate the probability */

  printf("\nbased on %ld replications and a needle of length %5.2f\n", N, R);
  printf("the estimated probability of a cross is %5.3f\n\n", p);

  return (0);
}
