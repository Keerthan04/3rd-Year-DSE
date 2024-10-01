#include<stdio.h>

__global__ void mult(char* s1, char* s2, int size){
    int i = threadIdx.x;
    s2[i] = s1[i % size];
}

int main(){
    cudaMemcpyKind htd = cudaMemcpyHostToDevice,
                   dth = cudaMemcpyDeviceToHost;

    printf("Enter n: ");
    int n; scanf("%d", &n);

    printf("Enter string size: ");
    int size; scanf("%d", &size);

    int s = sizeof(char);
    char s1[size], s2[n * size], *d_s1, *d_s2;
    cudaMalloc((void**)&d_s1, s * size);
    cudaMalloc((void**)&d_s2, s * size * n);
    
    printf("Enter s1: ");
    for(int i = 0; i < size; i++) scanf(" %c", s1 + i);
    cudaMemcpy(d_s1, s1, size * s, htd);

    mult<<<1, n * size>>>(d_s1, d_s2, size);
    cudaMemcpy(s2, d_s2, n * size * s, dth);

    for(int i = 0; i < n * size; i++) 
        printf("%c", s2[i]);
    printf("\n");

}