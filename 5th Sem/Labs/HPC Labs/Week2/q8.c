// Write an OpenMP program to implement Matrix multiplication.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n;
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);
    int a[n][n], b[n][n], c[n][n],d[n][n];
    printf("Enter the elements of matrix A: ");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter the elements of matrix B: ");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &b[i][j]);
        }
    }
    //time calculation start
    double begin1 = omp_get_wtime();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            c[i][j] = 0;
            for(int k = 0; k < n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    printf("The sequential resultant matrix is: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    double end1 = omp_get_wtime();
    double seq = end1 - begin1;
    printf("Time taken for serial execution: %lf\n", seq);

    //time calculation for parallel
    double begin2 = omp_get_wtime();
    #pragma omp parallel for num_threads(6)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            d[i][j] = 0;
            for(int k = 0; k < n; k++){
                d[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    printf("The parallel resultant matrix is: \n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    double end2 = omp_get_wtime();
    int num_threads = 6;
    printf("Number of threads is %d \n",num_threads);
    double par = end2-begin2;
    printf("Time taken for parallel execution: %lf\n", par);

    double speedup = seq / par;
	printf("Speedup: %f\n", speedup);
	printf("Efficiency: %f\n", speedup / num_threads);
    return 0;
}