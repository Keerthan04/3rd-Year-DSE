#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    char c[50];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Please enter the word: \n");
        fflush(stdout);  //to make output flushed before input
        scanf("%s", c);  
        
        MPI_Ssend(c, 50, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        printf("Message sent from process 0.\n");
        
        MPI_Recv(c, 50, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        printf("The updated characters are: \n");
        for (int i = 0; i < 50 && c[i] != '\0'; i++) {
            printf("%c", c[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        MPI_Recv(c, 50, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        printf("Data received from process 0.\n");
        
        for (int i = 0; i < 50 && c[i] != '\0'; i++) {
            if (isupper(c[i])) {
                c[i] = tolower(c[i]); 
            } else if (islower(c[i])) {
                c[i] = toupper(c[i]); 
            }
        }
        
        MPI_Ssend(c, 50, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
