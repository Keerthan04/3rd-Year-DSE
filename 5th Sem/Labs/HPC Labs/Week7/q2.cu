#include<stdio.h>
__global__ void convolution(int* x, int* f, int* r, int n, int m){
    int i = threadIdx.x, j = threadIdx.y;
    if(m-1 - j + i < n) atomicAdd(r + (m-1 - j + i), x[i] * f[j]);
}

int main(){
    cudaMemcpyKind htd = cudaMemcpyHostToDevice,
                   dth = cudaMemcpyDeviceToHost;

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

    
    int *d_x, *d_f, *d_r;
    
    cudaMalloc((void**)&d_x, s * n);
    cudaMalloc((void**)&d_f, s * m);
    cudaMalloc((void**)&d_r, s * n);
    
    cudaMemcpy(d_x, x, s * n, htd);
    cudaMemcpy(d_f, f, s * m, htd);
    cudaMemcpy(d_r, r, s * n, htd);
    
    dim3 threads(n, m, 1);
    convolution<<<1, threads>>>(d_x, d_f, d_r, n, m);

    cudaMemcpy(r, d_r, s * n, dth);
    for(int i = 0; i < n; i++)
        printf("%d ", r[i]);
    printf("\n");

}
