
/*
 * 3.58
 *
 */
long decode2(long x, long y, long z) {
    return ((y - z) << 63 >> 63) ^ (x * y);
}

/*
 * 3.60
 */
long loop(long x, int n) {
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n) {
        result |= x & mask;
    }
    return result;
}

/*
 * 3.61
 */
//gcc -O1 -S asm.c
//static is necessary
//the previous code won't adopt a conditional data transfer strategy
//as it risks dereferencing a zero address
/*
 * ```
   cread_alt:
    .LFB2:
	.cfi_startproc
	endbr64
	testq	%rdi, %rdi
	leaq	zero.0(%rip), %rax  //static value use %rip as relative address
	cmove	%rax, %rdi
	movq	(%rdi), %rax
	ret
	.cfi_endproc
    ```
  */
long cread_alt(long *xp) {
    static long zero = 0;
    return *(xp ? xp : &zero);
}


/* 
 * 3.62
 */
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;
long siwtch3(long *p1, long *p2, mode_t action) {
    long result = 0;
    switch(action) {
        case MODE_A: 
            result = *p2;
            *p1 = *p2;
            return result;
        case MODE_B:
            result = *p1 + *p2;
            *p1 = result;
        case MODE_C:
            *p1 = 59;
            result = *p2;
            return result;
        case MODE_D:
            result = *p2;
            *p1 = result;
            result = 27;
            return result;
        case MODE_E:
            result = 27;
            return result;
        default:
            result = 12;
            return result;
    }
}

/*
 * 3.63
 */
long switch_prob(long x, long n) {
    //jmp table:
    //0x4006f8: 0x00000000004005a1
    //0x400700: 0x00000000004005c3
    //0x400708: 0x00000000004005a1
    //0x400710: 0x00000000004005aa
    //0x400718: 0x00000000004005b2
    //0x400720: 0x00000000004005bf

    //n: 60 ~ 65
    //\Delta n = 0 => 4005a1
    //\Delta n = 1 => 4005c3
    //\Delta n = 2 => 4005a1
    //\Delta n = 3 => 4005aa
    //\Delta n = 4 => 4005b2
    //\Delta n = 5 => 4005bf

    //when n > 5, jump to 4005c3
    //So instruction at 4005c3 is the default case

    long result = x;
    switch (n) {
        case 60:
        case 62:
            result *= 8;
            break;
        case 63:
            result >>= 3;
            break;
        case 64:
            result <<= 4;
            result -= x;
            x = result;
        case 65:
            x = x * x; 
        default:
            result = x + 75;
    }
    return result;
}


/* 
 * 3.64
 */
//We know that sizeof(A) = 3640 = R * S * T * 8
//For `long A[R][S][T]`, we can divide it as two parts: `A1[R][S]`, `A2[T]` (A2 = A1[R][S])
//then, since the index of `A1[i][j]` = S * i + j
//the index of `(A1[i][j])[k]` = (S * i + j) * T + k
//From the assembly code, we know that `index` = 65 * i + 13 * j + k
//So T * S = 65, T = 13, then S = 5
//as R * S * T = 3640 >> 3 = 455, then we know R = 7


