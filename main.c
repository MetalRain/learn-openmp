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

  long num_steps = 100000000;
  double step_size = 1.0/(double)num_steps;
  double pi = 0.0;
  double elapsed = 0.0;

  omp_set_num_threads(requested_threads);
  omp_get_wtime();
  #pragma omp parallel for reduction (+:pi)
  for(int i=0; i < num_steps; i++){
    double x = (i + 0.5) * step_size;
    pi += 4.0 / (1.0 + x*x);
  }
  pi /= num_steps;
  elapsed = omp_get_wtime();

  printf("PI: %g took %g\n", pi, elapsed);
}