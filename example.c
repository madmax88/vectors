#include <stdio.h>
#include <stdlib.h>
#include "libmax.h"

int main() {
  vector v = MAKE_VECTOR(int);

  for (int i = 0; i < 20; i++) {
    VECTOR_PUSHBACK(i, int, v);
  }

  DELETE_ELEMENT(2, v);
  
  for (int i = 0; i < v.num_elements; i++) {
    int foo = ACCESS_POSITION(i, int, v);
    printf("%d\n", foo);
  }

  FREE_VECTOR(v);
}
