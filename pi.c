#include <stdio.h>
#include <omp.h>

int main(void) {

  long num_steps = 100000000;
  double step_size = 1.0/(double)num_steps;
  double pi = 0.0;
  double elapsed = 0.0;

  elapsed = omp_get_wtime();
  #pragma omp parallel for reduction (+:pi) schedule(guided, 256)
  for(int i=0; i < num_steps; i++){
    double x = (i + 0.5) * step_size;
    pi += 4.0 / (1.0 + x*x);
  }
  pi /= num_steps;
  elapsed = omp_get_wtime() - elapsed;

  printf("PI: %g took %f seconds\n", pi, elapsed);
}