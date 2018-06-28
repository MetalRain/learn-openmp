#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

#define DEPTH 4

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
  int i, sum = 0;
  if (n < 2) {
    return (n);
  }
  // Cut off parallelism after some point to avoid too many threads
  if (n > FS - DEPTH){
    #pragma omp parallel for num_threads(2) reduction(+:sum)
    for(i = 1; i < 3; i++){
      sum += fib(n - i);
    }
    return sum;
  } else {
    sum = fib(n - 1) + fib(n - 2);
  }
  return sum;
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  = malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
  double start, end;
  struct node *p=NULL;
  struct node *temp=NULL;
  struct node *head=NULL;
     
  printf("Process linked list\n");
  printf("  Each linked list node will be processed by function 'processwork()'\n");
  printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
  p = init_list(p);
  head = p;

  start = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      struct node * p = head;
      while (p != NULL) {
        #pragma omp task firstprivate(p)
        processwork(p);
        p = p->next;
      }
    }
  }

  end = omp_get_wtime();
  p = head;
  while (p != NULL) {
    printf("%d : %d\n",p->data, p->fibdata);
    temp = p->next;
    free (p);
    p = temp;
  }  
  free (p);

  printf("Compute Time: %f seconds\n", end - start);

  return 0;
}
