/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
// W 2020 Selection  //
///////////////////////
// Level 1
int test_tmax(void) {
  return 0x7FFFFFFF;
}
int test_fitsShort(int x)
{
  short int sx = (short int) x;
  return x == sx;
}
// Level 2
int test_anyEvenBit(int x) {
  int i;
  for (i = 0; i < 32; i+=2)
      if (x & (1<<i))
   return 1;
  return 0;
}
int test_oddBits(void) {
  int result = 0;
  int i;
  for (i = 1; i < 32; i+=2)
    result |= 1<<i;
  return result;
}
int test_isEqual(int x, int y)
{
  return x == y;
}
int test_divpwr2(int x, int n)
{
    int p2n = 1<<n;
    return x/p2n;
}
int test_fitsBits(int x, int n)
{
  int TMin_n = -(1U << (n-1));
  int TMax_n = (1U << (n-1)) - 1;
  return x >= TMin_n && x <= TMax_n;
}
// Level 3
int test_ezThreeFourths(int x)
{
  return (x*3)/4;
}
int test_conditional(int x, int y, int z)
{
  return x?y:z;
}
int test_bitMask(int highbit, int lowbit)
{
  int result = 0;
  int i;
  for (i = lowbit; i <= highbit; i++)
    result |= 1 << i;
  return result;
}
// Level 4
int test_satAdd(int x, int y)
{
  if (x > 0 && y > 0 && (int)((unsigned)x + (unsigned)y) < 0)
    return (0x7FFFFFFF);
  if (x < 0 && y < 0 && (int)((unsigned)x + (unsigned)y) >= 0)
    return (0x80000000);
  return x + y;
}
unsigned test_float_i2f(int x) {
  float f = (float) x;
  return f2u(f);
}
int test_bang(int x)
{
  return !x;
}
int test_trueFiveEighths(int x)
{
  return (int) (((long long int) x * 5)/8);
}
int test_absVal(int x) {
  return (x < 0) ? -x : x;
}
// Should be 15 puzzles, 2 level 1 puzzles, 5 level 2 puzzles, 3 level 3 puzzles, 5 level 4 puzzles
