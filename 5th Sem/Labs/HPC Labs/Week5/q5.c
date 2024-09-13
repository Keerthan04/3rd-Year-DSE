#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size, num, final = 0;
    char input[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //Number of processed should be equal to number of lines + 1
    if(rank == 0){
        FILE *fptr;
        fptr = fopen("q5_input.txt", "r");
        for(int i = 1; i < size; i++){
            fgets(input, 100, fptr);
            MPI_Send(input, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        fclose(fptr);

        for(int i = 1; i < size; i++){
            MPI_Recv(&num, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            final += num;
        }
        printf("0: Final word count: %d\n", final);
    } else {
        MPI_Recv(input, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        num = 1;
        for(int i = 0; input[i] != '\0'; i++)
            if(input[i] == ' ') num++;
        
        printf("%d: %d words in %s", rank, num, input);   
    }

    MPI_Finalize();
}
