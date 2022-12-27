#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "solver.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string file_name = argv[1]; 
  Solver solver(file_name);
  solver.launch();
  return 0;
}
