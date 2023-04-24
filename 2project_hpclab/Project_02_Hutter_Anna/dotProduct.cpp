// #include <omp.h>
#include "walltime.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <omp.h>

#define NUM_ITERATIONS 100

// Example benchmarks
// 0.008s ~0.8MB
// #define N 100000
// 0.1s ~8MB
// #define N 1000000
// 1.1s ~80MB
// #define N 10000000
// 13s ~800MB
// #define N 100000000
// 127s 16GB
// #define N 1000000000
#define EPSILON 0.1

using namespace std;

int main(int argc, char *argv[]) {
  double time_serial, time_start = 0.0;
  double *a, *b;
  int N = argc == 2 ? atoi(argv[1]) : 100000;
  int p = 0;
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    if (tid == 0) {
      p = omp_get_num_threads();
    }
  }
  cout << p << endl;

  // Allocate memory for the vectors as 1-D arrays
  a = new double[N];
  b = new double[N];

  // Initialize the vectors with some values
  for (int i = 0; i < N; i++) {
    a[i] = i;
    b[i] = i / 10.0;
  }

  long double alpha = 0;
  // serial execution
  // Note that we do extra iterations to reduce relative timing overhead
  if (p == 1) {
    time_start = wall_time();
    for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
      alpha = 0.0;
      for (int i = 0; i < N; i++) {
        alpha += a[i] * b[i];
      }
    }
    time_serial = wall_time() - time_start;
    cout << "Serial execution time = " << time_serial << " sec" << endl;
  }
  else {
    cout << "Serial execution time = 0 sec" << endl;
  }

  long double alpha_parallel = 0;
  double time_red = 0;
  double time_critical = 0;

  //   TODO: Write parallel version (2 ways!)
  //   i.  Using reduction pragma
  time_start = wall_time();
  for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
    alpha_parallel = 0.0;
    #pragma omp parallel
    {
      #pragma omp for reduction(+:alpha_parallel)
      for (int i = 0; i < N; i++) {
        alpha_parallel += a[i]*b[i];
      }
    }
  }
  time_red = wall_time() - time_start;
  
  
  //   ii. Using  critical pragma
  time_start = wall_time();
  for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
    alpha_parallel = 0.0;
    #pragma omp parallel
    {
      long double local_alpha = 0;
      #pragma omp for
      for (int i = 0; i < N; i++) {
        local_alpha += a[i] * b[i];
      }
      #pragma omp critical
      alpha_parallel += local_alpha;
    }
  }
  time_critical = wall_time() - time_start;

  if (p != 1) {
    alpha = alpha_parallel;
  }

  if ((fabs(alpha_parallel - alpha) / fabs(alpha_parallel)) > EPSILON) {
    cout << "parallel reduction: " << alpha_parallel << ", serial: " << alpha
         << "\n";
    cerr << "Alpha not yet implemented correctly!\n";
    exit(1);
  }
  cout << "Parallel dot product = " << alpha_parallel
       << " time using reduction method = " << time_red
       << " sec, time using critical method " << time_critical << " sec"
       << endl;

  // De-allocate memory
  delete[] a;
  delete[] b;

  return 0;
}
