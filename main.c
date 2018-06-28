#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int requested_threads = 4;

  if (argc > 1) {
    requested_threads = atoi(argv[1]);
    if (requested_threads > 16 || requested_threads < 1) {
      printf("Use 1-16 threads, not %d\n", requested_threads);
      return 1;
    }
  }

  int used_threads;
  long num_steps = 100000000;
  double step_size = 1.0/(double)num_steps;
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
    sum *= step_size;

    #pragma omp atomic
    pi += sum;
  }
  elapsed = omp_get_wtime();

  printf("PI: %g took %gus using %d threads\n", pi, elapsed / 1000., used_threads);
}