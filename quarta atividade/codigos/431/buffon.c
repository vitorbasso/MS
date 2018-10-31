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
#include <time.h>

#define N       1000L                     /* number of replications */
#define HALF_PI (2.0 * atan(1.0))          /* 1.5707963...           */


#define DEFAULT 123456789L
#define MODULUS 2147483647L
#define MULTIPLIER 48271L
#define CHECK 399268537L


static long seed = DEFAULT;    /* seed is the state of the generator        */


   double Random(void)
/* ---------------------------------------------------------------------
 * Random is a Lehmer generator that returns a pseudo-random real number
 * uniformly distributed between 0.0 and 1.0.  The period is (m - 1)
 * where m = 2,147,483,647 amd the smallest and largest possible values
 * are (1 / m) and 1 - (1 / m) respectively.
 * ---------------------------------------------------------------------
 */
{
  const long Q = MODULUS / MULTIPLIER;
  const long R = MODULUS % MULTIPLIER;
        long t;

  t = MULTIPLIER * (seed % Q) - R * (seed / Q);
  if (t > 0)
    seed = t;
  else
    seed = t + MODULUS;
  return ((double) seed / MODULUS);
}


   void PutSeed(long x)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to initialize or reset the state of
 * the random number generator according to the following conventions:
 *    if x > 0 then x is the initial seed (unless too large)
 *    if x < 0 then the initial seed is obtained from the system clock
 *    if x = 0 then the initial seed is to be supplied interactively
 * --------------------------------------------------------------------
 */
{
  char ok = 0;

  if (x > 0L)
    x = x % MODULUS;                          /* correct if x is too large  */
  if (x < 0L)
    x = ((unsigned long) time((time_t *) NULL)) % MODULUS;
  if (x == 0L)
    while (!ok) {
      printf("\nEnter a positive integer seed (9 digits or less) >> ");
      scanf("%ld", &x);
      ok = (0L < x) && (x < MODULUS);
      if (!ok)
        printf("\nInput out of range ... try again\n");
    }
  seed = x;
}


   void GetSeed(long *x)
/* --------------------------------------------------------------------
 * Use this (optional) procedure to get the current state of the random
 * number generator.
 * --------------------------------------------------------------------
 */
{
  *x = seed;
}


   void TestRandom(void)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to test for a correct implementation.
 * -------------------------------------------------------------------
 */
{
  long   i;
  long   x;
  double u;

  PutSeed(1);                                /* set initial state to 1 */
  for(i = 0; i < 10000; i++)
    u = Random();
  GetSeed(&x);                               /* get the new state      */
  if (x == CHECK)
    printf("\n The implementation of Random is correct\n");
  else
    printf("\n\a ERROR - the implementation of Random is not correct\n");
}

//########################################################
//#FIM RANDOM V########################
//#####################################################3

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
  long   seed;
  float const R = 1.0;

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

  printf("\nbased on %ld replications and a needle of length %.1lf\n", N, R);
  printf("the estimated probability of a cross is %5.3f\n\n", p);

  return (0);
}
