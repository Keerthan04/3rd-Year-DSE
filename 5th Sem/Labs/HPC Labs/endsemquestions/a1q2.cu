/*
Cuda question... Input matrix n*n is taken... All principal diagonal elements are set to 0,upper half set to their factorial and lower half set to the sum of number.
sum of number clarification - 43 then ans is 7  (f bc)
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<cuda.h>
#include<math.h>
//basic wala with 1 block only

//to call from device use of device functions(since global runs on kernel so)
__device__ int factorial(int num) {
    if (num <= 1) {
        return 1;
    }
    return num * factorial(num - 1);
}

__device__ int sum_of_digits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

__global__ void matrix_cal(int *matrix, int n) {
    int i = threadIdx.x;//since just 1 block used
    int j = threadIdx.y;
    
    if (i < n && j < n) {
        if (i == j) {
            matrix[i * n + j] = 0;  // Principal diagonal set to 0
        } else if (i > j) {
            matrix[i * n + j] = sum_of_digits(matrix[i * n + j]);  // Lower triangle - sum of digits
        } else {
            matrix[i * n + j] = factorial(matrix[i * n + j]);  // Upper triangle - factorial
        }
    }
}

int main() {
    int n;
    printf("Enter n for an n*n matrix: \n");
    scanf("%d", &n);

    int matrix_size = n * n;
    int matrix[matrix_size];

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < matrix_size; i++) {
        scanf("%d", &matrix[i]);
    }

    int *d_matrix;
    int size = matrix_size * sizeof(int);

    // Allocate memory on the device
    cudaMalloc((void**)&d_matrix, size);
    
    // Copy the matrix to the device
    cudaMemcpy(d_matrix, matrix, size, cudaMemcpyHostToDevice);

    // Set up a 2D grid with one block and n x n threads(basic one can do with variabl block but itna mehnat nahi)
    dim3 threadsPerBlock(n, n);
    matrix_cal<<<1, threadsPerBlock>>>(d_matrix, n);

    // Copy the modified matrix back to the host
    cudaMemcpy(matrix, d_matrix, size, cudaMemcpyDeviceToHost);

    // Print the modified matrix
    printf("The final matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i * n + j]);//use of row major
        }
        printf("\n");
    }


    cudaFree(d_matrix);
    return 0;
}