/* ---------------------------------------------------------------------- *
 * A Monte Carlo simulation to estimate the probability that the          *
 * determinant of a 3 by 3 matrix of random numbers is positive.          *
 *                                                                        *
 * Name              : det.c                                              *
 * Author            : Larry Leemis                                       *
 * Language          : ANSI C
 * Latest Revision   : 8-8-02                                             *
 * Compile with      : gcc det.c rng.c                                    *
 *                     if math functions needed, add #include <math.h>    *
 *                     and compile with gcc -lm det.c rng.c               *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 2000L                     /* number of replications        */

#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

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

/* ============= */
  int main(void)
/* ============= */
{
  int    i;                              /* replication index             */
  int    j;                              /* row index                     */
  int    k;                              /* column index                  */
  double a[4][4];                        /* matrix (only 9 elements used) */
  double temp1;                          /* first 2 by 2 determinant      */
  double temp2;                          /* second 2 by 2 determinant     */
  double temp3;                          /* third 2 by 2 determinant      */
  double x;                              /* determinant                   */
  int    count = 0;                      /* counts number of pos det      */

  PutSeed(0);

  for (i = 0; i < N; i++) {
    for (j = 1; j <= 3; j++) {
      for (k = 1; k <= 3; k++) {
        a[j][k] = Random();
        if (j != k)
          a[j][k] = -a[j][k];
      }
    }
    temp1 = a[2][2] * a[3][3] - a[3][2] * a[2][3];
    temp2 = a[2][1] * a[3][3] - a[3][1] * a[2][3];
    temp3 = a[2][1] * a[3][2] - a[3][1] * a[2][2];
    x = a[1][1] * temp1 - a[1][2] * temp2 + a[1][3] * temp3;
    if (x > 0)
      count++;
  }

  printf("\nbased on %ld replications ", N);
  printf("the estimated probability of a positive determinant is:\n");
  printf("%11.9f", (double) count / N);
  printf("\n");

  return (0);
}
