#include <stdio.h>
#include <stdlib.h>

struct MyStruct {
  int i;
  double d;
  char a[5];
};

int main() {
  MyStruct *p = (MyStruct *)calloc(4, sizeof(MyStruct));
  p[0].i = 1;
  p[0].d = 0.1;
  p[0].a[0] = 'a';
  p[0].a[1] = 'b';
  p[0].a[2] = 'c';
  p[0].a[3] = 'd';
  printf("Address: %p, value: %d\n", p, *p[0].a);
  printf("Address: %p, value: %d\n", p, p[0].i);
  printf("Address: %p, value: %d\n", p, *p[1].a);
}