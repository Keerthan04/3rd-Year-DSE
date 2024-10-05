#include<stdio.h>

__global__ void inclusive_scan(int* a, int size){
    __shared__ int a_shared[4];

    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < size) a_shared[threadIdx.x] = a[i];
    __syncthreads();

    for(int x = i + 1; x < size; x++) 
        atomicAdd(&a[x], a_shared[i]);
}

int main(){
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int a[size];
    printf("Enter array: ");
    for(int i = 0; i < size; i++) scanf("%d", a + i);

    int *d_a; cudaMalloc(&d_a, sizeof(int) * size);
    cudaMemcpy(d_a, a, sizeof(int) * size, cudaMemcpyHostToDevice);

    inclusive_scan<<<ceil(size / 4.0), 4>>>(d_a, size);
    cudaMemcpy(a, d_a, sizeof(int) * size, cudaMemcpyDeviceToHost);

    for(int i = 0; i < size; i++) printf("%d ", a[i]);
    printf("\n");
}