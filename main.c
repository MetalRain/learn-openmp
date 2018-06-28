#include <stdio.h>
#include <omp.h>

int main() {
  int threads = 2;
  long num_steps = 100000;
  int steps_per_thread = num_steps / threads;
  double step_size = 1.0/(double)num_steps;
  double sums[threads];
  double total_sum = 0.0;
  double elapsed = 0.0;

  omp_set_num_threads(threads);
  omp_get_wtime();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    int offset = steps_per_thread * id;
    double x, sum = 0.0;

    for(int i=offset; i < offset + steps_per_thread; i++){
      x = (i + 0.5) * step_size;
      sum = sum + 4.0 / (1.0 + x*x);
    }
    sums[id] = sum * step_size;
  }
  elapsed = omp_get_wtime();

  for (int i=0; i < threads; i++) {
    total_sum += sums[i];
  }

  printf("PI: %g took %gms using %d threads\n", total_sum, elapsed / 1000., threads);
}