#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mat[3][3], sub[3], search, count = 0;
    if(rank == 0){
        printf("0: Enter matrix: ");
        fflush(stdout);
        
        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            scanf("%d", &mat[i][j]);

        printf("0: Enter search value: ");
        fflush(stdout);
        scanf("%d", &search);
    }
    
    MPI_Scatter(mat, 3, MPI_INT, sub, 3, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&search, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < 3; i++) 
        if(sub[i] == search) count++;

    MPI_Reduce(&count, mat, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0) printf("0: %d\n", mat[0][0]);

    MPI_Finalize();
}