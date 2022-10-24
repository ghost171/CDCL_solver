#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

int Solver::literalWithPolarity(int variable) {
  if (variable > 0) {
    return variable - 1;
  } else {
    return -variable - 1;
  }
}