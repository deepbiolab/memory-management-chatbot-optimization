#include <stdio.h>
#include <stdlib.h>

int main() {
  // void* p = malloc(sizeof(int)); // this will raise a error.
  int *p = (int *)malloc(sizeof(int));
  printf("Address=%p, value=%d, valueAddress=%p\n", p, p[0], &p[0]);
  printf("Address=%p, value=%d, valueAddress=%p\n", p, p[1], &p[1]);
  printf("Address=%p, value=%d, valueAddress=%p\n", p, p[2], &p[2]);
  return 0;
}