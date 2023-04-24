/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: : Parallel matrix-vector multiplication and the     *
 *            and power method                                  *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

#include "hpc-power.h"

#include <math.h>

#include <stdlib.h>

#include <stdio.h>
#include <mpi.h>

double norm(double* vec, int N){
    double res = 0;

    for(int i = 0; i < N; i++){
        res += vec[i]*vec[i];
    }

    return sqrt(res);
}

void matVec(double* x, double* A, int N, int ny){
    
    int my_rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double* x_temp = (double*)calloc(ny, sizeof(double));

    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for(int j = 0; j < ny; ++j) {
        for(int i = 0; i < N; ++i) {
            x_temp[j] += A[N*j+i]*x[i];
        }
    }

    MPI_Gather(x_temp, ny, MPI_DOUBLE, x, ny, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(x_temp);
}



void powerMethod(double* A, double* x, int k, int N, int ny){

    int my_rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (my_rank == 0){
        for(int i = 0; i < N; ++i) {
            x[i] = (rand() % 100) / 100.;
        }
    }

    for(int i = 0; i < k; ++i) {
        if (my_rank == 0) {
            double nrm = norm(x, N);

            for(int i = 0; i < N; ++i) {
                x[i] /= nrm;
            }
        }

        matVec(x, A, N, ny);
    }
}



int main (int argc, char *argv[])
{
    int my_rank, size;
    int snd_buf, rcv_buf;
    int right, left;
    int sum, i;

    MPI_Status  status;
    MPI_Request request;

    int k = argc > 1 ? atoi(argv[1]) : 1000;
    int N = argc > 2 ? atoi(argv[2]) : 1<<12;
    int nx, ny;



    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if(my_rank == 0) {
        printf("Ki   = %d\n", k);
        printf("Ni   = %d\n", N);
    }



    /* This subproject is about to write a parallel program to
       multiply a matrix A by a vector x, and to use this routine in
       an implementation of the power method to find the absolute
       value of the largest eigenvalue of the matrix. Your code will
       call routines that we supply to generate matrices, record
       timings, and validate the answer.
    */


    nx = my_rank;
    ny = N/size;

    double *A = hpc_generateMatrix(N, nx*ny, ny);
        
    double* x = (double*)calloc(N, sizeof(double));

    double time_end, time_start=0.0;
    time_start = hpc_timer();

    powerMethod(A, x, k, N, ny);

    time_end   = hpc_timer() - time_start;

    if(my_rank == 0) {
        printf("size = %i\n", size);
        printf("N    = %i\n", N);
        printf("time = %.4f\n", time_end);
    }

    if(my_rank == 0) {
        int correct = hpc_verify(x, N, time_end);
    }


    MPI_Finalize();
    free(A);
    free(x);

    return 0;
}
