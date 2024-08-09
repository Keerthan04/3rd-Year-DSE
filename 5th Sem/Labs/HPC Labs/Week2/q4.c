//Write an OpenMP program to perform Arithmetic operations (Add, Sub, Mul, Div) on two vectors A and B of size 4
#include <omp.h>
#include <stdio.h>  
#include <stdlib.h>

int main(){
    int a[4], b[4];
    printf("Enter 4 numbers for vector A: ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &a[i]);
    }
    printf("Enter 4 numbers for vector B: ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &b[i]);
    }

    #pragma omp parallel sections num_threads(4)
    {
        #pragma omp section
        {
            printf("Thread %d doing Addition: A + B = {", omp_get_thread_num());
            for (int i = 0; i < 4; i++) {
                printf("%d ", a[i] + b[i]);
            }
            printf("}\n");
        }
        #pragma omp section
        {
            printf("Thread %d doing Subtraction: A - B = {", omp_get_thread_num());
            for (int i = 0; i < 4; i++) {
                printf("%d ", a[i] - b[i]);
            }
            printf("}\n");
        }
        #pragma omp section
        {
            printf("Thread %d doing Multiplication: A * B = {", omp_get_thread_num());
            for (int i = 0; i < 4; i++) {
                printf("%d ", a[i] * b[i]);
            }
            printf("}\n");
        }
        #pragma omp section
        {
            printf("Thread %d doing Division: A / B = {", omp_get_thread_num());
            for (int i = 0; i < 4; i++) {
                if (b[i] != 0) {
                    printf("%d ", a[i] / b[i]);
                } else {
                    printf("Division by zero error ");
                }
            }
            printf("}\n");
        }
    }
    return 0;
}