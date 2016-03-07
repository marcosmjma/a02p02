
/*
 ============================================================================
 Name        : a02p02.cc
 Author      : Marcos J. Martinez A.
 Version     :
 Copyright   : Your copyright notice
 Description : Clemson University, Spring 2016
 ============================================================================
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

using namespace std;

int main(int argc, char * argv[])	{
	int my_rank, nprocs;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	long max_size = pow(2, 32);
	if (argc > 1) {
		max_size = pow(2, atoi(argv[1]));
	} //Here is line 23

	int num_repeats = 100;
	if (argc > 2) {
		num_repeats = atoi(argv[2]);
	}

	long msg_size = 1;
	double begin_time, end_time, rtt;
	double max_rtt, bandwidth;

	for (msg_size = 1; msg_size <= max_size; msg_size *= 2) {
		char *buf = new char[msg_size];
		if (!buf) {
			fprintf(stderr,"Insuficcient memory--msg_size=%ld");
			break;
		}
		begin_time = MPI_Wtime();

		for (int i= 0; i<num_repeats; i++) {
			if (my_rank == 0) {
				MPI_Send(buf, msg_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(buf, msg_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			} else if (my_rank == 1) {
				MPI_Recv(buf, msg_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				MPI_Send(buf, msg_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}

		end_time = MPI_Wtime();
		rtt = (end_time - begin_time) /num_repeats;

		MPI_Reduce(&rtt, &max_rtt, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

		bandwidth = 2.0e-6 * msg_size * sizeof(char) / max_rtt;

		if (my_rank == 0) {
			fprintf(stdout, "%ld %f %.f\n", msg_size*sizeof(char), 0.5e6 * max_rtt, bandwidth);
		}

		delete[] buf;
	}

	MPI_Finalize();
	return 0;
}



