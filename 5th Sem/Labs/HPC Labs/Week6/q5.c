#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int fct = 1, sum;
    for(int i = 1; i <= rank; i++) fct *= i;

    MPI_Scan(&fct, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("%d: Subtotal = %d\n", rank, sum);
    MPI_Finalize();
}