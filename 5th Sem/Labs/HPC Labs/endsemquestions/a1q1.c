/*
Mpi question...
Take an n*n matrix as input and then send every row to a different process.
Display each value  with it's process id.If the values are multiples of 2 then they are changed to 0 else to 1.
They are then returned to the root process and displayed.
*/

//1.basic approach with scatter amd gather and 1d array else 2d array with send each individual array using send op with for loop and receive can be done in loops(1st is better)

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc,char*argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int n;
    //since scatter and gather works with 1 array just take as continuous allocation
    int *matrix = NULL;
    int *scatter_buf = NULL;
    int *gather_buf = NULL;
    if(rank == 0){
        printf("enter the value for n \n");
        fflush(stdout);
        scanf("%d",&n);
        if(n!=size){
            printf("since entered n is not equal to the number of processes cant proceed \n");
            MPI_Abort(MPI_COMM_WORLD,1);//new command to stop the execution
        }
        matrix = (int *)malloc(n*n*sizeof(int));
        gather_buf = (int *)malloc(n*n*sizeof(int));

        printf("enter the elements of the matrix \n");
        fflush(stdout);
        for(int i =0;i<n*n;i++){
            scanf("%d",&matrix[i]);
        }
    }
    //n shd be available to all so to allocate the value
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    scatter_buf = (int*)malloc(n*sizeof(int));//each shd have its scatter buf so

    MPI_Scatter(matrix,n,MPI_INT,scatter_buf,n,MPI_INT,0,MPI_COMM_WORLD);//scatter each n ele of row
    for(int i =0;i<n;i++){
        printf("process id is %d and value is %d \n",rank,scatter_buf[i]);
        if(scatter_buf[i]%2 == 0) scatter_buf[i] = 0;
        else scatter_buf[i] = 1;
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(scatter_buf,n,MPI_INT,gather_buf,n,MPI_INT,0,MPI_COMM_WORLD);//similar gather all to one
    if(rank ==0){
        printf("the final matrix is \n");
        for(int i =0;i<n;i++){
            for(int j = 0;j<n;j++){
                printf("%d ",gather_buf[i*n+j]);//getting using row major format
            }
            printf("\n");
        }
    }
    free(matrix);
    free(gather_buf);
    free(scatter_buf);
    MPI_Finalize();
    return 0;
}