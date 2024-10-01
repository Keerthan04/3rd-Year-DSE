#include<stdio.h>

__global__ void row_add(int *a, int *b, int *c, int m, int n){
    int i = threadIdx.x;
    for(int j = 0; j < n; j++) c[n * i + j] = a[n * i + j] + b[n * i + j];
}
__global__ void col_add(int *a, int *b, int *c, int m, int n){
    int j = threadIdx.x;
    for(int i = 0; i < m; i++) c[n * i + j] = a[n * i + j] + b[n * i + j];
}
__global__ void ele_add(int *a, int *b, int *c, int m, int n){
    int i = threadIdx.x, j = threadIdx.y;
    c[n * i + j] = a[n * i + j] + b[n * i + j];
}

int main(){
    int int_s = sizeof(int), m, n;
    printf("Enter m, n: ");
    scanf("%d %d", &m, &n);

    int a[m * n], b[m * n], c[m * n];
    printf("Enter a: ");
    for(int i = 0; i < m * n; i++) scanf("%d", a + i);
    printf("Enter b: ");
    for(int i = 0; i < m * n; i++) scanf("%d", b + i);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, int_s * m * n);
    cudaMalloc((void**)&d_b, int_s * m * n);
    cudaMalloc((void**)&d_c, int_s * m * n);

    cudaMemcpy(d_a, a, int_s * m * n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, int_s * m * n, cudaMemcpyHostToDevice);

    row_add<<<1, m>>>(d_a, d_b, d_c, m, n);
    /*
    cudaMemcpy(c, d_c, int_s * m * n, cudaMemcpyDeviceToHost);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", c[n * i + j]);
        printf("\n");
    }
    */
    col_add<<<1, n>>>(d_a, d_b, d_c, m, n);
    /*
    cudaMemcpy(c, d_c, int_s * m * n, cudaMemcpyDeviceToHost);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", c[n * i + j]);
        printf("\n");
    }
    */
    ele_add<<<1, dim3(m, n)>>>(d_a, d_b, d_c, m, n);
    cudaMemcpy(c, d_c, int_s * m * n, cudaMemcpyDeviceToHost);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", c[n * i + j]);
        printf("\n");
    }
}