#include <iostream>
#include <cstdlib>
#include <vector>

// to include libs.h, because the path defined in target_include_directories
// on the CMakeLists.txt under the libs
#include "libs.h"

void PrintLibsVer() {
  // LIBS_VERSION is defined in CMakeLists.txt under the directory libs.
  std::cout << "The Libs version: " << LIBS_VERSION << std::endl;
}

int main(int argv, char* args[]) {
  PrintLibsVer();

  std::vector<int> checkVect = {-1, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11};
  for(int i = 0 ; i < checkVect.size(); i++) {
    try {
        std::cout << "Number " << checkVect[i] << " is a prime number? " << std::IsPrimeNum(checkVect[i]) << std::endl;
    } catch (std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
    }
  }
}