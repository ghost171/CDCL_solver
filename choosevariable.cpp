#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

int Solver::VariableChoice() {
  bool too_many_attempts = false;
  int attempts = 0;
  uniform_int_distribution<int> chooseBranch(1, 11);
  uniform_int_distribution<int> chooseVariable(0, literalCount);
  int BranchChosen = chooseBranch(generator);
  if (BranchChosen > 4 || assignedLiteralCount < literalCount / 2 || too_many_attempts) {
    pickedVariablesCounters++;
    if (pickedVariablesCounters == 20 * literalCount) {
      for (unsigned int i = 0; i < literalsList.size(); i++) {
        BackTrackFrequency[i] /= 2;
        if (frequency[i] != -1) {
          frequency[i] /= 2;
        }
      }
      pickedVariablesCounters = 0;
    }
    int variable = distance(frequency.begin(), max_element(frequency.begin(), frequency.end()));
    if (polarity[variable] >= 0) {
      return variable + 1;
    }
    return -variable - 1;
  } else {
    while (attempts < 10 * literalCount) {
      int variable = chooseVariable(generator);
      if (frequency[variable] != -1) {
        if (polarity[variable] >= 0) {
          return variable + 1;
        }
        return -variable - 1;
      }
      attempts++;
    }
    too_many_attempts = true;
  }
  while (too_many_attempts) {
    if (BranchChosen > 4 || assignedLiteralCount < literalCount / 2 || too_many_attempts) {
      pickedVariablesCounters++;
      if (pickedVariablesCounters == 20 * literalCount) {
        for (unsigned int i = 0; i < literalsList.size(); i++) {
          BackTrackFrequency[i] /= 2;
          if (frequency[i] != -1) {
            frequency[i] /= 2;
          }
        }
        pickedVariablesCounters = 0;
      }
      int variable = distance(frequency.begin(), max_element(frequency.begin(), frequency.end()));
      if (polarity[variable] >= 0) {
        return variable + 1;
      }
      return -variable - 1;
    } else {
      while (attempts < 10 * literalCount) {
        int variable = chooseVariable(generator);
        if (frequency[variable] != -1) {
          if (polarity[variable] >= 0) {
            return variable + 1;
          }
          return -variable - 1;
        }
        attempts++;
      }
      too_many_attempts = true;
    }
  }
  return 0;
}