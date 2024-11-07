/*
Cuda question... Input matrix n*n is taken... All principal diagonal elements are set to 0,upper half set to their factorial and lower half set to the sum of number.
sum of number clarification - 43 then ans is 7  (f bc)
*/
//tested with hard coded -> NO GPU

%%writefile q.cu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>
#include <ctype.h>
#include<math.h>

#define N 3 // Matrix size for testing (N x N)

// Device function for calculating factorial
__device__ int factorial(int num) {
    if (num <= 1) return 1;
    return num * factorial(num - 1);
}

// Device function for calculating the sum of digits
__device__ int sum_of_digits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Kernel function for matrix calculation
__global__ void matrix_cal(int *matrix, int n) {
    int i = threadIdx.x;
    int j = threadIdx.y;

    if (i < n && j < n) {
        if (i == j) {
            matrix[i * n + j] = 0; // Set diagonal elements to 0
        } else if (i > j) {
            matrix[i * n + j] = sum_of_digits(matrix[i * n + j]); // Lower triangle: sum of digits
        } else {
            matrix[i * n + j] = factorial(matrix[i * n + j]); // Upper triangle: factorial
        }
    }
}

int main() {
    int matrix[N * N] = {2, 3, 4, 55, 6, 4, 12, 15, 10}; // Hardcoded 3x3 matrix

    int *d_matrix;
    int size = N * N * sizeof(int);

    // Allocate memory on the device
    cudaMalloc((void**)&d_matrix, size);

    // Copy matrix from host to device
    cudaMemcpy(d_matrix, matrix, size, cudaMemcpyHostToDevice);

    // Define block and grid sizes
    dim3 threadsPerBlock(N, N);

    // Launch kernel
    matrix_cal<<<1, threadsPerBlock>>>(d_matrix, N);

    // Copy result back to host
    cudaMemcpy(matrix, d_matrix, size, cudaMemcpyDeviceToHost);

    // Print the resulting matrix
    printf("The final matrix is:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i * N + j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d_matrix);

    return 0;
}
