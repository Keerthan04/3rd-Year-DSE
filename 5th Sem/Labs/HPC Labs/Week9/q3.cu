#include<stdio.h>

__global__ void row_mult(int *a, int *b, int *c, int ma, int na, int nb){
    int i = threadIdx.x;
    for(int j = 0; j < nb; j++){
        c[na * i + j] = 0;
        for(int k = 0; k < na; k++)
            atomicAdd(c + na * i + j, a[na * i + k] * b[nb * k + j]); 
    }
}
__global__ void col_mult(int *a, int *b, int *c, int ma, int na, int nb){
    int j = threadIdx.x;
    for(int i = 0; i < ma; i++){
        c[na * i + j] = 0;
        for(int k = 0; k < na; k++)
            atomicAdd(c + na * i + j, a[na * i + k] * b[nb * k + j]); 
    }
}
__global__ void ele_mult(int *a, int *b, int *c, int ma, int na, int nb){
    int i = threadIdx.x, j = threadIdx.y;
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

    row_mult<<<1, ma>>>(d_a, d_b, d_c, ma, na, nb);
    
    cudaMemcpy(c, d_c, int_s * ma * nb, cudaMemcpyDeviceToHost);
    for(int i = 0; i < ma; i++){
        for(int j = 0; j < nb; j++)
            printf("%d ", c[nb * i + j]);
        printf("\n");
    }
    
    col_mult<<<1, nb>>>(d_a, d_b, d_c, ma, na, nb);
    
    cudaMemcpy(c, d_c, int_s * ma * nb, cudaMemcpyDeviceToHost);
    for(int i = 0; i < ma; i++){
        for(int j = 0; j < nb; j++)
            printf("%d ", c[nb * i + j]);
        printf("\n");
    }
    
    ele_mult<<<1, dim3(ma, nb)>>>(d_a, d_b, d_c, ma, na, nb);
    cudaMemcpy(c, d_c, int_s * ma * nb, cudaMemcpyDeviceToHost);

    for(int i = 0; i < ma; i++){
        for(int j = 0; j < nb; j++)
            printf("%d ", c[nb * i + j]);
        printf("\n");
    }
}