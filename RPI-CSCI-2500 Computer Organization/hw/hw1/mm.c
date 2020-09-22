/*****************************************************************************/
/* Assignment 1: 2-D/ Matrix Multiplication **********************************/
/* Name: Weston Jones ********************************************************/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int **mm_alloc( int rows, int columns )
{
    /*
     * hints: allocate an array of pointers to ints, then allocate
     * an row/array of ints and assign each int pointer that row
     * see slide 62
     */

    // Allocate space for the "rows" of the matrix
    int ** matrix = (int **)calloc(rows,sizeof(int *));

    // Allocate space for each "column" of the matrix
    for (int i=0;i<rows;i++) {
        // Each of the "row" pointers points to another array of ints
        matrix[i] = (int *)calloc(columns,sizeof(int));
    }
    return matrix;
}

void mm_free( int **matrix, int rows, int columns )
{
    // Delete all pointers, starting from the lowest level up
    int r;

    // delete each "row" pointer first
    for (r=0;r<rows;r++) {
        free(matrix[r]);
    }

    // Delete the original pointer
    free(matrix); 
}

void mm_read( int **matrix, int rows, int columns )
{
    printf("Please enter the values for the %d x %d matrix:\n",rows, columns );
    int r,c;
    // loop through rows then columns
    for (r=0;r<rows;r++) {
        for (c=0;c<columns;c++) {
            // fill in the matrix
            scanf("%d",&matrix[r][c]);
        }
    }
}

void mm_print( int **matrix, int rows, int columns )
{
    int r,c;
    // loop through rows then columns
    for (r=0;r<rows;r++) {
        for (c=0;c<columns;c++) {
            // output the value of the current cell
            printf("%d ", matrix[r][c] );
        }
        // skip to a new line after every rows
        printf("\n");
    }
}

void mm_mult( int **m1, int m1_rows, int m1_cols,
              int **m2, int m2_rows, int m2_cols,
              int **results)
{

    // Algorithm I got from the wikipedia page linked in the HW pdf
    /*
    First = n x m
    Second = m x p
    Result = n x p

    for i = 0 to n
     for j = 0 to p
     result [i][j] = 0
      for k = 0 to m
       result[i][j] += first[i][k]*second[k][j]
    */

    int i,j,k;
    // For every row in the first matrix...
    for (i=0;i<m1_rows;i++) {
        // Loop through the column in the second matrix
        for (j=0;j<m2_cols;j++) {
            // Initialize the result matrix cell with placeholder value
            results[i][j] = 0;
            // Get values from the current row of first matrix and current column of second
            for (k=0;k<m1_cols;k++) {
                // Add the product of each corresponding row and column value to current sum
                results[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
  
}

int main()
{
    /*
     * You must keep this function AS IS.
     * You are not allowed to modify it!
     */
    int **matrix1 = NULL;
    int **matrix2 = NULL;
    int **results_matrix = NULL;

    int m1_rows, m1_columns;
    int m2_rows, m2_columns;

    printf("How many rows are in the first matrix? \n");
    scanf("%d", &m1_rows);
    printf("How many columns are in the first matrix? \n");
    scanf("%d", &m1_columns);

    printf("How many rows are in the second matrix? \n");
    scanf("%d", &m2_rows);
    printf("How many columns are in the second matrix? \n");
    scanf("%d", &m2_columns);

    printf("\n");

    if (m1_columns != m2_rows) {
        printf("Invalid matrix multiplication!\n");
        exit(-1);
    }

    matrix1 = mm_alloc(m1_rows, m1_columns);
    matrix2 = mm_alloc(m2_rows, m2_columns);

    results_matrix = mm_alloc(m1_rows, m2_columns);

    mm_read( matrix1, m1_rows, m1_columns );
    mm_read( matrix2, m2_rows, m2_columns );

    printf("\n");

    mm_mult(matrix1, m1_rows, m1_columns, matrix2, m2_rows, m2_columns, results_matrix);

    mm_print( matrix1, m1_rows, m1_columns );
    printf("\n");
    printf("multiplied by\n\n");
    mm_print( matrix2, m2_rows, m2_columns );
    printf("\n");
    printf("is: \n\n");
    mm_print( results_matrix, m1_rows, m2_columns );
    mm_free( matrix1, m1_rows, m1_columns );
    mm_free( matrix2, m2_rows, m2_columns );
    mm_free( results_matrix, m1_rows, m2_columns );

    return 0;
}
