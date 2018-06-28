#include <stdio.h>
#include <omp.h>

#define PAD 8 // 64 byte L1 cache line

int main() {
  int requested_threads = 4;
  int used_threads;
  long num_steps = 100000000;
  double step_size = 1.0/(double)num_steps;
  double sums[requested_threads][PAD];
  double pi = 0.0;
  double elapsed = 0.0;

  omp_set_num_threads(requested_threads);
  omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int threads = omp_get_num_threads();
    double x;
    double sum = 0.0;
    if (id == 0){
      used_threads = threads;
    }

    for(int i=id; i < num_steps; i += threads){
      x = (i + 0.5) * step_size;
      sum += 4.0 / (1.0 + x*x);
    }
    sums[id][0] = sum;
  }
  elapsed = omp_get_wtime();

  for (int i=0; i < used_threads; i++) {
    pi += sums[i][0] * step_size;
  }

  printf("PI: %g took %gus using %d threads\n", pi, elapsed / 1000., used_threads);
}