//Write a OpenMP program for generating prime numbers from a given starting number to the given ending number.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int start, end;
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);

    //use of 4 so that divide the iterations but each does a function call
    #pragma omp parallel for num_threads(4)
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            printf("%d is a prime number\n", i);
        }
    }
    return 0;
}
//one template is where a function does and a parallel for does for each check and does