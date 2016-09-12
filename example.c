#include <stdio.h>
#include <stdlib.h>
#include "libmax.h"

int main() {
  vector v = MAKE_VECTOR(int);

  for (int i = 0; i < 20; i++) {
    INSERT_ELEMENT(i, v);
  }

  for (int i = 0; i < v.num_elements; i++) {
    int temp;
    ACCESS_ELEMENT(i, temp, v);
    printf("%d\n", temp);
  }
}
