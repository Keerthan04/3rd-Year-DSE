#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int main(){
    int i;
    printf("Please enter the value of i \n");
    scanf("%d",&i);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int x = omp_get_thread_num();
        printf("Thread %d is running\n",x);
        double power = pow(i,x);
        printf("The power of %d raised to %d is %d\n",i,x,power);
    }
    return 0;
}