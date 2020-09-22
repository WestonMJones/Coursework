#include <math.h>
#include <stdio.h>
#include <stdint.h>
#ifdef _OPENMP
#include <omp.h>
#include <time.h>
#endif /* _OPENMP */

#define END   100000000

// Only pass odd values to this function! :)
int is_prime(uint32_t v)
{
    uint32_t end = sqrt(v);
    for (uint32_t i = 3; i <= end; i += 2) {
        if ((v % i) == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{

    time_t start1, end1;
    clock_t start2, end2;

    start1 = time(NULL);
    start2 = clock();

    // We'll grab 2 as it's the only even prime
    int prime_count = 1;
    
    uint32_t bracket = 10;
    
    // Wow!  Quite a bit of parallel...
    // Maybe too much for one time!
    for (uint32_t i = 3; i < END; i += 2) {
        if (i > bracket) {
            printf("%12d\t%12d\n", bracket, prime_count);
            bracket *= 10;
        }
        if (is_prime(i)) {
            prime_count++;
        }
    }

    printf("%12d\t%12d\n", bracket, prime_count);

    end1 = time(NULL);
    end2 = clock();

    printf("Wall time taken was %lf\nCPU time taken was %lf\n",
    difftime(end1, start1), ((double)(end2-start2))/CLOCKS_PER_SEC);
    
    return 0;
}
