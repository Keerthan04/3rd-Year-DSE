#include<stdio.h>
#include<omp.h>

int main(){
	int n, bsize, total= 0;
	printf("enter matrix, block size: ");
	scanf("%d %d", &n, &bsize);

	int a[n][n];
	int b[n/bsize][n/bsize];
	for(int i = 0; i < n/bsize; i++)
		for(int j = 0; j < n/bsize; j++)
			b[i][j] = 0;
	omp_set_nested(1);
	#pragma omp parallel if(n > 5) shared(n, bsize, a, b)
	{
		#pragma omp single
		{
			printf("Enter matrix: ");
			for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
			printf("Initialized by thread %d\n", omp_get_thread_num());
		}
		int t = omp_get_thread_num();
		#pragma omp for collapse(2)
		for(int i = 0; i < n; i+=bsize)
		for(int j = 0; j < n; j+= bsize){
			int s = 0;
			#pragma omp parallel for reduction(+:s) collapse(2)
			for(int ii = i; ii < i + bsize; ii++)
			for(int jj = j; jj < j + bsize; jj++) 
				s += a[ii][jj];
			b[i/bsize][j/bsize] = s;
			printf("Block %d, %d by thread %d, value %d\n", i/bsize, j/bsize, t, b[i/bsize][j/bsize]);	
		}
		
		#pragma omp for
		for(int i = 0; i < n/bsize; i++){
			int rsum = 0;
			#pragma omp parallel for reduction(+:rsum)
			for(int j = 0; j < n/bsize; j++)
				rsum += b[i][j];
			printf("row %d value %d thread %d\n", i, rsum, t);
		}

		#pragma omp for
		for(int j = 0; j < n/bsize; j++){
			int csum = 0;
			#pragma omp parallel for reduction(+:csum)
			for(int i = 0; i < n/bsize; i++)
				csum += b[i][j];
			printf("column %d, value %d, thread %d\n", j, csum, t);
		}

		#pragma omp for collapse(2) reduction(+:total)
		for(int i = 0; i < n/bsize; i++)
		for(int j = 0; j < n/bsize; j++)
			total += b[i][j];
	}
	printf("Total: %d\n", total);
}		
		
		
