#include <iostream>
#include <cstdlib>
#include <vector>
#include "libs.h"

int main(int argv, char* args[]) {
  std::vector<int> checkVect = {2, 3, 4, 5, 7, 8, 9, 11};
  for(int i = 0; i < checkVect.size(); i++) {
    std::cout << "The number " << checkVect[i] << " is a prime number? " << std::IsPrimeNum(checkVect[i]) << std::endl;
  }
  return 0;
}