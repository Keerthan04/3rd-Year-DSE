#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float subtotal = 0, total = 0;
    float x = (float) rank / size; 
    //printf("%d: %f\n", rank, x);

    subtotal = 4 / (1 + x * x) / size;
    MPI_Reduce(&subtotal, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) printf("%d: pi = %f\n", rank, total);
    MPI_Finalize();
}