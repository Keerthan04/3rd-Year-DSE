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
        scanf("%d", &len);        
    }
    
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char str[len], sub[len/size];
    int counts[size], total = 0;

    if(rank == 0){
        printf("0: Enter string: ");
        fflush(stdout);
        for(i = 0; i < len; i++){
            scanf(" %c", str + i);
        }
        //puts(str);
    }

    MPI_Scatter(str, len/size, MPI_CHAR, sub, len/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    //puts(sub);

    int count = 0;
    for(i = 0; i < len/size; i++)
        switch(sub[i]){
            case 'a': case 'A':
            case 'e': case 'E':
            case 'i': case 'I':
            case 'o': case 'O':
            case 'u': case 'U': break;
            default: count++;
        }
    
    MPI_Gather(&count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for(i = 0; i < size; i++){
            printf("0: Rank %d, non-vowels: %d\n", i, counts[i]);
            total += counts[i];
        }

        printf("0: Total: %d\n", total);  
    }

    MPI_Finalize();
}
