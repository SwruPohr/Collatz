#include <stdio.h>
#include <stdint.h>
#include <time.h>

static inline int collatz(unsigned __int128 n, unsigned __int128 THRESH) {
    if (n == 0) return 1;

    while (n != 1) {
        if ((n & 1) == 0) {
            n >>= 1;
        } else {
            if (n >= THRESH) return 1;
            n = 3 * n + 1;
        }
    }
    return 0;
}

static void print_u128(unsigned __int128 x) {
    if (x == 0) { putchar('0'); return; }

    char buf[64];
    int i = 0;
    while (x > 0) {
        unsigned __int128 q = x / 10;
        unsigned __int128 r = x - q * 10;
        buf[i++] = (char)('0' + (int)r);
        x = q;
    }
    while (i--) putchar(buf[i]);
}

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main(void) {
    unsigned __int128 MAX    = ~(unsigned __int128)0;
    unsigned __int128 THRESH = MAX / 3;
    
    unsigned __int128 LIMIT = ((unsigned __int128)1) << 24;
    
    
    if (LIMIT >= THRESH) return 1;
    print_u128(THRESH);
    printf("\n");
    print_u128(LIMIT);
    printf("\n");
    double t0 = now_seconds();

    for (unsigned __int128 n = 1; n < LIMIT; n++) {
        int value = collatz(n, THRESH);
        if (value) {
            printf("n=");
            print_u128(n);
            printf(" impossible\n");
        }
    }

    double t1 = now_seconds();
    printf("Time for n in [0, 2^20): %.6f seconds\n", (t1 - t0));
    return 0;
}
