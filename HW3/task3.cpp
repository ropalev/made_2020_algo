#include <iostream>
#include <math.h>

int NUM_ITERATION = 999;

long double root_and_square(long double value) {
  long double eps, left, right, mid;

  eps = 0.0000001;
  left = 1;
  right = pow(value,0.5);
  for (int i = 0; i < NUM_ITERATION; i++) {
    mid = left + (right - left) / 2;
    if (((pow(mid,2) + pow(mid,0.5)) < value + eps) &&
		((pow(mid,2) + pow(mid, 0.5)) > value - eps)) {
	  return right;
    }
    else if ((pow(mid,2) + pow(mid, 0.5)) > value - eps) {
      right = mid;
    }
    else {
      left = mid;
    }
  }
  return right;
}


int main() {
  long double c;

  std::cin >> c;
  std::cout << root_and_square(c);
  return (0);
}