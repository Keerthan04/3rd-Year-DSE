#include<stdio.h>

__global__ void mult(int *a, int *b, int *c, int ma, int na, int nb){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if(i >= ma || j >= nb) return;
    c[na * i + j] = 0;
    for(int k = 0; k < na; k++)
        atomicAdd(c + na * i + j, a[na * i + k] * b[nb * k + j]);
}

int main(){
    int int_s = sizeof(int), ma, na, mb, nb;
    printf("Enter m, n for a: ");
    scanf("%d %d", &ma, &na);

    printf("Enter m, n for b: ");
    scanf("%d %d", &mb, &nb);

    int a[ma * na], b[mb * nb], c[ma * nb];
    printf("Enter a: ");
    for(int i = 0; i < ma * na; i++) scanf("%d", a + i);
    printf("Enter b: ");
    for(int i = 0; i < mb * nb; i++) scanf("%d", b + i);

    int *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, int_s * ma * na);
    cudaMalloc((void**)&d_b, int_s * mb * nb);
    cudaMalloc((void**)&d_c, int_s * ma * nb);

    cudaMemcpy(d_a, a, int_s * ma * na, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, int_s * mb * nb, cudaMemcpyHostToDevice);

    mult<<<dim3(2, 2), dim3(ceil(ma/2.0), ceil(nb/2.0))>>>(d_a, d_b, d_c, ma, na, nb);
    cudaMemcpy(c, d_c, int_s * ma * nb, cudaMemcpyDeviceToHost);

    for(int i = 0; i < ma; i++){
        for(int j = 0; j < nb; j++)
            printf("%d ", c[nb * i + j]);
        printf("\n");
    }
}