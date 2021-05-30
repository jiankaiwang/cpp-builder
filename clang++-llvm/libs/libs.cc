#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "libs.h"

int std::IsPrimeNum(int getNum) {
  if(getNum <= 1) {
    throw std::invalid_argument("Received the value <= 1.");
  } else if (getNum == 2 || getNum == 3) {
    return 1;
  } else {
    double sqrtNum = sqrt(getNum);
    int targetNum = static_cast<int>(sqrtNum);
    int itself = 1;
    for(int mod = 2; mod <= targetNum; mod++) {
      if(getNum % mod == 0) {
        itself = 0;
        break;
      }
    }
    return itself;
  }
}