#include<stdio.h>

__global__ void word_count(char* s, char* sub, int* count, int words[], int subl){
    int i = threadIdx.x;
    if(words[i + 1] - 1 - words[i] != subl) return;
    for(int x = 0; x < subl; x++)
        if(s[words[i] + x] != sub[x]) return;
    atomicAdd(count, 1);
    
}
int main(){
    int n, size = sizeof(char), i, count = 0;
    int *d_count;
    printf("Number of words: ");
    scanf("%d", &n);

    int words[n + 1], *d_words; words[0] = 0;
    char s[100], sub[100], *d_s, *d_sub;

    printf("Enter string: ");
    fgets(s, 100, stdin);
    fgets(s, 100, stdin);

    int t = 1;
    for(i = 0; s[i] != '\0'; i++)
        if(s[i] == ' ') words[t++] = i + 1;
    words[t] = i;

    printf("Enter substring: ");
    fgets(sub, 100, stdin);
    int subl = 0; for(; sub[subl] != '\0'; subl++); subl--;

    cudaMalloc((void**)&d_s, size * words[t]);
    cudaMalloc((void**)&d_sub, size * subl);
    cudaMalloc((void**)&d_words, (t + 1) * sizeof(int));
    cudaMalloc(&d_count, sizeof(int));

    cudaMemcpy(d_s, s, size * words[t], cudaMemcpyHostToDevice);
    cudaMemcpy(d_sub, sub, size * subl, cudaMemcpyHostToDevice);
    cudaMemcpy(d_words, words, sizeof(int) * (t + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    word_count<<<1, t>>>(d_s, d_sub, d_count, d_words, subl);
    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    printf("%d\n", count);
    
}