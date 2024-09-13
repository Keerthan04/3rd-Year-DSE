#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int m;
    if(rank == 0){
        printf("0: Enter m: ");
        fflush(stdout);
        scanf("%d", &m);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int arr[size * m], sub[m], res[size], avg = 0;

    if(rank == 0){
        printf("0: Enter elements: ");
        fflush(stdout);
        for(int i = 0; i < m * size; i++)
            scanf("%d", arr + i);
    }

    MPI_Scatter(arr, m, MPI_INT, sub, m, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < m; i++) avg += sub[i];
    avg /= m;
    printf("%d: Average = %d\n", rank, avg);

    MPI_Gather(&avg, 1, MPI_INT, res, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        avg = 0;
        for(int i = 0; i < size; i++) avg += res[i];
        printf("0: Average of averages = %d\n", avg / size);
    }

    MPI_Finalize();
}
