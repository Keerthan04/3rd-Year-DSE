#include<stdio.h>
__global__ void reverse(char* s, char* rev, int len){
    int i = threadIdx.x;
    rev[i] = s[len - 1 - i];
}

int main(){
    int len, char_s = sizeof(char); 
    char s[100], *d_s, *d_rev;

    printf("Enter string: ");
    fgets(s, 100, stdin);
    for(len = 0; s[len] != '\0'; len++); len--;

    cudaMalloc((void**)&d_s, char_s * len);
    cudaMalloc((void**)&d_rev, char_s * len);

    cudaMemcpy(d_s, s, len * char_s, cudaMemcpyHostToDevice);
    reverse<<<1, len>>>(d_s, d_rev, len);
    cudaMemcpy(s, d_rev, char_s * len, cudaMemcpyDeviceToHost);

    puts(s);

}