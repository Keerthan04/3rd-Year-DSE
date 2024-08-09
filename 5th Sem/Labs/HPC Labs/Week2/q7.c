//Write a program using OpenMp to compute the Fibonacci number for the following arrays of numbers: A={10, 13, 5, 6}. Create a separate thread to perform the operations.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int fib(int n){
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return fib(n-1) + fib(n-2);
}

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    #pragma omp parallel num_threads(n)
    {
        #pragma omp for
        for(int i = 0; i < n; i++){
            printf("Thread id: %d, Fibonacci number of %d is %d\n", omp_get_thread_num(), arr[i], fib(arr[i]));
        }
    }
    return 0;
}
