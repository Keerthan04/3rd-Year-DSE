#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int *arr = NULL;
    int value, result;
    char *buffer;
    int buffer_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Root process: Allocate array and read N elements
        arr = (int *)malloc(size * sizeof(int));
        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    }

    // Calculate required buffer size for buffered send
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &buffer_size);
    buffer_size += MPI_BSEND_OVERHEAD;//also calculate the overhead for the buffer also

    // Allocate buffer for buffered send
    buffer = (char *)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    if (rank == 0) {
        // Root process: Send each element to the corresponding process
        for (int i = 0; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    // Each process receives its respective value
    MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Calculate square or cube based on the rank
    if (rank % 2 == 0) {
        result = value * value;  // Square for even-ranked processes
    } else {
        result = value * value * value;  // Cube for odd-ranked processes
    }

    // Output the result
    printf("Process %d received %d and calculated %d\n", rank, value, result);

    // Detach and free the buffer
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    if (rank == 0) {
        free(arr);
    }

    MPI_Finalize();
    return 0;
}
