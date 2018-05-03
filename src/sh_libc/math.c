#include "include/math.h"

double sh_pow(double x, double y) {
  int i = 1;
  int j = 1;
  double p = 1;

  if (y == 0) { return 1; }

  if (y > 0) {
    while (i <= y) {
      p *= x;
      ++i;
    }
    return p;
  }

  if (y < 0) {
    y = - y;
    while (j <= y) {
      p *= x;
      ++j;
    }
  }
  return (1 / p);
}
