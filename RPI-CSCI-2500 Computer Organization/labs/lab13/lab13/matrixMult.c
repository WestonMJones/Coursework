#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define n 250

int main(int argc, char ** argv)
{
    int ** a;
    int ** b;
    int ** c;

    a = (int **) malloc(sizeof(int *)* n);
    b = (int **) malloc(sizeof(int *)* n);
    c = (int **) malloc(sizeof(int *)* n);

    for(int i = 0; i < n; i++) {
        a[i] = (int *) malloc(sizeof(int)*n);
        b[i] = (int *) malloc(sizeof(int)*n);
        c[i] = (int *) malloc(sizeof(int)*n);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            c[i][j] = 0;
            a[i][j] = b[i][j] = i;
        }
    }

    time_t start1, end1;
    clock_t start2, end2;

    start1 = time(NULL);
    start2 = clock();

    // A = n x m
    // B = m x p
    // C = n x p

    /*For i from 1 to n:
        For j from 1 to p:
            Let sum = 0
            For k from 1 to m:
                Set sum ← sum + Aik × Bkj
            Set Cij ← sum
    Return C*/

    //# pragma omp parallel num_threads(3)
    for (int i=0;i<n;i++) {
        # pragma omp parallel num_threads(3)
        for (int j=0;j<n;j++) {
            int sum = 0;
            //# pragma omp parallel num_threads(3)
            for (int k=0;k<n;k++) {
                sum = sum + (a[i][k]*b[k][j]);
            }
            c[i][j]=sum;
        }
    }

    end1 = time(NULL);
    end2 = clock();

    printf("Wall time taken was %lf\nCPU time taken was %lf\n",
           difftime(end1, start1), ((double)(end2-start2))/CLOCKS_PER_SEC);

    for(int i=0; i<n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}
