#include<stdio.h>

__global__ void power(int *a, int n){
    int i = threadIdx.x, j = threadIdx.y;
    int res = a[n * i + j];
    for(int x = 0; x < i; x++) a[n * i + j] *= res;
}

int main(){
    int m, n, int_s = sizeof(int);
    printf("Enter m, n: ");
    scanf("%d %d", &m, &n);

    int a[m * n], *d_a;
    printf("Enter matrix: ");
    for(int i = 0; i < m * n; i++) 
        scanf("%d", a + i);

    cudaMalloc((void**)&d_a, int_s * m * n);
    cudaMemcpy(d_a, a, int_s * m * n, cudaMemcpyHostToDevice);

    power<<<1, dim3(m, n)>>>(d_a, n);
    cudaMemcpy(a, d_a, int_s * m * n, cudaMemcpyDeviceToHost);
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", a[n * i + j]);
        printf("\n");
    }
}