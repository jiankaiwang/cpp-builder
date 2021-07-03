#include <cmath>
#include <algorithm>
#include "mmth.hpp"

double sinh_impl(double x) {
  return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl(double x) {
  return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double tanh_impl(double x) {
  return sinh_impl(x) / cosh_impl(x);
}

void sort(double array[], const int size) {
  std::sort(array, array + size);
}