/**
 * @file      main.cpp
 * @brief     Header of
 * @date      Fri Apr 18 16:30:45 2025
 * @author    celsuss
 * @copyright BSD-3-Clause
 *
 * This module
 */

#include "simulator.h"
#include <iostream>

int main() {
  const int kalle = 1;

  std::cout << "Hello, Worlds!" << std::endl;
  Simulator *simulator = new Simulator();
  simulator->run();
  std::cout << "Bye, Worlds!" << std::endl;
  return 0;
}
