#include<stdio.h>

__global__ void compute_sine(float* angle, float* sine){
    int i = threadIdx.x;
    sine[i] = sin(angle[i]);
}

int main(){
    int n;
    printf("Enter size: ");
    scanf("%d", &n);

    float angle[n], sine[n], *d_angle, *d_sine;
    cudaMalloc((void**)&d_angle, sizeof(float) * n);
    cudaMalloc((void**)&d_sine, sizeof(float) * n);

    printf("Enter array: ");
    for(int i = 0; i < n; i++) scanf("%f", angle + i);
    cudaMemcpy(d_angle, angle, sizeof(float) * n, cudaMemcpyHostToDevice);

    compute_sine<<<1, n>>>(d_angle, d_sine);
    cudaMemcpy(sine, d_sine, sizeof(float) * n, cudaMemcpyDeviceToHost);

    for(int i = 0; i < n; i++) printf("%f ", sine[i]);
    printf("\n");

    cudaFree(d_angle);
    cudaFree(d_sine);
}