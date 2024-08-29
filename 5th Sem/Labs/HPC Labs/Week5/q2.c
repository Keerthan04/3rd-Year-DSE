#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char* argv[]){
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int n;
    if(rank==0){
        printf("Enter a number \n");
        fflush(stdout);
        scanf("%d",&n);
        //sending to all the slaves of master
        for(int i=1;i<size;i++){//size gives 1 based indexing
            printf("sending data from process 0 to process %d \n",i);
            MPI_Send(&n,1,MPI_INT,i,1,MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);//status to track
        printf("data received from process 0 by process rank %d \n",rank);
        printf("the number is %d \n",n);
    }
    MPI_Finalize();
}