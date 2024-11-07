//take two matrix(n x n) and then add and multiply them(use 2d blocks and 2d threads)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<cuda.h>
#include<math.h>


__global__ void matrix_cal(int *a,int *b,int *res,int *add, int m,int n) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;//since 2d block and 2d thread
    int j = blockDim.y * blockIdx.y + threadIdx.y;
    if (i < m && j < n) {
        int val = 0;
        for (int k = 0; k < n; k++) {
            val += a[i * n + k] * b[k * n + j];
        }
        res[i * n + j] = val;
        add[i * n + j] = a[i * n + j] + b[i * n + j];
    }
}

int main() {
    int int_s = sizeof(int), m, n;
    printf("Enter m, n: ");
    scanf("%d %d", &m, &n);

    int a[m * n], b[m * n], res[m * n], add[m * n];
    printf("Enter a: ");
    for (int i = 0; i < m * n; i++) scanf("%d", a + i);
    printf("Enter b: ");
    for (int i = 0; i < m * n; i++) scanf("%d", b + i);

    int *d_a, *d_b, *d_res, *d_add;
    cudaMalloc((void**)&d_a, int_s * m * n);
    cudaMalloc((void**)&d_b, int_s * m * n);
    cudaMalloc((void**)&d_res, int_s * m * n);
    cudaMalloc((void**)&d_add, int_s * m * n);

    cudaMemcpy(d_a, a, int_s * m * n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, int_s * m * n, cudaMemcpyHostToDevice);
    int blockSize = 2;//expecting multiple of 2 ka input(else just to ceil)
    dim3 dimBlock(2, 2);
    dim3 dimGrid(m / blockSize, n / blockSize);
    matrix_cal<<<dimGrid, dimBlock>>>(d_a, d_b, d_res, d_add, m, n);
    cudaMemcpy(res, d_res, int_s * m * n, cudaMemcpyDeviceToHost);
    cudaMemcpy(add, d_add, int_s * m * n, cudaMemcpyDeviceToHost);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", res[n * i + j]);
        }
        printf("\n");
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", add[n * i + j]);
        }
        printf("\n");
    }
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_res);
    cudaFree(d_add);
    return 0;
}