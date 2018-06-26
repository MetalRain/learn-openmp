#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) {  
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    printf("A: %d\n", ID);
    printf("B: %d\n", ID);
  }
}