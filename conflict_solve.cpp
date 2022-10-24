#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

vector<int>& Solver::ConflictSolve(vector<int> &input, int literal) {
  vector<int> input_2 = literalsListInclause[literalPast[literal]];
  input.insert(input.end(), input_2.begin(), input_2.end());
  for (unsigned int i = 0; i < input.size(); i++) {
    if (input[i] == literal + 1 || input[i] == -literal - 1) {
      input.erase(input.begin() + i);
      i--;
    }
  }
  sort(input.begin(), input.end());
  input.erase(unique(input.begin(), input.end()), input.end());
  return input;
}