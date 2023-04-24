#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "consts.h"
#include "pngwriter.h"

unsigned long get_time() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec * 1000000 + tp.tv_usec;
}

int main(int argc, char *argv[]) {

  int IS = argc == 2 ? atoi(argv[1]) : 4096;

  png_data *pPng = png_create(IS, IS);

  double x, y, x2, y2, cx, cy;
  cy = MIN_Y;

  double fDeltaX = (MAX_X - MIN_X) / (double)IS;
  double fDeltaY = (MAX_Y - MIN_Y) / (double)IS;

  long nTotalIterationsCount = 0;
  unsigned long nTimeStart = get_time();

  long i, j, n;

  n = 0;
  // do the calculation
  #pragma omp parallel for schedule(dynamic) private(cx,cy,x,y,x2,y2,n) shared(nTotalIterationsCount)
  {
       for (j = 0; j < IS; j++) {
              for (i = 0; i < IS; i++) {
                     cx = MIN_X + i*fDeltaX;
                     cy = MIN_Y + j*fDeltaY;
                     x = cx;
                     y = cy;
                     x2 = x * x;
                     y2 = y * y;
                     // compute the orbit z, f(z), f^2(z), f^3(z), ...
                     // count the iterations until the orbit leaves the circle |z|=2.
                     // stop if the number of iterations exceeds the bound MAX_ITERS.
                     // TODO
                     n = 0;

                     while (x2 + y2 < 2*2 && n < MAX_ITERS) {
                            y = 2*x*y + cy;
                            x = x2-y2 + cx;
                            
                            x2 = x * x;
                            y2 = y * y;

                            n += 1;
                     }
                     
                     #pragma omp atomic
                     nTotalIterationsCount += n;
                     
                     // n indicates if the point belongs to the mandelbrot set
                     // plot the number of iterations at point (i, j)
                     int c = ((long)n * 255) / MAX_ITERS;
                     png_plot(pPng, i, j, c, c, c);
              }
       }
  }
  unsigned long nTimeEnd = get_time();

  // print benchmark data
  printf("Total time:                 %g millisconds\n",
         (nTimeEnd - nTimeStart) / 1000.0);
  printf("Image size:                 %ld x %ld = %ld Pixels\n",
         (long)IS, (long)IS,
         (long)(IS * IS));
  printf("Total number of iterations: %ld\n", nTotalIterationsCount);
  printf("Avg. time per pixel:        %g microseconds\n",
         (nTimeEnd - nTimeStart) / (double)(IS * IS));
  printf("Avg. time per iteration:    %g microseconds\n",
         (nTimeEnd - nTimeStart) / (double)nTotalIterationsCount);
  printf("Iterations/second:          %g\n",
         nTotalIterationsCount / (double)(nTimeEnd - nTimeStart) * 1e6);
  // assume there are 8 floating point operations per iteration
  printf("MFlop/s:                    %g\n",
         nTotalIterationsCount * 8.0 / (double)(nTimeEnd - nTimeStart));

  //png_write(pPng, "mandel.png");
  return 0;
}
