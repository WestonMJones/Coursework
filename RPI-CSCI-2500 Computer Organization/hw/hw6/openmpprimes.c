#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#define END   100000000

// Only pass odd values to this function! :)
// I used the same function to determine if a number was prime or not
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

    // Keep track of the time for comparison of performance
    time_t start1, end1;
    clock_t start2, end2;

    start1 = time(NULL);
    start2 = clock();

    // Subdivide the prime count into 8 chunks --those values less than 10, less than 100, 
    // less than 1000, etc
    int * prime_count = calloc(8,sizeof(int));

    // Initalize those chunks
    for (int i=0;i<7;i++) {
        prime_count[i]=0;
    }

    // We'll grab 2 as it's the only even prime
    prime_count[0]++;
    
    // Do the for loop in parallel
    #pragma omp parallel for
    for (uint32_t i = 3; i < END; i += 2) {

        // Use logs to correctly calculate which chunk the current i value falls in.
        int index = ceil(log10(i+1))-1;

        // Make a local copy
        int local = is_prime(i);

        // Update the global count with critical designation to avoid bottlenecks
        #pragma omp critical
        prime_count[index]+=local;

    }

    // The rest of the code is just formatting

    // Initialize bracket to 1 so we can do everything in one loop
    int bracket = 1;

    // Loop through the prime_count array
    for (int i=0;i<7;i++) {

        // Make each chunk cumulative -- including the number of primes in previous chunks
        if (i!=0) {
            prime_count[i]+=prime_count[i-1];
        }

        // Update the bracket and print
        bracket = bracket * 10;
        printf("%12d\t%12d\n", bracket, prime_count[i]);
    }

    // Print out performance results
    end1 = time(NULL);
    end2 = clock();

    printf("Wall time taken was %lf\nCPU time taken was %lf\n",
    difftime(end1, start1), ((double)(end2-start2))/CLOCKS_PER_SEC);

    // The original code takes about 90 seconds to run
    // My code without OpenMP takes about 98 seconds to run
    // My code with OpenMP takes about 35 seconds to run

    return 0;
}
