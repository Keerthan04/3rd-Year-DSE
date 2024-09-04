#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter the dimension of the squared matrix: \n");
    scanf("%d", &n);

    int a[n][n], b[n][n], c[n][n], d[n][n];

    // Initialization
    printf("Please enter the elements of the matrix a \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Please enter the elements of the matrix b \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    int chunk_size;
    printf("Please enter the chunk size \n");
    scanf("%d", &chunk_size);

    omp_set_num_threads(8);

    // Initialize matrices c and d
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            d[i][j] = 0;
        }
    }

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            // Matrix multiplication
            #pragma omp parallel num_threads(4)
            {
                #pragma omp for schedule(static, chunk_size) collapse(2)
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        int sum = 0;
                        for (int k = 0; k < n; k++) {
                            sum += a[i][k] * b[k][j];
                        }
                        c[i][j] = sum;
                    }
                }
            }

            // Printing matrix c
            #pragma omp critical
            {
                printf("thread id: %d",omp_get_thread_num());
                printf("Matrix c (result of multiplication):\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        printf("%d ", c[i][j]);
                    }
                    printf("\n");
                }
            }
        }

        #pragma omp section
        {
            // Matrix addition
            #pragma omp parallel num_threads(4)
            {
                #pragma omp for schedule(static, chunk_size) collapse(2)
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        d[i][j] = a[i][j] + b[i][j];
                    }
                }
            }

            // Printing matrix d
            #pragma omp critical
            {
                printf("thread id: %d",omp_get_thread_num());
                printf("Matrix d (result of addition):\n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        printf("%d ", d[i][j]);
                    }
                    printf("\n");
                }
            }
        }
    }

    return 0;
}
