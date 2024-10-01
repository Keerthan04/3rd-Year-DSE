#include<stdio.h>

__global__ void word_reverse(char* s, char* rev, int words[]){
    int i = threadIdx.x;
    for(int x = words[i]; x < words[i + 1] - 1; x++)
        rev[x] = s[words[i + 1] - 2 - x + words[i]];
    rev[words[i + 1] - 1] = ' ';
}

int main(){
    int n, size = sizeof(char), i;
    printf("Number of words: ");
    scanf("%d", &n);

    int words[n + 1], *d_words; words[0] = 0;
    char s[100], *d_s, *d_rev;

    printf("Enter string: ");
    fgets(s, 100, stdin);
    fgets(s, 100, stdin);

    int t = 1;
    for(i = 0; s[i] != '\0'; i++)
        if(s[i] == ' ') words[t++] = i + 1;
    words[t] = i;

    cudaMalloc((void**)&d_rev, size * words[t]);
    cudaMalloc((void**)&d_s, size * words[t]);
    cudaMalloc((void**)&d_words, (t + 1) * sizeof(int));

    cudaMemcpy(d_s, s, size * words[t], cudaMemcpyHostToDevice);
    cudaMemcpy(d_words, words, sizeof(int) * (t + 1), cudaMemcpyHostToDevice);

    word_reverse<<<1, t>>>(d_s, d_rev, d_words);
    cudaMemcpy(s, d_rev, size * words[t], cudaMemcpyDeviceToHost);

    puts(s);
}