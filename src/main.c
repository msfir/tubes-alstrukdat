#include <stdio.h>
#include "boolean.h"
#include "point.h"

int main() {
  Point p;
  CreatePoint(&p, 3, 2);
  TulisPOINT(p);
  return 0;
}
