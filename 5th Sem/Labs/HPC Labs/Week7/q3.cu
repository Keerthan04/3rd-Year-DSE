#include<stdio.h>

__global__ void linear(int a, int* x, int* y){
    int i = threadIdx.x;
    y[i] += a * x[i];
}

int main(){
    cudaMemcpyKind htd = cudaMemcpyHostToDevice, 
                   dth = cudaMemcpyDeviceToHost;

    printf("Enter size: ");
    int n; scanf("%d", &n);

    int x[n], y[n], a, *d_x, *d_y, size = sizeof(int);
    cudaMalloc((void**)&d_x, n * size);
    cudaMalloc((void**)&d_y, n * size);

    printf("Enter x: ");
    for(int i = 0; i < n; i++) scanf("%d", x + i);
    cudaMemcpy(d_x, x, size * n, htd);

    printf("Enter y: ");
    for(int i = 0; i < n; i++) scanf("%d", y + i);
    cudaMemcpy(d_y, y, size * n, htd);

    printf("Enter a: ");
    scanf("%d", &a);

    linear<<<1, n>>>(a, d_x, d_y);
    cudaMemcpy(y, d_y, size * n, dth);

    for(int i = 0; i < n; i++)
        printf("%d ", y[i]);
    printf("\n");

}