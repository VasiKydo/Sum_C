// Athroisi 2 dianismatwn C[N]=A[N]+B[N] opou N=10mil


#include <stdio.h>
#include <stdlib.h> 
#include <mpi.h>

int main(int argc, char **argv)
{
   	int rank, size;
   	double ta, tt; // metrisi xronou
	int N=10000000;
	int *A, *B, *C, *count;
	int i;
	
	A=malloc(N*sizeof(int));
	B=malloc(N*sizeof(int));
	C=malloc(N*sizeof(int));
	count=malloc(N*sizeof(int));

	MPI_Init(&argc, &argv);
   	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) 
	{
		for (i=0; i<N; i++) 
		{
			A[i]=rand() % 1000;
			B[i]=rand() % 1000;
//			printf("\n\nTimi A[%d]=%d Timi B[%d]=%d", i,A[i],i,B[i]);
		}
	}

	ta = MPI_Wtime(); // Arxi metrisis xronou
   	MPI_Bcast(A, N, MPI_INT, 0, MPI_COMM_WORLD); 
	MPI_Bcast(B, N, MPI_INT, 0, MPI_COMM_WORLD); 
	for (i=rank*(N/size); i<(rank+1)*(N/size); i+=1) 
	{
		count[i]=A[i]+B[i];
//		printf("\n\n Timi count[%d]=%d",i,count[i]);
	}

	MPI_Reduce(count, C, N, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) 
	{
      		tt = MPI_Wtime(); // Telos metrisis xronou
//		for (i=0; i<N; i++) 
//		{
			printf("\n\nTimi A[%d]=%d Timi B[%d]=%d Timi C[%d]=%d", 5000000,A[i],5000000,B[i],5000000,C[i]);
//		}
      		printf("\n\nXronos pou xreiastike:%.6f\n\n", tt-ta);
  	}		


	MPI_Finalize();
   	return 0;
}
