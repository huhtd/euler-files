#include "walltime.h"
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
  int N = 2000000000;
  double up = 1.00000001;
  double Sn = 1.00000001;
  int n;
  /* allocate memory for the recursion */
  double *opt = (double *)malloc((N + 1) * sizeof(double));

  if (opt == NULL)
    die("failed to allocate problem size");

  double time_start = wall_time();

  double dist;
	long nthreads, tid;
  
  #pragma omp parallel private(dist, tid) shared(nthreads) reduction(*: Sn)
	{
		tid = omp_get_thread_num();
    nthreads = omp_get_num_threads();
		dist = pow(up, tid * N / nthreads);
		long i;
		for(i=0;i<N/nthreads;++i)
		{
			opt[i + tid*N/nthreads] = Sn * dist;
			Sn *= up;	
		}
  }

  printf("Parallel RunTime   :  %f seconds\n", wall_time() - time_start);
  printf("Final Result Sn    :  %.17g \n", Sn);

  double temp = 0.0;
  for (n = 0; n <= N; ++n) {
    temp += opt[n] * opt[n];
  }
  printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
  printf("\n");

  return 0;
}