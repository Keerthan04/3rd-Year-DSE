#include<stdio.h>

__global__ void block_add(float *out, float *a, float *b) {
    int i = blockIdx.x;
    out[i] = a[i] + b[i];     
}

__global__ void thread_add(float *out, float *a, float *b) {
    int i = threadIdx.x;
    out[i] = a[i] + b[i];     
}

__global__ void var_add(float *out, float *a, float *b, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n) out[i] = a[i] + b[i];     
}

int main(){
    cudaMemcpyKind htd = cudaMemcpyHostToDevice, dth = cudaMemcpyDeviceToHost;
    int n;
    printf("Enter size: ");
    scanf("%d", &n);
    
    float a[n], b[n], out[n];
    float *da, *db, *dout;

    cudaMalloc((void**)&da, sizeof(float) * n);
    cudaMalloc((void**)&db, sizeof(float) * n);
    cudaMalloc((void**)&dout, sizeof(float) * n);

    printf("Enter a: ");
    for(int i = 0; i < n; i++)
        scanf("%f", a + i);
    
    printf("Enter b: ");
    for(int i = 0; i < n; i++)
        scanf("%f", b + i);

    cudaMemcpy(da, a, sizeof(float) * n, htd);
    cudaMemcpy(db, b, sizeof(float) * n, htd);
    cudaMemcpy(dout, out, sizeof(float) * n, htd);

    block_add<<<n, 1>>>(dout, da, db);
    cudaMemcpy(out, dout, n * sizeof(float), dth);

    for(int i = 0; i < n; i++)
        printf("%f ", out[i]);
    printf("\n");

    thread_add<<<1, n>>>(dout, da, db);
    cudaMemcpy(out, dout, n * sizeof(float), dth);
    
    for(int i = 0; i < n; i++)
        printf("%f ", out[i]);
    printf("\n");

    var_add<<<ceil(n/256.0), 256>>>(dout, da, db, n);
    cudaMemcpy(out, dout, n * sizeof(float), dth);
    
    for(int i = 0; i < n; i++)
        printf("%f ", out[i]);
    printf("\n");
    
    cudaFree(da);
    cudaFree(db);
    cudaFree(dout);

}