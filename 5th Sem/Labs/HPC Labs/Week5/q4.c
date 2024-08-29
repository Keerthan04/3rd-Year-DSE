#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int value_to_send;
    int val_received;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the initial value: ");
        fflush(stdout);
        scanf("%d", &value_to_send);
        
        // Send the value to the next process (rank 1)
        MPI_Ssend(&value_to_send, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
        printf("Initial value sent from process 0: %d\n", value_to_send);

        // Receive the final value from the last process (rank size-1)
        MPI_Recv(&val_received, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Circle completed at process 0 and the final value is: %d\n", val_received);
    } else {
        // Receive value from the previous process
        MPI_Recv(&val_received, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Value received by process %d: %d\n", rank, val_received);
        
        // Increment the received value
        val_received++;
        printf("Value sent by process %d after incrementing: %d\n", rank, val_received);
        
        // Send the incremented value to the next process
        MPI_Ssend(&val_received, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
