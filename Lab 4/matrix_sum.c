// #Write a MPI program to read 4 X 4 matrix and display the following output using four processes.
// #I/p matrix: 1 2 3 4
// #            1 2 3 1
// #            1 1 1 1
// #            2 1 2 1
// #O/p matrix: 1 2 3 4
// #            2 4 6 5
// #            3 5 7 6
// #            5 6 9 7

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank, size, mat[4][4], out[4][4];

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0) {
		printf("Enter 4x4 Matrix : \n");
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				scanf("%d", &mat[i][j]);
				out[i][j] = 0;
			}
		}
	} 

	for(int i=0; i<4; i++){
		MPI_Bcast(mat[i], 4, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(out[i], 4, MPI_INT, 0, MPI_COMM_WORLD);
	}

	MPI_Scan (mat[rank], out[rank], 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Gather(out[rank], 4, MPI_INT, mat[rank], 4, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank==0){
		printf("The New Matrix is : \n");
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				printf("%d ", mat[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
}