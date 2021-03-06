/* -------------------------------------------------------------------------
 * This program reads a (text) data file and computes the mean, minimum,
 * maximum, and standard deviation.   The one-pass algorithm used is due to
 * B.P. Welford (Technometrics, vol. 4, no 3, August 1962.)
 *
 * NOTE: the text data file is assumed to be in a one-value-per-line format
 * with NO blank lines in the file.   The data can be either fixed point
 * (integer valued), or floating point (real valued).
 *
 * To use the program, compile it to disk to produce uvs.  Then at a command
 * line prompt, uvs can be used in three ways.
 *
 * (1) To have uvs read a disk data file, say uvs.dat (in the format above),
 * at a command line prompt use '<' redirection as:
 *
 *     uvs < uvs.dat
 *
 * (2) To have uvs filter the numerical output of a program, say test, at a
 * command line prompt use '|' pipe as:
 *
 *     test | uvs
 *
 * (3) To use uvs with keyboard input, at a command line prompt enter:
 *
 *      uvs
 *
 * Then enter the data -- one value per line -- being sure to remember to
 * signify an end-of-file.  In Unix/Linux, signify an end-of-file by
 * entering ^d (Ctrl-d) as the last line of input.
 *
 * Name              : uvs.c  (Univariate Statistics)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-28-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include <math.h>

double Random(void)
{
const long A = 48271; /* multiplier */
const long M = 2147483647; /* modulus */
const long Q = M / A; /* quotient */
const long R = M % A; /* remainder */
static long state = 1;
long t = A * (state % Q) - R * (state / Q);
if (t > 0)
state = t;
else
state = t + M;
return ((double) state / M);
}

double Exponential(double x)
{
    return (-x * log(1 - Random()));
}


  int main(void)
{
  long    index = 0;
  double  data;
  double  sum = 0.0;
  double  mean;
  double  stdev;
  double  diff;

  while (index < 100) {
    data = Exponential(17);
    index++;
    diff  = data - mean;
    sum  += diff * diff * (index - 1.0) / index;
    mean += diff / index;
    stdev = sqrt(sum / index);
    printf("data ................. = %7.3f\n", data);
    printf("mean ................. = %7.3f\n", mean);
    printf("standard deviation ... = %7.3f\n", stdev);
    //printar informação ou escrever em arquivo aqui
  }


  return (0);
}
