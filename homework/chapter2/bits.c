/* 
 * Bit-Level Integer Coding Rules
 * 
 * - Assumptions
 *   - Integers are represented in 2's-complement form
 *   - Right shifts of signed data are performed arithmetically.
 *   - Data type int is `w` bits long. For some of the problems, you will be given a specific value for `w`,
 *     but otherwise your code should work as long as w is a multiple of 8.
 *     You can use the expression `sizeof (int) << 3` to compute `w`
 *
 *  - Forbidden
 *   - Conditionals(`if` or `?:`), loops, switch statements, function calls, and macro invocations.
 *   - Division, modulus, and multiplication.
 *   - Relative comparison operators(`<`, `>`, `<=`, and `>=`)
 *
 *  - Allowed operations
 *   - All bit-level and logic operations
 *   - Left and right shifts, but only with shift amounts between 0 and `w - 1`.
 *   - Addition and subtraction.
 *   - Equality (==) and inequality (!=) tests. (Some of the problems do not allow these).
 *   - Integer constants INT_MIN and INT_MAX
 *   - Casting between data types int and unsigned, either explicitly or implicitly.
 */ 



/* 
 * 2.61 
 * Write C expressions that evaluate to 1 when the following conditions are true and to 0 when they
 * are false. Assume x is of type int. 
 * 
 * Note that your code should follow the bit-level integer coding rules, with the additional restriction
 * that you may not use equality (==) or inequality (!=) tests.
 * 
 * A. Any bit of x equals 1.
 * B. Any bit of x equals 0.
 * C. Any bit in the last significant byte of x equals 1.
 * D. Any bit in the last significant byte of x equals 0.
 * 
 */
int case_a(int x) {
    //switch x to bool
    return 0 || x;  
}

int case_b(int x) {
    //If any bit of x equals 0, then there exist bit of ~x equals 1, then do as what case_a do
    return 0 || ~x;  
}

int case_c(int x) {
    //we first use `x & 0xFF` to get the last significant byte of x, then do what case_a do
    return 0 || (x & 0xFF); 
}

int case_d(int x) {
    return 0 || ~(x & 0xFF);
}

/* 
 * 2.6.2
 * Write a function `int_shifts_are_arithmetic()` that yields 1 when run on a machine that uses
 * arithmetic right shifts for data type int and yields 0 otherwise.
 */
int int_shifts_are_arithmetic() {
    //We use ~0 to get 11111....11111, then we right shift it, denoting the result as x.
    //If the shift is logical, there must be zero digit in the binary representation of x, 
    //that means there exits digit equals to 1 in the binary representation of ~x
    //Otherwise, the shift must be arithmetic, ~x equals to 0
    return !~(~0 >> 1);
    //Another solution: return !(~0 ^ (~0 >> 1));
}

/* 2.63
 * Fill in code for the following C functions.
 * 
 * ```
 *  unsigned logical_right_shift(unsigned x, int k) {
        unsigned x_shift_arithemetically = ((int) x) >> k;
        //..
    }

    unsigned arithemetical_right_shift(int x, int k) {
        unsigned x_shift_logically = ((unsigned) x) >> k;
        //..
    }
    ```
 * Note that the code you fill in should not include right shifts or division.
 * You may use the computaion sizeof(int) << 3 to determine `w`.
 * The shift amount k can range from 0 to `w - 1`
 */
unsigned logical_right_shift(unsigned x, int k) {
    unsigned x_shift_arithemetically = ((int) x) >> k;
    //We need to get the mask 11111...00, where 1 occurs k times
    //Since that we are not allowed to use right shift, 
    //we can use left shift instead to get that value.
    //`mask & the given value` is the result 
    //Note that it is only allowed to shift value between 0 and w, we have to check whether
    //`w - k` will be `w`. So we have to check whether k = 0
    //If k != 0, we need the mask to be ~(~0 << (w - k));
    //Other wise the mask should be 0
    //but (0 || k) return 1 or 0, and `1` will affect the mask in unexpected way
    //To map the return value to ~0 and 0 respectively, we use (~(unsigned)(0 || k) + 1)
    int w = sizeof(int) << 3;
    unsigned mask = ((~(unsigned)(0 || k) + 1)) & ~(~0 << (w - k));
    return mask & x_shift_arithemetically;
}

unsigned arithemetical_right_shift(int x, int k) {
    unsigned x_shift_logically = (unsigned)x >> k;
    //The mask is the same as the function above
    //All we need to do is to return `mask | the given value` if x is negative
    //To determine whether x is negative, we need another mask 100...0
    //If x is negative, then the mask 1000...0 & x should not be zero
    //Since that it is only allowed to shift value between 0 and w, we have to check whether
    //`w - k` will be `w`. So we have to check whether k = 0
    //If x is negative and k != 0, we need the mask to be ~0 << (w - k)
    //Other wise the mask should be 0
    //but (k && x_is_negative) return 1 or 0, and `1` will affect the mask in unexpected way
    //To map the return value to ~0 and 1 respectively, we let it & 1111..0 
    int w = sizeof(int) << 3;
    int x_is_negative = (((unsigned)~0 << 1) & x) != 0;
    unsigned mask =  (~(unsigned)(k && x_is_negative) + 1) & (~0 << (w - k));
    return mask | x_shift_logically;
}


/*
 * 2.6.4
 * Write a function `int any_odd_one(unsigned x)` that returns 1 when any odd bit of x equals 1;
 * 0 otherwise. Your function should follow the bit-level integer coding rules, excect that you
 * may assume that data type int has `w` = 32 bits. 
 */
int any_odd_one(unsigned x) {
    //We group the bits of the binary representation of x by byte. A `5` in hex is `0101` in binary
    //Since `int` is 32-bits, each int value can be represented by 8 numbers of hex digits.
    //To determine whether any odd bit of x equals to 1, we can check whether there exist one byte of x that
    //has at least one odd digit equals to 1.
    //Thus we can solve this problem by checking whether `0x55555555 & x` has a `1` digit.
    return 0 || (0x55555555 & x);
}


/* 
 * 2.6.5
 * Write a function `int odd_ones(unsigned x)` that returns 1 when x contains an odd number of
 * `1`; 0 otherwise.
 * Assume that w = 32
 * Your code should contain a total of at most 12 arithmetic, bitwise, and logical operations
 */
int odd_ones(unsigned x) {
    //We calcaulate the xor conjunctions of each bit in x
    //If x has an odd numbers of `1`, the result will be 1, as 1 xor 1 = 0
    //Otherwise the result will be 0;
    //But the problem is how to implement that
    //We focus on the last bit of x, and use a accumulative xor strategy, this can work
    //thanks to the logical right shift and 0 xor any bit will be that bit
    x ^= x >> 16;  //w_0 = w_0 ^ w_16,  w_8 = w_8 ^ w_24, w_4 = w_4 ^ w_20, w_12 = w_12 ^ w_28
    x ^= x >> 8;   //w_0 = (w_0 ^ w_16) ^ (w_8 ^ w_24),  w_4 = (w_4 ^ w_20) ^ (w_12 ^ w_28)
    x ^= x >> 4;   //w_0 = (w_0 ^ w_16) ^ (w_8 ^ w_24) ^ (w_4 ^ w_20) ^ (w_12 ^ w_28)
    x ^= x >> 2;   //...
    x ^= x >> 1;
    return x & 0x1;  //Finally the w_0 has accumulated the xor conjunctions of every bit
}


/* 
 * 2.6.6
 * Write a function `int leftmost_one(unsigned x)` that returns mask indicating
 * leftmost 1 in x. Assume w = 32
 * For example, 0xFF00 -> 0x8000, and 0x6600 -> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x) {
    //Suppose the leftmost `1` is at (n-1)th bit to store x.
    //What we want is 2^{n-1} - 1. 
    //We can use 1 + 000..111..11 where 1 occurs `n - 1` times to get it
    //That is, we need to fill `n - 1` numbers of `1` into the rightmost of (int)0
    //To achieve this, we can first let x = x | (x >> 1), this append a `1` after the leftmost 1
    //Then we can let x = x | (x >> 2), we can do this as we know there is at least 1 number
    //of `1` after the leftmost `1`, this append two more `1` after the left most 1
    //Then we let x = x | (x >> 4), we get 4 more `1`
    //When we let x = x | (x >> 16), we have shift 32 times in sum, and it confirms that 
    //every bit after the leftmost `1` is `1`
    //But we have make assumption that x is not zero. If x is zero, after the or operations and
    //right shift operations, x will be still zero. But we add a additional 1 to x
    int bool_x = x && 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x = (x >> 1) + bool_x;
    return x;
} 


/*
 * 2.6.7
 * You are given a procedure `int int_size_is_32()` that yields 1 when
 * run on a machine for which an `int` is 32 bits, and yields 0 otherwise. Here is an attempt.
 * ```
 *   int bad_int_size_is_32() {
 *       int x = 1 << 31;
 *       int y = 1 << 32;
 *       return x && !y;
 * }
 * ```
 * The code above does not run properly on some machines 
 * as we know that if the value of the right operand of right shift is negative
 * or is greater than or equal to the size of the left operand, the behavior is undefined.
 * 
 * A. Try to modify the code to run properly on any machine for which data type `int` is at least 32 bits
 * B. Try to modify the code to run properly on any machine for which data type `int` is at least 16 bits
 */
int case_a_int_size_is_32() {
    int x = 1 << 31;
    int y = x << 1;
    return x && !y; 
}

int case_b_int_size_is_32() {
    int x = 1 << 15 << 15 << 1;
    int y = x << 1;
    return x && !y;
}



/* 
 * 2.6.8
 * Write a function `int lower_one_mask(int n)` with the following prototype:
 * 
 * ```
 *   Mask with least significant n bits set to 1
 *   Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 *   Assume 1 <= n <= w
 * 
 * ```
 * Your functions should follow the bit-level integer coding rules. Be careful of the case `n = w`
 */
int lower_one_mask(int n) {
    //The problem is about how to get `n` numbers of 1. 
    //We can first obtain 111...111 with ~0, then we let it logical right shift `w - n` bits,
    //this yields the value we want.
    //As we need logical right shift, we have to treat the type of ~0 as unsigned.
    //After all the operations, all we need is to transform the type back to int
    int w = sizeof(int) << 3;
    unsigned u = (unsigned) ~0;
    return (int)(u >> (w - n));
}


/* 
 * 2.6.9
 * Write a function `unsigned rotate_left(unsigned x, int n)` with the following prototype
 * 
 * ```
 * Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32: 
 *  n = 4 -> 0x2345781,
 *  n = 20 -> 0x67812345 
 * ```
 * 
 * Your function should follow the bit-level integer coding rules. Be careful of the case `n = 0`
 */
unsigned rotate_left(unsigned x, int n) {
    //The problem is how to compensate the loss bits after left shift.
    //To get bits that is to be sacrificed, we need a mask `1111..00`, where the numbers of `1` is `n`. 
    //We can get this mask by (~0) << (32 - n).
    //Then (mask & x) >> n yield the sacrifice value
    //And (x << n) plus that value is what we want
    //To avoid the case where n = 0 lead to `<< 32`, we use ( (~(unsigned)(0 || n)) + 1) 
    //that return ~0 if(n), and return 0 if (!n)
    int mask = (~(unsigned)(0 || n) + 1) & (~0 << (32 - n));
    int delta = (mask & x) >> n;
    return (x << n) + delta;
}


/* 
 * 2.7.0
 * Write a function `int fit_bits(int x, int n)` with the following prototype:
 * 
 * ```
 * Return 1 when x can be represented as an n-bit, 2's-complement number; 0 otherwise
 * Assume 1 <= n <= w
 * ```
 * 
 * Your function should follow the bit-level integer coding rules. 
 */
int fit_bits(int x, int n) {
    int w = sizeof(int) << 3;
    return (~(unsigned)(n != w) + 1) & !((unsigned)x >> n); 
}


/* 
 * 2.73
 * Write a function `int saturating_add(int x, int y)` that do addition saturates
 * to Tmin or Tmax
 * Your function should follow the bit-level integer coding rules. 
 */
int saturating_add(int x, int y) {
    int w = sizeof(int) << 3;
    int sum = x + y;
    int x_is_negative = x >> (w - 1);
    int y_is_negative = y >> (w - 1);
    int sum_is_negative = sum >> (w - 1);
    int x_is_positive = !x_is_negative && x;
    int y_is_positive = !y_is_negative && y;
    int sum_is_positive = !sum_is_negative && sum;

    int T_MAX = (unsigned)~0 >> 1;
    int T_MIN = ~T_MAX;

    int is_positive_overflow = x_is_positive && y_is_positive && (sum_is_negative || !sum);
    int is_negative_overflow = x_is_negative && y_is_negative && (sum_is_positive || !sum);

    int fix = 0;
    fix += (~(unsigned)is_positive_overflow + 1) & T_MAX;
    fix += (~(unsigned)is_negative_overflow + 1) & T_MIN;
    int need_fix = 0 || fix;
    return ((~(unsigned)need_fix + 1) & fix) + (sum & (~(unsigned)(!need_fix) + 1)); 
}


/*
 * 2.74
 * Write a function `int tsub_ok(int x, int y)` that yield 1 if (x - y) won't overflow
 * and 0 otherwise
 */
int tadd_ok(int x, int y) {
    int w = sizeof(int) << 3;
    int sum = x + y;
    int x_is_negative = x >> (w - 1);
    int y_is_negative = y >> (w - 1);
    int sum_is_negative = sum >> (w - 1);
    int x_is_positive = !x_is_negative && x;
    int y_is_positive = !y_is_negative && y;
    int sum_is_positive = !sum_is_negative && sum;

    int T_MAX = (unsigned)~0 >> 1;
    int T_MIN = ~T_MAX;

    int positive_overflow = x_is_positive && y_is_positive && (sum_is_negative || !sum);
    int negative_overflow = x_is_negative && y_is_negative && (sum_is_positive || !sum);
    return !positive_overflow && !negative_overflow;
}

int tsub_ok(int x, int y) {
    //The problem is equivalent to t_add_ok(x, -y), except for the case
    //where y = Tmin. In this case, -y = y = Tmin
    //So we need to check whether y = Tmin first
    int T_min = ~((unsigned)~0 >> 1);
    int y_equal_to_T_min = (y == T_min);
    return (~(unsigned)!y_equal_to_T_min + 1) & tadd_ok(x, -y);
}


/*
 * 2.7.8
 * Write a function `int divide_power2(int x, int k)` with the following prototype
 * 
 * ```
 * Divide by power of 2. Assume 0 <= k < w - 1
 * ```
 * 
 * The function should compute x / 2^{k} with correct rounding, and it should follow the bit-level
 * integer coding rules
 */  
int divide_power2(int x, int k) {
    //x / 2^{k} will be rounded down if x >= 0, and also rounded down if x < 0
    //but we expect it rounded up when x < 0, thus we need an offset(alka bias) `2^{k} - 1`
    //Since that we aren't allowed to use conditional statments, we can obtain the most significant bit
    //of x using x >> (w - 1), which represents whether x is negative
    //Then, if it is negative, we need to set bias as 2^{k} - 1, otherwise the bias should be zero
    //We can implement this by `int bias = (is_negative << k) - (is_negative & 1)` 
    int w = sizeof(int) << 3;
    int is_negative = x >> (w - 1);
    int bias = (is_negative << k) - (is_negative & 1);
    //int bias = (~is_negative + 1) & ((1 << k) - 1)
    return (x + bias) >> k;
}


/* 
 * 2.8.0
 * Write code for a function `int threefourths(int x)` that computes the value of (3/4)x,
 * rounded towards zero. It should not overflow. Your functions should follow the bit-level integer
 * coding rules
 */
int threefourths(int x) {
    //It is not feasible to do the division first and then do the multiplication
    //as it causes improper rounding.
    //We can convert (3/4)x into 1 - (1/4)x
    //So the problem lies in how to calculate -(1/4)x
    //Note that we have to round (3/4)x to zero, and i.e. we have to round -(1/4)x to zero
    //That means we have to round (1/4)x opposite to zero
    //We do this by add bias to (1/4)x when x is positive, rather than when x is negative.
    int w = sizeof(int) << 3;
    int x_is_positive = !(x >> (w - 1));
    int bias = (~x_is_positive + 1) & ((1 << 2) - 1); 
    int quarter = x >> 2;
    return 1 - (quarter + bias);
}


/* 
 * 2.81
 * Write C expressions to generate the bit patterns that follow, where a^{k} represents
 * k repetitions of symbol a. Assume the data type is `w`-bit
 * A. 1^{w-k}0^{k}
 * B. 0^{w-k-j}1^{k}0^{j}
 */
int case_a_pattern(int k) {
    return (unsigned)~0 << k;
}

int case_b_pattern(int k, int j) {
    return ~((unsigned)~0 << k) << j;
}


/* Supplementary Notes */

int int_val_is_negative(int x) {
    int w = sizeof(int) << 3;
    return x >> (w - 1);
    //Another solution:
    //  int sign_mask = ~((unsigned)~0 >> 1);
    //  return 0 || (x & sign_mask);
}


int if_x_then_y_else_0(int x, int y) {
    int bool_x = 0 || x;
    return (~bool_x + 1) & y;
}


int if_x_then_y_else_z(int x, int y, int z) {
    int bool_x = 0 || x;
    return ((~(unsigned)bool_x + 1) & y) + ((~(unsigned)(!bool_x) + 1) & z);
}


int is_int_sub_overflow(int, int);

int int_less_than(int x, int y) {
    int w = sizeof(int) << 3;
    int x_minus_y_is_negative = (x - y) >> (w - 1);
    return x_minus_y_is_negative ^ is_int_sub_overflow(x, y);
}


int is_int_add_overflow(int x, int y) {
    //Signed addition has overflowed if and only 
    //if x > 0 && y > 0 && x + y <= 0 
    //or if x < 0 && y < 0 && x + y >= 0
    int w = sizeof(int) << 3;
    int sum = x + y;
    int x_is_negative = x >> (w - 1);
    int y_is_negative = y >> (w - 1);
    int sum_is_negative = sum >> (w - 1);
    int x_is_positive = !x_is_negative && x;
    int y_is_positive = !y_is_negative && y;
    int sum_is_positive = !sum_is_negative && sum;

    int T_MAX = (unsigned)~0 >> 1;
    int T_MIN = ~T_MAX;

    int is_positive_overflow = x_is_positive && y_is_positive && (sum_is_negative || !sum);
    int is_negative_overflow = x_is_negative && y_is_negative && (sum_is_positive || !sum);
    return is_positive_overflow || is_negative_overflow;
}


int is_int_sub_overflow(int x, int y) {
    //If y == T_min, x - y is bond to overflow logically
    //But -y = T_min in fact 
    int T_min = ~(~(unsigned)0 >> 1);
    return y == T_min || is_int_add_overflow(x, -y);
}


//division allowed
int is_int_multiply_overflow(int x, int y) {
    //If y != 0 && (x * y) / y != x, then there is mutiply overflow
    int mult = x * y;
    return y != 0 && mult / y != x; 
}


//`<` allowed
int is_unsigned_add_overflow(unsigned x, unsigned y) {
    //If `x + y < x` (equivalent to `x + y < y`), then there is an unsigend addition
    //overflow 
    int sum = x + y;
    return sum < x;
}


//`<` allowed
int is_unsigned_sub_overflow(unsigned x, unsigned y) {
    return x < y;
}


//division allowed
int is_unsigned_multiply_overflow(unsigned x, unsigned y) {
    int mult = x * y;
    return is_int_multiply_overflow((int)x, (int)y);
}


