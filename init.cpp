#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

Solver::Solver(string &file_name) : generator(random_generator()), alreadyUnsatisfied(false), pickedVariablesCounters(0),  assignedLiteralCount(0), degreeAntecedent(-1) {
  char p1, p2, p3, p4;
  string line;
  std::ifstream myfile; 
  myfile.open(file_name);
  
  myfile >> p1;
  myfile >> p2;
  myfile >> p3;
  myfile >> p4;
  

  myfile >> literalCount;
  myfile >> clauseCount;

  literalsList.clear();
  literalsList.resize(literalCount, -1);
  frequency.clear();
  frequency.resize(literalCount, 0);
  polarity.clear();
  polarity.resize(literalCount, 0);
  literalsListInclause.clear();
  literalsListInclause.resize(clauseCount);
  literalPast.clear();
  literalPast.resize(literalCount, -1);
  literalDecisionLevel.clear();
  literalDecisionLevel.resize(literalCount, -1);
  int literal;
  int NumberOfVariablesInclause = 0; 
  for (int i = 0; i < clauseCount; i++) {
    NumberOfVariablesInclause = 0;
    while (true) {
      myfile >> literal;
      if (literal > 0) {
        literalsListInclause[i].push_back(literal);
        frequency[literal - 1]++;
        polarity[literal - 1]++;
      } else if (literal < 0) {
        literalsListInclause[i].push_back(literal); 
        frequency[-1 - literal]++;
        polarity[-1 - literal]--;
      } else {
        if (NumberOfVariablesInclause == 0)
        {
          alreadyUnsatisfied = true;
        }
        break; 
      }
      NumberOfVariablesInclause++;
    }
  }
  myfile.close();
  BackTrackFrequency = frequency;
}
