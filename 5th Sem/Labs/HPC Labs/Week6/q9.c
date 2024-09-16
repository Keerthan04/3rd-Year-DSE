#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    int rank, a[4][4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        printf("Enter matrix: ");
        fflush(stdout);

        for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            scanf("%d", &a[i][j]);
    }

    MPI_Bcast(a, 16, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 1; i < 4; i++)
        a[i][rank] += a[i - 1][rank];

    for(int i = 1; i < 4; i++){
        MPI_Bcast(&a[i][0], 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&a[i][1], 1, MPI_INT, 1, MPI_COMM_WORLD);
        MPI_Bcast(&a[i][2], 1, MPI_INT, 2, MPI_COMM_WORLD);
        MPI_Bcast(&a[i][3], 1, MPI_INT, 3, MPI_COMM_WORLD);
    }
    

    if(rank == 0){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
}