#include<stdio.h>
//ChatGPT, should be correct

__global__ void conv2D(float *input, float *output, int x_m, int x_n, float *mask, int f) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    float value = 0.0f;

    int pad = f / 2;

    for (int i = -pad; i <= pad; i++) 
        for (int j = -pad; j <= pad; j++) {

            int curRow = row + i;
            int curCol = col + j;

            if (curRow >= 0 && curRow < x_n && curCol >= 0 && curCol < x_m) 
                value += input[curRow * x_m + curCol] * mask[(i + pad) * f + (j + pad)];
            
        }

    if (row < x_n && col < x_m) {
        output[row * x_m + col] = value;
    }
}

int main() {
    int x_m, x_n, f, float_s = sizeof(float);
    
    printf("Enter input dimensions: ");
    scanf("%d %d", &x_m, &x_n);
    
    printf("Enter filter size: ");
    scanf("%d", &f);

    float h_input[x_m * x_n], h_mask[f * f], h_output[x_m * x_n];
    printf("Enter matrix: ");
    for(int i = 0; i < x_m * x_n; i++) 
        scanf("%f", h_input + i);
    
    printf("Enter filter: ");
    for(int i = 0; i < f * f; i++) 
        scanf("%f", h_mask + i);

    float *d_input, *d_output, *d_mask;
    cudaMalloc(&d_input, x_m * x_n * float_s);
    cudaMalloc(&d_output, x_m * x_n * float_s);
    cudaMalloc(&d_mask, f * f * float_s);

    cudaMemcpy(d_input, h_input, x_m * x_n * float_s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, h_mask, f * f * float_s, cudaMemcpyHostToDevice);

    dim3 dimBlock(2, 2);
    dim3 dimGrid(ceil(x_m / 2.0), ceil(x_n / 2.0));
    conv2D<<<dimGrid, dimBlock>>>(d_input, d_output, x_m, x_n, d_mask, f);
    cudaMemcpy(h_output, d_output, x_m * x_n * float_s, cudaMemcpyDeviceToHost);

    for (int i = 0; i < x_n; i++) {
        for (int j = 0; j < x_m; j++) {
            printf("%0.2f ", h_output[i * x_m + j]);
        }
        printf("\n");
    }
}
