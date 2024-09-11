#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[size], val, res = 1;
    if(rank == 0){
        printf("0: Enter array: ");
        for(int i = 0; i < size; i++) scanf("%d", arr + i); 
    }

    MPI_Scatter(arr, 1, MPI_INT, &val, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 2; i <= val; i++) res *= i;
    printf("%d: %d\n", rank, res);
    
    MPI_Gather(&res, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        res = 0;
        for(int i = 0; i < size; i++)
            res += arr[i];
        printf("0: Sum of factorials: %d\n", res);
        
    }



    MPI_Finalize();
}