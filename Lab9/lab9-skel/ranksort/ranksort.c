#include<mpi/mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 1000
#define MASTER 0
#define MAX_LIMIT 10000

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		printf("%i ", v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}
 
int main(int argc, char * argv[]) {
	int rank, i, j;
	int nProcesses;
	MPI_Init(&argc, &argv);
	int pos[N], posBuffer[N];
	int sorted = 0;
	int *v = (int*)malloc(sizeof(int)*N);
	int *tmp = (int*)malloc(sizeof(int)*N);	
	int *vQSort = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++) {
		pos[i] = 0;
		posBuffer[i] = 0;
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	int batchSize = N/nProcesses;
	MPI_Status status;

    if (rank == MASTER) {
		srandom(42);
        // generate random vector
		for(int i = 0; i < N; ++i) {
			v[i] = random() % MAX_LIMIT;
			tmp[i] = v[i];
		}

		for(int i = 1; i < nProcesses; ++i) {
			MPI_Send(v, N, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
    }


	if(rank == 0) {
		// DO NOT MODIFY
		displayVector(v);

		// make copy to check it against qsort
		// DO NOT MODIFY
		for(i = 0; i < N; i++)
			vQSort[i] = v[i];
		qsort(vQSort, N, sizeof(int), cmp);

		// sort the vector v
		
		for(int i = 0; i < batchSize; ++i) {
			for(int j = 0; j < N; ++j) {
				if(v[rank * batchSize + i] > v[j]) {
					pos[rank * batchSize + i]++;
				}
			}
		}

        // recv the new pozitions
		
		for(int i = 1; i < nProcesses; ++i) {
			MPI_Recv(posBuffer, N, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

			for(int j = 0; j < N; ++j) {
				pos[j] += posBuffer[j];
			}
		}

		int* freq = calloc(MAX_LIMIT, sizeof(int)); // handle duplication

		for(int i = 0; i < N; ++i) {
			pos[i] += freq[v[i]];
			freq[v[i]]++;
		}

		for(int i = 0; i < N; ++i) {
			v[pos[i]] = tmp[i];
		}

		printf("\n");

		displayVector(v);
		compareVectors(v, vQSort);
	} else {
		MPI_Recv(v, N, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // compute the positions
		for(int i = 0; i < batchSize; ++i) {
			for(int j = 0; j < N; ++j) {
				if(v[rank * batchSize + i] > v[j]) {
					pos[rank * batchSize + i]++;
				}
			}
		}

        // send the new positions to process MASTER
		MPI_Send(pos, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}
