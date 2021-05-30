#include <iostream>
#include <cstdlib>
#include <vector>
#include "../libs/libs.h"

int main(int argv, char* args[]) {
  std::vector<int> checkVect = {-1, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11};
  for(int i = 0 ; i < checkVect.size(); i++) {
    try {
        std::cout << "Number " << checkVect[i] << " is a prime number? " << std::IsPrimeNum(checkVect[i]) << std::endl;
    } catch (std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
    }
  }
}