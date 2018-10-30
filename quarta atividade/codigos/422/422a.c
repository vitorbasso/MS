/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of Galileo's three dice experiment.
 *
 * Name              : galileo.c
 * Author            : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-11-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <time.h>

// RANDOM PROGRAMA ################################################################

#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */
#define CAIXAS     1000
#define MAXIMO     22
#define BOLAS      10000


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

//###############################################################
// ACABOU O RANDOM ###################################################################3
//###############################################################

   long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
  return (a + (long) ((b - a + 1) * Random()));
}


  int main(void)
{
  long   i, j;
  long xi[CAIXAS];                          //armazena quantas BOLAS estao em cada caixa
  double f[MAXIMO] = {0.0};                   //relative frequencies

  PutSeed(12345);

  //Inicializa o vetor de caixas com o valor zero
  for (i = 0; i <= CAIXAS; i++)
    xi[i] = 0;


  /* Coloca cada bola em uma caixa escolhida aleatoriamente*/
  for (j = 0; j < BOLAS; j++) {
        i = Equilikely(1, CAIXAS);        //Escolhe uma caixa aleatoria
        xi[i]++;                    //Coloca a bola na caixa escolhida
   }

   //Inicializa o vetor de frequencias relativas com o valor zero
   for(i=0;i<MAXIMO;i++)
    f[i]=0;

    //Realiza o calculo das frequencias relativas de quantidade de bola em uma dada caixa
    for(j = 0; j < CAIXAS; j++)
        if(xi[j] < MAXIMO)
            f[xi[j]]++;


    printf("Frequencias relativas:\n");
    for(i = 0; i < MAXIMO; i++)
        printf("f[%d]=%5.3f\n", i,(double)f[i]/CAIXAS);  // calcula e imprime a frequencia para x{1...9}


  printf("\n\n ");


  return (0);
}
