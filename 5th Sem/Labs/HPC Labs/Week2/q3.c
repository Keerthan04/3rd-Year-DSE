#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    //when section diff thread does different part but any can do any part
    #pragma omp parallel sections num_threads(4)
    {
        #pragma omp section
        {
            printf("Thread %d doing Addition: %d + %d = %d\n", omp_get_thread_num(), a, b, a + b);
        }
        #pragma omp section
        {
            printf("Thread %d doing Subtraction: %d - %d = %d\n", omp_get_thread_num(), a, b, a - b);
        }
        #pragma omp section
        {
            printf("Thread %d doing Multiplication: %d * %d = %d\n", omp_get_thread_num(), a, b, a * b);
        }
        #pragma omp section
        {
            if (b != 0) {
                printf("Thread %d doing Division: %d / %d = %d\n", omp_get_thread_num(), a, b, a / b);
            } else {
                printf("Thread %d doing Division: Division by zero error\n", omp_get_thread_num());
            }
        }
    }
    return 0;
}
