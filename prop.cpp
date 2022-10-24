#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

int Solver::variablePropagation(int decisionLevel) {
  bool clauseFound = false;
  unsigned int falseCount = 0;
  unsigned int unsetCount = 0;
  unsigned int literalIndex;
  bool satisfiedFlag = false;
  int lastUnsetLiteral = -1;
  
  clauseFound = false;
  for (unsigned int i = 0; i < literalsListInclause.size() && !clauseFound; i++) {
    falseCount = 0;
    unsetCount = 0;
    satisfiedFlag = false;
    for (unsigned int j = 0; j < literalsListInclause[i].size(); j++) {
      literalIndex =
          literalWithPolarity(literalsListInclause[i][j]);
      if (literalsList[literalIndex] == -1) {
        unsetCount++;
        lastUnsetLiteral = j;
      } else if ((literalsList[literalIndex] == 0 && literalsListInclause[i][j] > 0) || (literalsList[literalIndex] == 1 && literalsListInclause[i][j] < 0)) {
        falseCount++;
      } else {
        satisfiedFlag = true;
        break;
      }
    }
    if (satisfiedFlag) {
      continue;
    }
    if (unsetCount == 1) {
      fillLiteral(literalsListInclause[i][lastUnsetLiteral], decisionLevel, i);
      clauseFound = true;
      break;
    } else if (falseCount == literalsListInclause[i].size()) {
      degreeAntecedent = i;
      return 1;
    }
  }

  while (clauseFound) {
    clauseFound = false;
    for (unsigned int i = 0; i < literalsListInclause.size() && !clauseFound; i++) {
      falseCount = 0;
      unsetCount = 0;
      satisfiedFlag = false;
      for (unsigned int j = 0; j < literalsListInclause[i].size(); j++) {
        literalIndex =
            literalWithPolarity(literalsListInclause[i][j]);
        if (literalsList[literalIndex] == -1) {
          unsetCount++;
          lastUnsetLiteral = j;
        } else if ((literalsList[literalIndex] == 0 && literalsListInclause[i][j] > 0) || (literalsList[literalIndex] == 1 && literalsListInclause[i][j] < 0)) {
          falseCount++;
        } else {
          satisfiedFlag = true;
          break;
        }
      }
      if (satisfiedFlag) {
        continue;
      }
      if (unsetCount == 1) {
        fillLiteral(literalsListInclause[i][lastUnsetLiteral], decisionLevel, i);
        clauseFound = true;
        break;
      } else if (falseCount == literalsListInclause[i].size()) {
        degreeAntecedent = i;
        return 1;
      }
    }
  }

  degreeAntecedent = -1;
  return 2;
}
