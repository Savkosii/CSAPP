#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNKNOWN 0xffffffff

int string_length(char *);
int strings_not_equal(char *, char *);
int read_six_numbers(char *, int *);
char *read_line();

void explode_bomb() {
    char *str_0x4025a3 = "BOOM!!!";
    char *str_0x4025ac = "The bomb has blown up";
    puts(str_0x4025a3);
    puts(str_0x4025ac);
    exit(8);
}

//%rdi: char *input
void phase_1(char *input) {
    char *str_0x402400 = "Border relations with Canada have never been better.";
    if (strings_not_equal(input, str_0x402400)) {
        explode_bomb();
    }
    //payload: Border relations with Canada have never been better.
}

//%rdi: char *input
void phase_2(char *input) {
    int buf[6];
    read_six_numbers(input, buf);
    if (buf[0] != 1) {
        explode_bomb();
    } 
    for (int i = 1; i != 6; i++) {
        if (buf[i - 1] * 2 != buf[i]) {
            explode_bomb();
        }
    }
    //payload: 1 2 4 8 16 32
}


//%rdi: char *input 
int phase_3(char *input) {
    int buf[6];
    //.rodata: 0x4025cf
    //25 64 20 25 64 00 -> "%d %d"
    char *str_0x4025cf = "%d %d";
    if (sscanf(input, str_0x4025cf, buf + 2, buf + 3) <= 1) {
        explode_bomb();
    }
    //jmp *0x402470 + buf[2] * 8
    //.rodata: 0x402470 (little endian):
    //402470  7c0f4000 00000000
    //402478  b90f4000 00000000
    //402480  830f4000 00000000
    //402488  8a0f4000 00000000
    //402490  910f4000 00000000 
    //402498  980f4000 00000000
    //4024a0  9f0f4000 00000000
    //4024a8  a60f4000 00000000
    int target;
    switch (buf[2]) {
        case 0: //0x400f7c
            target = 0xcf; break;
        case 1: //0x400fb9
            target = 0x137; break; 
        case 2: //0x400f83
            target = 0x2c3; break;
        case 3: //0x400f8a
            target = 0x100; break;
        case 4: //0x400f91
            target = 0x185; break;
        case 5: //0x400f98
            target = 0xce; break;
        case 6: //0x400f9f
            target = 0x2aa; break;
        case 7: //0x400fa6
            target = 0x147; break;
        default:
            explode_bomb();
            target = 0;
    }
    if (target != buf[3]) {
        explode_bomb();
    }
    return target;
    //payload: 0 207
}


//%edi: int x; %esi: int y; %edx: int z
int func4(int x, int y, int z) {
    unsigned int a = z - y;
    a += a >> 0x1f;
    //sar %eax
    a >>= 1;
    unsigned int c = a + y;
    if (c > x) {
        return 2 * func4(x, y, c - 1);
    } else if (c < x) {
        return 2 * func4(x, c + 1, z) + 1;
    } else {
        return 0;
    }
}

//%rdi: char *input
int phase_4(char *input) {
    int buf[6];
    char *str_0x4025cf = "%d %d";
    if (sscanf(input, str_0x4025cf, buf + 2, buf + 3) != 2) {
        explode_bomb();
    }
    if (buf[2] > 0xe) {
        explode_bomb();
    }
    int res = func4(buf[2], 0, 0xe);
    if (res != 0 || buf[3] != 0) {
        explode_bomb();
    }
    return res;
    //payload: 0 0
}

//%rdi: char *input
int phase_5(char *input) {
    //sub $0x20, %rsp
    //%fs: a data segment register
    //%fs:0x28: stack guard value(stored in memory)
    char buf[24];
    /* buf[24] = %fs:0x28 */

    if (string_length(input) != 6) {
        explode_bomb();
    }
    char bytes_0x4024b0[] = 
        {'m','a','d','u','i','e','r','s','n','f','o','t','v','b','y','l'};
    for (int i = 0; i != 6; i++) {
        buf[0] = input[i];
        buf[16 + i] = bytes_0x4024b0[input[i] & 0xf];
    }
    buf[22] = 0;
    char *str_0x40245e = "flyers";
    if (strings_not_equal(buf + 16, str_0x40245e)) {
        explode_bomb();
    }
    /*
     * if (buf[24] != %fs:0x28) {
     *     stack_chk_fail();
     * }
     */
    return 0;
    /*
     * exp:
     *  ```python
     *   bytes_list = ['m','a','d','u','i','e','r','s','n','f','o','t','v','b','y','l']
     *   target = "flyers"
     *   for c in target:
     *       index = bytes_list.index(c)
     *       for i in range(33, 127):
     *           if i & 0xf == index:
     *               print(chr(i), end="")
     *               break
     *   ```
     */

    //payload: )/.%&'
}

struct node {
    int val;
    int id;
    struct node *next;
};

struct node node1_0x6032d0 = {
    (int)0x14c,
    (int)0x1,
    (struct node*)0x6032e0,
};

struct node node2_0x6032e0 = {
    (int)0xa8,
    (int)0x2,
    (struct node*)0x6032f0,
};

struct node node3_0x6032f0 = {
    (int)0x39c,
    (int)0x3,
    (struct node*)0x603300,
};

struct node node4_0x603300 = {
    (int)0x2b3,
    (int)0x4,
    (struct node*)0x603310,
};

struct node node5_0x603310 = {
    (int)0x1dd,
    (int)0x5,
    (struct node*)0x603320,
};

struct node node6_0x603320 = {
    (int)0x1bb,
    (int)0x6,
    (struct node*)NULL,
};

//%rdi: char *input
void phase_6(char *input) {
    //sub $0x50 %rsp
    int buf[6];
    //buf2: %rsp + 0x18
    void *buf2;
    //buf3: %rsp + 0x20
    struct node *buf3[6];
    read_six_numbers(input, buf);
    for (int *p = buf, n = 0; n < 6; p++, n++) {
        if (*p - 1 > 5) {
            explode_bomb();
        }
        for (int k = n + 1; k < 6; k++) {
            if (buf[k] == *p) {
                explode_bomb();
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        buf[i] = 7 - buf[i];
    }

    //0x401197
    //i: %rsi / 4
    for (int i = 0; i < 6; i++) {
        //0x401183
        struct node *rdx = &node1_0x6032d0;
        if (buf[i] > 1) {
            //0x401176
            //k: %eax
            for (int k = 1; k < buf[i]; k++) {
                rdx = rdx->next;
            }
        }
        //0x401188
        buf3[i] = rdx;
    }

    //0x4011ab
    struct node *rbx = buf3[0];
    //0x4011ba
    struct node *rcx = rbx;
    //0x4011bd
    for (int i = 1; 1; i++) {
        rcx->next = buf3[i];
        if (i == 5) {
            break;
        }
        rcx = rcx->next;
    }

    //0x4011d2
    //48 c7 42 08 00 00 00  movq $0x8(%rdx)
    buf3[5]->next = NULL;
    for (int n = 5; n != 0; n--) {
        //mov 0x8(%rbx),%rax => rax = rbx->next
        //mov (%rax),%eax => eax = rax->val
        //cmp %eax,(%rbx) => cmp (rbx->val, eax)
        if (rbx->next->val > rbx->val) {
            explode_bomb();
        }
        rbx = rbx->next;
    }

    //path: 0x39c -> 0x2b3 -> 0x1dd -> 0x1bb -> 0x14c -> 0xa8
    //payload: 4 3 2 1 6 5
}

struct st {
    long val;
    struct st *next1;
    struct st *next2;
};

struct st n1_0x6030f0 = {
    (long)0x24,
    (struct st*)0x603110,
    (struct st*)0x603130,
};

struct st n21_0x603110 = {
    (long)0x8,
    (struct st*)0x603190,
    (struct st*)0x603150,
};

struct st n22_0x603130 = {
    (long)0x32,
    (struct st*)0x603170,
    (struct st*)0x6031b0,
};

struct st n31_0x603190 = {
    (long)0x6,
    (struct st*)0x6031f0,
    (struct st*)0x603250,
};

struct st n32_0x603150 = {
    (long)0x16,
    (struct st*)0x603270,
    (struct st*)0x603230,
};

struct st n33_0x603170 = {
    (long)0x2d,
    (struct st*)0x6031d0,
    (struct st*)0x603290,
};

struct st n34_0x6031b0 = {
    (long)0x6b,
    (struct st*)0x603210,
    (struct st*)0x6032b0,
};

struct st n41_0x6031f0 = {
    (long)0x1,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n42_0x603250 = {
    (long)0x7,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n43_0x603270 = {
    (long)0x14,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n44_0x603230 = {
    (long)0x23,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n45_0x6031d0 = {
    (long)0x28,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n46_0x603290 = {
    (long)0x2f,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n47_0x603210 = {
    (long)0x63,
    (struct st*)NULL,
    (struct st*)NULL,
};

struct st n48_0x6032b0 = {
    (long)0x3e9,
    (struct st*)NULL,
    (struct st*)NULL,
};

int fun7(struct st *x, int y) {
    if (x == NULL) {
        return -1;
    }
    if (x->val < y) {
        return 2 * fun7(x->next2, y) + 1;
    } else if (x->val == y) {
        return 0;
    } else {
        return 2 * fun7(x->next1, y);
    }
}

void phase_defused();
void secret_phase() {
    long val = strtol(read_line(), 0, 10);
    if ((int)(val - 1) > 0x3e8) {
        explode_bomb();
    }
    if (fun7(&n1_0x6030f0, (int)val) != 2) {
        explode_bomb();
    }
    puts("Wow! You've defused the secret stage!");
    phase_defused();
    //path: 0x24 -> 0x8 -> 0x16
    //payload: 22  (not used)
}

char *input_strings_0x603780 = 0;
int num_input_strings = 0;

void phase_defused() {
    if (num_input_strings != 6) {
        return;
    }
    int x, y;
    char buf[UNKNOWN];
    char *str_0x603870 = input_strings_0x603780 + 0xf0;
    //0x603780 +   0: The border...
    //0x603780 +  80: 1 2 4 8 16 32
    //0x603780 + 160: 0 207
    //0x603780 + 240: 0 0
    //0x603780 + 320: )/%&
    //0x603780 + 360: 4 3 2 1 6 5
    int res = sscanf(str_0x603870, "%d %d %s", &x, &y, buf);
    if (res == 3) {
        if (!strings_not_equal(buf, "DrEvil")) {
            puts("Curses, you've found the secret phase!");
            puts("But finding it and solving it are quite different");
            secret_phase();
        }
    }
    puts("Congratulations! You've defused the bomb!");
}

FILE *infile;

int blank_line();
char * skip() {
    char *buf = input_strings_0x603780 + num_input_strings * 80;
    char *res;
    if ((res = fgets(buf, 80, infile)) == NULL) {
        return NULL;
    }
    if (blank_line(res)) {
        return skip();
    }
    return res;
}

char *read_line() {
    if (skip() != NULL) {
        addr_0x40151f: {
            char *rsi = input_strings_0x603780 + num_input_strings * 80;
            /* 
              mov $0xffffffffffffffff,%rcx
              repnz scas %es:(%rdi),%al 
                => 
                  size_t rcx = (size_t)-1;
                  char *s = rdi;
                  while (*s++ != '\0') rcx--;
                  rcx = ~rcx;
                  rcx -= 1;
            */
            size_t rcx = strlen(rsi);  //equivalent form

            if ((int)rcx > 0x4e) {
                puts("Error: Input line too long");
                // *(long *)(input_strings_0x603780 + offset) = 0x636e7572742a2a2a;
                // *(long *)(input_strings_0x603780 + offset + 8) = 0x2a2a2a64657461;

                // memcpy(input_strings_0x603780 + offset, 
                // "\x2a\x2a\x2a\x74\x72\x75\x6e\x63""\x61\x74\x65\x64\x2a\x2a\x2a", 15)
                memcpy(rsi + 80, "***truncated***", 15);  //equivalent form
                explode_bomb();
            } 
            rcx -= 1;
            //erase the '\n'
            *(rsi + rcx) = '\0';
            num_input_strings++;
            return rsi;
        }
    } else {
        if (infile == stdin) {
            puts("Error: Premature EOF on stdin");
            exit(8);
        } else {
            if (getenv("GRADE_BOMB") == NULL) {
                infile = stdin;
                if (skip() == NULL) {
                    puts("Error: Premature EOF on stdin");
                    exit(0);
                } else {
                    goto addr_0x40151f;
                }
            } else {
                exit(0);
            }
        }

    }
}

int __printf_chk(int flag, char *, char *);
void invalid_phase(char *s) {
    __printf_chk(1, "Invalid phase%s", s);
    exit(8);
}

void signal(void *, int);
void initialize_bomb() {
    signal((void *)0x4012a0, 2);
}


int main(int argc, char *argv[]) {
    if (argc == 1) {  
	    infile = stdin;
    }  else if (argc == 2) {
	    if (!(infile = fopen(argv[1], "r"))) {
	        printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	        exit(8);
	    }
    } else {
	    printf("Usage: %s [<input_file>]\n", argv[0]);
	    exit(8);
    }

    char *input;
    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    input = read_line();
    phase_1(input);
    phase_defused();
    printf("Phase 1 defused. How about the next one?\n");
    
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");
    
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the next...\n");

    input = read_line();
    phase_6(input);
    phase_defused();

    return 0;
}