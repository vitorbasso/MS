
/* -------------------------------------------------------------------------
 * Name            : rng.h  (header file for the library file rng.c)
 * Author          : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 09-11-98
 * -------------------------------------------------------------------------
 */
#ifndef RNG_H_INCLUDED
#define RNG_H_INCLUDED

#if !defined( _RNG_ )
#define _RNG_

double Random(void);
void   GetSeed(long *x);
void   PutSeed(long x);
void   TestRandom(void);

#endif


#endif // RNG_H_INCLUDED
