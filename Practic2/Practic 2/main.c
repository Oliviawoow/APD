#include<mpi.h>
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define CONVERGENCE_COEF 100

/**
 * Run: mpirun -np 12 ./a.out
 */

static int num_neigh;
static int *neigh;

void read_neighbours(int rank) {
    FILE *fp;
    char file_name[15];
    sprintf(file_name, "./files/%d.in", rank);

    fp = fopen(file_name, "r");
	fscanf(fp, "%d", &num_neigh);

	neigh = malloc(sizeof(int) * num_neigh);

	for (size_t i = 0; i < num_neigh; i++)
		fscanf(fp, "%d", &neigh[i]);
}

int* get_dst(int rank, int numProcs, int leader) {
	MPI_Status status;
	MPI_Request request;

	/* Vectori de parinti */
	int *v = malloc(sizeof(int) * numProcs);
	int *vRecv = malloc(sizeof(int) * numProcs);

	memset(v, -1, sizeof(int) * numProcs);
	memset(vRecv, -1, sizeof(int) * numProcs);
	
	if (rank == leader)
		v[rank] = 0;
	else {

		for (int i = 0; i < num_neigh; ++i)
		{
			v[neigh[i]] = 1; 
		}

		for (int k = 0; k < CONVERGENCE_COEF; k++) {
			for(int i = 0; i < num_neigh; ++i) {
				MPI_Send(&v, numProcs, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
			}

			for(int i = 0; i < num_neigh; ++i) {
				int neighbourLeader;
				MPI_Status status;
				MPI_Recv(&vRecv, numProcs, MPI_INT, neigh[i], 0, MPI_COMM_WORLD, &status);
				for (int j = 0; j < numProcs; ++j)
				{
					if(v[j] == -1 && j != rank)
						v[j] = vRecv[j] + 1;
				}
				MPI_Send(&v, numProcs, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
			}

		}
	}

	return v;
}

int leader_chosing(int rank, int nProcesses) {
	int leader = -1;
	int q;
	leader = rank;
	
	/* Executam acest pas pana ajungem la convergenta */
	for (int k = 0; k < CONVERGENCE_COEF; k++) {
		/* TODO1: Pentru fiecare vecin, vom trimite liderul pe care il cunosc 
		* 		 si voi astepta un mesaj de la orice vecin
		* 		 Daca liderul e mai mare decat al meu, il actualizez pe al meu
		*/
		for(int i = 0; i < num_neigh; ++i) {
			MPI_Send(&leader, 1, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);
		}

		for(int i = 0; i < num_neigh; ++i) {
			int neighbourLeader;
			MPI_Status status;
			MPI_Recv(&neighbourLeader, 1, MPI_INT, neigh[i], 0, MPI_COMM_WORLD, &status);
			leader = (neighbourLeader > leader) ? neighbourLeader : leader;
		}

	}

	MPI_Barrier(MPI_COMM_WORLD);

	return leader;
}

int main(int argc, char * argv[]) {
	int rank, nProcesses, num_procs, leader;
	int *parents, **topology;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	if (nProcesses != 12) {
		printf("please run with: mpirun --oversubscribe -np 12 %s\n", argv[0]);
		MPI_Finalize();	
		exit(0);
	}
	 
	read_neighbours(rank);
	leader = leader_chosing(rank, nProcesses);
	
	MPI_Barrier(MPI_COMM_WORLD);

	parents = get_dst(rank, nProcesses, rank);

	for(int i = 0; i < nProcesses; i++){
		printf("v[%d] = %d\n",i, parents[i]);
	}
	
	MPI_Finalize();
	return 0;
}