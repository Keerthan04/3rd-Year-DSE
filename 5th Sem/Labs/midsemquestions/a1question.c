/*Matrix A..
Find transpose AT..
Multiply A and AT to get C
Find diagonal sum
Find boundary sum
Use chunk size
Explicitly mention private or shared for all var in pragma.
Then print all sums and matrices
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {
    int n, chunk_size, diag_sum = 0, border_sum = 0;
    printf("Enter n: \n");
    scanf("%d", &n);

    int a[n][n], b[n][n],c[n][n];
    printf("Enter elements of matrix a \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter the chunk size \n");
    scanf("%d", &chunk_size);

    // Initialization (always do this, it is better)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
        }
    }

    omp_set_num_threads(8);
    omp_set_nested(1);

    int i, j, k;

    #pragma omp parallel shared(a, b)
    {
        #pragma omp single
        {
            // Matrix transpose
            #pragma omp parallel for private(i, j) schedule(static, chunk_size) num_threads(4)
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    b[j][i] = a[i][j];  // No need for a critical section here
                }
            }

        
            //since the main point here is when for and parallel the iterations are divided and each will get unique of i and j so there is no problem of same i and j so no race conditions happens on b and c also in side loops
        
            // Matrix multiplication of a and b
            #pragma omp parallel for private(i, j, k) schedule(static, chunk_size) num_threads(4)
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    for (k = 0; k < n; k++) {
                        c[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        
            //print the c matrix

        
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    printf("%d ", c[i][j]);
                }
                printf("\n");
            }
        }

        // Diagonal and border sum with the help of nested parallelism
        //when doing these sum across all better to use reduction(does private copy of the variable and does the thing for each thread then open mp manages to add all copies in the end and stored in the shared variable)
        #pragma omp parallel sections reduction(+:diag_sum, border_sum) num_threads(2)
        {//whenever we have nested parallelism reduction shd be in the outermost only because it does after all the summing of individual copies because outer one does all the final so reduction shd be here
            #pragma omp section
            {
                // Diagonal sum
                #pragma omp parallel for  private(i) schedule(static, chunk_size) num_threads(4)
                for (i = 0; i < n; i++) {
                    diag_sum += c[i][i];
                }
                
            }

            #pragma omp section
            {
                // Border sum
                #pragma omp parallel for  private(i, j) schedule(static, chunk_size) num_threads(4)
                for (i = 0; i < n; i++) {
                    for (j = 0; j < n; j++) {
                        if (i == 0 || i == n-1 || j == 0 || j == n-1) {
                            border_sum += c[i][j];
                        }
                    }
                }
                
            }
        }
    }
    printf("Diagonal sum is %d\n", diag_sum);//write this to get value after parallel region
    printf("Border sum is %d\n", border_sum);
    return 0;
}
