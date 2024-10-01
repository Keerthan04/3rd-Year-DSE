#include <stdio.h>
//Something wrong for sure + ChatGPT nonsense
__global__ void spmv_csr_kernel(int num_rows, float *values, int *col_indices, int *row_offsets, float *x, float *y) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < num_rows) {
        float dot = 0.0f;
        int row_start = row_offsets[row];
        int row_end = row_offsets[row + 1];
        for (int jj = row_start; jj < row_end; jj++) {
            dot += values[jj] * x[col_indices[jj]];
        }
        y[row] = dot;
    }
}



int main() {
    float values[5] = {10, 20, 30, 40, 50};
    int col_indices[5] = {0, 2, 1, 0, 1};
    int row_offsets[4] = {0, 2, 3, 5};
    float x[3] = {1, 2, 3};
    int num_rows = 3;
    float y[3] = {0, 0, 0};

    float *d_values, *d_x, *d_y;
    int *d_col_indices, *d_row_offsets;
    int float_s = sizeof(float);
    int int_s = sizeof(int);

    cudaMalloc(&d_values, 5 * float_s);
    cudaMalloc(&d_col_indices, 5 * int_s);
    cudaMalloc(&d_row_offsets, 4 * int_s);
    cudaMalloc(&d_x, 3 * float_s);
    cudaMalloc(&d_y, num_rows * float_s);

    cudaMemcpy(d_values, values, 5 * float_s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_indices, col_indices, 5 * int_s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_offsets, row_offsets, 4 * int_s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, 3 * float_s, cudaMemcpyHostToDevice);

    int blockSize = 4;
    int gridSize = ceil((float) num_rows / blockSize);
    spmv_csr_kernel<<<gridSize, blockSize>>>(num_rows, d_values, d_col_indices, d_row_offsets, d_x, d_y);

    cudaMemcpy(y, d_y, num_rows * float_s, cudaMemcpyDeviceToHost);

    printf("Result of SpMV (CSR): ");
    for (int i = 0; i < num_rows; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");
}
