/*
 * CS:APP Data Lab
 *
 * Noah Hanks, nhanks10
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
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
/*
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
    return ~(1 << 31); // Shifts 1 to the leftmost bit - 1 then bitwise not to get 0x7FFFFFFF.
}
/*
 * fitsShort - return 1 if x can be represented as a
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
    int y = x >> 15; // y is equal to x / 2^15
    return !y | !~y; // If y is all 0s, returns 1. 0 otherwise.
}
// Level 2
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    int y = 0x55 + (0x55 << 8) + (0x55 << 16) + (0x55 << 24); // Adds and shifts to get 0x55555555.
    return !!(x & y); // AND and then NOT NOT to get 1 if any even bit is set, 0 if not.
}
/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
    return 0xAA + (0xAA << 8) + (0xAA << 16) + (0xAA << 24); // Adds and shifts to get 0xAAAAAAAA.
}
/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    return !(x ^ y); // XOR to check if bits differ. If value has a 1 in any bit, returns 0 due to
                     // NOT. 1 otherwise.
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int isNeg = x >> 31;                // Shifts x 31 bits to tell if x is negative.
    int y = ((isNeg & 1) << n) + isNeg; // If x is negative, y is 2^n - 1. 0 otherwise.
    return (x + y) >> n;                // Adds y to x and then shifts x n bits to the right.
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int normalN = 33 + ~n;             // Makes y between 1 and 32.
    int y = (x << normalN) >> normalN; // Shifts x n bits to the left and then right to truncate.
    return !(x ^ y);                   // Does the same thing as isEqual.
}
// Level 3
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    int y = ((x << 1) + x);   // Multiplies by 3.
    int signBit = y >> 31;    // Shifts y 31 bits to find leftmost bit.
    int bias = 0x3 & signBit; // If y is negative, bias is 3. 0 otherwise.
    return ((y + bias) >> 2); // Adds bias and then shifts y 2 bits to the right.
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int mask = (!x + ~0x00);               // If x is 0, mask is 0xffffffff. 0 otherwise.
    return ((((mask)&y) | ((~mask) & z))); // If x is 0, returns z. y otherwise.
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    int negativeOne = ~0;                        // -1
    int lowNum = negativeOne << lowbit;          // 1s to the left of lowbit.
    int highNum = (negativeOne << highbit) << 1; // 1s to the left of highbit.
    return (highNum ^ lowNum) &
           lowNum; // XORs highNum and lowNum to get 1s between highbit and
                   // lowbit. ANDs with lowNum to get 1s to the right of lowbit.
}
// Level 4
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
    int sum = x + y; // Adds x and y.
    int overflowBit =
        ((sum ^ x) & (sum ^ y)) >>
        31; // Checks if there is an overflow by ANDing the values of XORing the sum with x and y.
    return (sum >> (overflowBit & 31)) +
           (overflowBit << 31); // If there is an overflow, returns the
                                // maximum or minimum value. Negative overflow returns minumum and
                                // positive returns maximum. Otherwise, returns the sum.
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {

    int absValue = x;
    unsigned result = 0;
    int signBit = x & 0x80000000; // Gets the sign bit.

    int exponent = 0x7f; // Exponent starts at 127.
    int absValueCopy, lastBit, mask, maskedAbsValue;
    int shift1, shift2, shift3, value1, value2, value3, subtotal;

    switch (x) { // Checks for special cases.
    case 0:
        return 0;
    case 0x80000000:
        return 0xcf000000;
    default:
        break;
    }

    absValue = signBit ? -x : x; // Get absolute value.
    result |= signBit;           // Put the sign bit on the result.

    absValueCopy = absValue; // Creates a copy for the while loop.
    while (absValueCopy /= 2)
        exponent += 1; // Get the exponent.

    lastBit = exponent - 0x7f;          // Get the last bit.
    mask = (1 << lastBit) - 1;          // Shifts the lastBit and subtracts one to get the mask.
    maskedAbsValue = (mask & absValue); // ANDs the mask with the absolute value.
    shift1 = 23 - lastBit;              // Shifts the last bit 23 bits to the left.
    if (lastBit < 24)                   // Checks if there is less than 24 bits.
        result += (maskedAbsValue
                   << shift1); // Shifts the masked absolute value by the first shift calculated.
    else {
        shift2 = -shift1;           // Shifts the first shift by -1.
        shift3 = 1 << (shift2 - 1); // Shifts the first shift by -2.
        value1 = maskedAbsValue &
                 (shift3 - 1); // ANDs the masked absolute value with the second shift - 1.
        value2 = maskedAbsValue & (1 << (shift2)); // ANDs the masked absolute value with the
                                                   // second shift.
        value3 = maskedAbsValue & shift3; // ANDs the masked absolute value with the second shift
                                          // - 1.
        subtotal =
            maskedAbsValue >> shift2; // Shifts the masked absolute value by the second shift.
        subtotal += (value3 && (value1 || value2)); // Adds the third value and the second value
                                                    // to the subtotal.
        result |= subtotal;
    }

    return result + (exponent << 23); // Put the exponent on the result.
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    return (((~x + 1) | x) >> 31) + 1; // If x is 0, returns 1. 0 otherwise.
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x) {
    int divByEight = x >> 3; // x / 8
    int remainder = x & 7;   // x % 8
    int mask = x >> 31 & 7;  // 0 if x is positive, 7 if x is negative.
    int divByEight_timesFive = divByEight + (divByEight << 2); // x / 8 * 5
    int remainder_timesFive = remainder + (remainder << 2);    // x % 8 * 5

    return divByEight_timesFive +
           ((remainder_timesFive + mask) >> 3); // x / 8 * 5 + (x % 8 * 5 + 7) / 8
}
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    int sign = x >> 31;       // mask = 0xffffffff if x is negative, 0 otherwise.
    return (x + sign) ^ sign; // if x is negative, x + sign is 0. if x is positive, x + sign is x.
}
// Should be 15 puzzles, 2 level 1 puzzles, 5 level 2 puzzles, 3 level 3 puzzles, 5 level 4
// puzzles
