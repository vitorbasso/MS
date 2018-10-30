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
#include "rng.h"

//#define N 10000L                          /* number of replications */


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
  long   i;                               /* replication index      */
  long   x;                               /* sum of three dice      */
  double p[10]     = {0.0};               /* probability estimates  */
  long n;                                   //numero de caixas
  long xi[1000];                        //armazena quantas bolas estao em cada caixa
  long j;


  PutSeed(12345);    //semente inicial 12345

  n = 1000;
  for (i = 0; i <= n; i++) /* i counts boxes */
    xi[i] = 0;

  for (j = 0; j < 2000; j++) {         /* j conta as bolas */
        i = Equilikely(1, n);           /* gera uma caixa aleatoria  */
        xi[i]=xi[i]+1;                   /* armazena a bola na caixa */
   }

   for(i=0;i<10;i++)                    //zera o vetor p[10]
    p[i]=0;

//ESTATISTICAS
//Calculo frequencia

    for(i=0;i<10;i++){              //percorre o vetor analisando quantas vezes o numero de bolas repete em cada caixa
        for(j=0;j<1000;j++){
        if (xi[j]==i)
            p[i]=p[i] +1;

    }
    printf("x[%d]=%5.3f\n", i,(double)p[i]/n);  // calcula e imprime a frequencia para x{1...9}
}

  printf("\n\n ");


  return (0);
}
