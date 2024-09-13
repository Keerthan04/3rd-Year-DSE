#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int len, i;
    if(rank == 0){
        printf("0: Enter length: ");
        fflush(stdout);
        scanf("%d", &len);        
    }
    
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char s1[len], s2[len], sub1[len/size], sub2[len/size];
    char comb[2 * len/size], final[2 * len];
    int counts[size], total = 0;

    if(rank == 0){
        printf("0: Enter string 1: ");
        fflush(stdout);
        for(i = 0; i < len; i++){
            scanf(" %c", s1 + i);
        }

        printf("0: Enter string 2: ");
        fflush(stdout);
        for(i = 0; i < len; i++){
            scanf(" %c", s2 + i);
        }
        //puts(str);
    }

    MPI_Scatter(s1, len/size, MPI_CHAR, sub1, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, len/size, MPI_CHAR, sub2, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    for(i = 0; i < len/size; i++){
        comb[2 * i] = sub1[i];
        comb[2 * i + 1] = sub2[i];
    }

    MPI_Gather(comb, 2 * len/size, MPI_CHAR, final, 2 * len/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("0: Final string: ");
        for(i = 0; i < 2 * len; i++) printf("%c", final[i]);
        printf("\n");
    }
    MPI_Finalize();

}
