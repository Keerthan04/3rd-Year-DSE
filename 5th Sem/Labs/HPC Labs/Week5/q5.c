#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size, num;
    char input[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        FILE *fptr;
        fptr = fopen("q5_input.txt", "r");
        for(int i = 1; i < size; i++){
            fgets(input, 100, fptr);
            MPI_Send(input, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        fclose(fptr);
    } else {
        MPI_Recv(input, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        num = 1;
        for(int i = 0; input[i] != '\0'; i++)
            if(input[i] == ' ') num++;
        
        printf("%d: %d spaces in %s", rank, num, input);   
    }

    MPI_Finalize();
}