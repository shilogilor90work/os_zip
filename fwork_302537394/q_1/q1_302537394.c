#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. Where is allocated?  Uninitialized data segment – bss - global */
int primes[] = { 2, 3, 5, 7 };  /* 2. Where is allocated? Initialized data segment. – data - global */

static int
square(int x)                   /* 3. Where is allocated? Allocated in frame for square() – text - local*/
{
    int result;                 /* 4. Where is allocated? Allocated in frame for square() – stack frame, in square function*/

    result = x * x;
    return result;              /* 5. How the return value is passed? Return value passed via register*/
}

static void
doCalc(int val)                 /* 6. Where is allocated? Allocated in frame for doCalc() – text - local*/
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. Where is allocated? Allocated in frame for doCalc() – stack frame, in doCalc function*/

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /*8. Where is allocated? Allocated in frame for main() – text - global*/
{
    static int key = 9973;      /*9. Where is allocated? Initialized data segment – data - local */
    static char mbuf[10240000]; /*10. Where is allocated? Uninitialized data segment – bss - local */
    char* p;                    /*11. Where is allocated? Allocated in frame for main() - Uninitialized */


    doCalc(key);

    exit(EXIT_SUCCESS);
}
