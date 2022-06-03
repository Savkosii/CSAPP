/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //~(~x ~y): , yields bit `0` if and only if both corresponding bits of x and y are `0`,
  //equivalent to `|`
  //~(x & y): yields bit `0` if and only if both corresponding bits of x and y are `1`
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int max = ~(1 << 31);
  return !(x ^ max);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  x &= x >> 16;
  x &= x >> 8;
  x &= x >> 4;
  x &= x >> 2;
  int mask = 0x2;
  return !!(x & mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int minus_0x30 = ~0x30 + 1;
  int minus_0x39 = ~0x39 + 1;
  int sign_mask = 1 << 31;
  int x_sub_0x30 = x + minus_0x30;
  int x_sub_0x39 = x + minus_0x39;
  int x_greq_0x30 = !(x_sub_0x30 & sign_mask); 
  int x_leq_0x39 = (!x_sub_0x39) | !!(x_sub_0x39 & sign_mask);
  return x_greq_0x30 & x_leq_0x39;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int bool_x = !!x;
  int bool_not_x = !x;
  return (y & (~bool_x + 1)) + (z & (~bool_not_x + 1));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sig_mask = 1 << 31;
  int x_not_neg = !(x & sig_mask);
  int y_not_neg = !(y & sig_mask);
  int x_neg_but_y_not =  y_not_neg & !x_not_neg; 
  int y_neg_but_x_not = x_not_neg & !y_not_neg;
  int minus_y = ~y + 1;
  int x_sub_y = x + minus_y;
  int x_sub_y_not_neg = !(x_sub_y & sig_mask);
  int x_sub_y_leq_0 = (!x_sub_y_not_neg) | (!x_sub_y);
  return (!y_neg_but_x_not) & (x_neg_but_y_not | x_sub_y_leq_0);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //It is not the point whether x is negative or not.
  //As `!` only care about the bits.
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;
  //13 ops solution: return ~(x & 0x1) + 2;
  return (x & 0x1) ^ 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //If x = 0 or x = -1, howManyBits(x) = howManyBits(0) = 1, not 2;
  //If x is positive, let `k` be the index of the leftmost `1` bit of x,
  //then howManyBits(x) = k + 2;
  //If x is negative but not -1, let `k` be the index of the leftmost `0` bit of x,
  //then howManyBits(x) = k + 2. 
  int sign_mask = 0x1 << 31;
  int x_not_neg = !(x & sign_mask); 
  int x_is_neg = !x_not_neg;
  int offset = 2;
  //If `x` is negative, we can convert it to the case where `x` is not negative
  //by assignment `x = ~x`.
  x = ((~x_is_neg + 1) & (~x)) + ((~x_not_neg + 1) & x);
  //If now x is zero, we map it to 1, and map the initial offset `2` into 1. 
  //This include the case where x is originally -1 and is converted into 0 by ~x.
  int x_is_zero = !x;
  int x_not_zero = !x_is_zero;
  x = ((~x_not_zero + 1) & x) + ((~x_is_zero + 1) & 1);
  offset = ((~x_not_zero + 1) & offset) + ((~x_is_zero + 1) & 1);
  //All we need then is to get the mask of the leftmost `1` of x
  //and figure out its index.
  //As we have mapped the original `x` into positive integer, we can regard
  //the arithematic right shift as a logical one, and thus it is straight forward
  //to get the mask of the leftmost `1`. 
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x = (x >> 1) + 1;
  //Finding the index of the leftmost 1 
  //is equivalent to get log2(x) where x = 1 << k.

  //bits_shift: numbers of bits that x needs to right shift to be 0x1, equal to log2(x)
  //For example, log2(1) = 0; log2(2) = 1;
  int bits_shift = 0;
  //need_shift: numbers of bits shift in the current round.
  int need_shift = 0;
  //Initially, x has 32 bits that we need to consider. 
  //If the bit `1` lies in the higher 16 bits of x, x >>= 16.
  //Otherwise x = x
  need_shift = !!(x >> 16) << 4;
  x >>= need_shift;
  bits_shift += need_shift;
  //Now we only need to consider the lower 16 bits of x, denoted as x16_t.
  //If the bit `1` lies in the higher 8 bits of x16_t, x >>= 8.
  //Otherwise x = x
  need_shift = !!(x >> 8) << 3;
  x >>= need_shift;
  bits_shift += need_shift;
  //Similarly, we now consider x8_t.
  //If the bit `1` lies in the higher 4 bits of x8_t, x >>= 4.
  //Otherwise x = x
  need_shift = !!(x >> 4) << 2;
  x >>= need_shift;
  bits_shift += need_shift;
  //...
  need_shift = !!(x >> 2) << 1;
  x >>= need_shift;
  bits_shift += need_shift;
  //As for x2_t, if the bit `1` lies in the lower bit, we have got 0x1 
  //Otherwise we need `x >> 1` to obtain 0x1
  need_shift = !!(x >> 1);
  x >>= need_shift;
  bits_shift += need_shift;
  return offset + bits_shift;
}

/* Note: float labs omitting */