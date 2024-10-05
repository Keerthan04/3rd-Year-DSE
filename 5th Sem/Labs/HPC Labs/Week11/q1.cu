#include<stdio.h>
__constant__ int array[100], filter[20];
__global__ void convolution(int* r, int n, int m){

    int i = threadIdx.x, j = threadIdx.y;
    if(m-1 - j + i < n) atomicAdd(r + (m-1 - j + i), array[i] * filter[j]);
}

int main(){
    int n, m, s = sizeof(int);
    printf("Enter n, m: ");
    scanf("%d %d", &n, &m);

    int x[n], f[m], r[n];
    printf("Enter array: ");
    for(int i = 0; i < n; i++){
        scanf("%d", x + i);
        r[i] = 0;
    }

    printf("Enter mask: ");
    for(int i = 0; i < m; i++)
        scanf("%d", f + i);

    
    int *d_r;
    cudaMemcpyToSymbol(array, x, sizeof(float) * n);
    cudaMemcpyToSymbol(filter, f, sizeof(float) * m);
    cudaMalloc((void**)&d_r, s * n);
    
    dim3 threads(n, m);
    convolution<<<1, threads>>>(d_r, n, m);
    cudaMemcpy(r, d_r, s * n, cudaMemcpyDeviceToHost);

    for(int i = 0; i < n; i++)
        printf("%d ", r[i]);
    printf("\n");

}