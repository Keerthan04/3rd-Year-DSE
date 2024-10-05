#include<stdio.h>

__global__ void complement(int *a, int m, int n){
    int i = threadIdx.x;
    if(i / m == 0 || i / m == n - 1 || i % n == 0 || i % n == n - 1) return;
    int pow2 = 1;
    while(pow2 <= a[i]) pow2 *= 2;
    int dec = a[i] ^ (pow2 - 1), bin = 0, offset = 1;
    while(dec > 0){
        bin += (dec % 2) * offset;
        offset *= 10;
        dec /= 2;
    }
    a[i] = bin;
}

int main(){
    int m, n;
    printf("Enter m, n: ");
    scanf("%d %d", &m, &n);

    int a[m * n];
    printf("Enter matrix: ");
    for(int i = 0; i < m * n; i++) scanf("%d", a + i);

    int *d_a;
    cudaMalloc(&d_a, sizeof(int) * m * n);
    cudaMemcpy(d_a, a, sizeof(int) * m * n, cudaMemcpyHostToDevice);

    complement<<<1, m * n>>>(d_a, m, n);
    cudaMemcpy(a, d_a, sizeof(int) * m * n, cudaMemcpyDeviceToHost);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", a[i * n + j]);
        printf("\n");
    }
    

}