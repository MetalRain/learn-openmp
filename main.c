#include <stdio.h>
#include <omp.h>

int main() {
  int requested_threads = 100;
  int used_threads;
  long num_steps = 10000000;
  double step_size = 1.0/(double)num_steps;
  double sums[requested_threads];
  double pi = 0.0;
  double elapsed = 0.0;

  omp_set_num_threads(requested_threads);
  omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int threads = omp_get_num_threads();
    double x;
    sums[id] = 0.0;
    if (id == 0){
      used_threads = threads;
    }

    for(int i=id; i < num_steps; i += threads){
      x = (i + 0.5) * step_size;
      sums[id] = sums[id] + 4.0 / (1.0 + x*x);
    }
  }
  elapsed = omp_get_wtime();

  for (int i=0; i < used_threads; i++) {
    pi += sums[i] * step_size;
  }

  printf("PI: %g took %gus using %d threads\n", pi, elapsed / 1000., used_threads);
}