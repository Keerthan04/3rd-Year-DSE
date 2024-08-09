//Write a program in OpenMP to toggle the character of a given character array indexed by the thread_Id. Print the corresponding Thread_Id.
#include <omp.h>
#include<stdio.h>
#include<stdlib.h>

int isUpper(char c){
    return c >= 'A' && c <= 'Z';
}
int main(){
    int n;
    printf("Enter the number of characters: ");
    scanf("%d", &n);
    char arr[n];
    printf("Enter the characters: ");
    for(int i = 0; i < n; i++){
        scanf(" %c", &arr[i]);
    }
    //setting the num_threads as the length and also when parallel for the for written below only no {}
    #pragma omp parallel num_threads(n)
    {
        #pragma omp for
        for(int i=0;i<n;i++){
            if(isUpper(arr[i])){
                printf("Thread id array index %d: character is %c\n", omp_get_thread_num(), arr[i]);
                arr[i] = arr[i] + 32;
                printf("Thread id array index %d: updated character is %c\n", omp_get_thread_num(), arr[i]);
            }
        }
        #pragma omp single //among all n threads only one will do
            {
                printf("Thread %d is executing the single region\n", omp_get_thread_num());
                printf("The final array is: ");
            }
        #pragma omp for ordered 
            for(int i=0;i<n;i++){
                #pragma omp ordered //since ordered so on loop iterations order it will be
                printf("%c ", arr[i]);
            }
    }
    
        return 0;
}