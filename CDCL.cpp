#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

int Solver::CDCL() {
  int decisionLevel = 0; 
  if (alreadyUnsatisfied) {
    return 1;
  }
  int prop = variablePropagation(decisionLevel);
  if (prop == 1) {
    return prop;
  }

  while (!(literalCount == assignedLiteralCount)) {
    int literal = VariableChoice(); 
    
    decisionLevel++;
    fillLiteral(literal, decisionLevel, -1);
    while (true) {
      prop = variablePropagation(decisionLevel);
      if (prop == 1) {
        if (decisionLevel == 0) {
          return prop;
        }
        decisionLevel = backtrack(decisionLevel);
      } else {
        break;
      }
    }
  }
  return 0;
}