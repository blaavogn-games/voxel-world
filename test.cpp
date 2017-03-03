#include <stdio.h>

#include "src/geom/Vector2.h"

void test(Vector2 v){
  v.x += 100.0f;
  printf("%f\n", v.x);
}

int main() {
  Vector2 v(2.0f,2.0f);
  printf("%f\n", v.x);
  test(v);
  printf("%f\n", v.x);
  return 0;
}