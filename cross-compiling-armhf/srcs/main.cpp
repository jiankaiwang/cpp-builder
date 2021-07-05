#include <cstdlib>
#include <iostream>
#include "mmth.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Tanh(3):" << tanh_impl(3.0) << std::endl;
}