//program to find the sum of even and odd numbers in a array
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(){
    int n;
    printf("Please enter the size of the array \n");
    scanf("%d",&n);
    int arr[n];
    printf("Please enter the elements of the array \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int odd_sum =0,even_sum=0;
    #pragma omp parallel sections num_threads(2)
    {
        //since section only one thread will do this
        #pragma omp section
        {
            for(int i=0;i<n;i++){
                if(arr[i]%2==0){
                    even_sum+=arr[i];
                }
            }
            printf("The sum of even numbers is %d\n",even_sum);
        }
        #pragma omp section
        {
            for(int i=0;i<n;i++){
                if(arr[i]%2!=0){
                    odd_sum+=arr[i];
                }
            }
            printf("The sum of odd numbers is %d\n",odd_sum);
        }
    }
}