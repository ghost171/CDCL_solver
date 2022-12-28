#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

int Solver::variablePropagation(int decisionLevel) {
	bool clauseFound = false;
	unsigned int false_count = 0;
	int unsetCount = 0;
	int literalIndex;
	bool satisfiedFlag = false;
	int lastUnsetLiteral = -1;
  	do {
    	clauseFound = false;
    	for (unsigned int i = 0; i < literalsListInclause.size() && !clauseFound; i++) {
      		false_count = 0;
      		unsetCount = 0;
      		satisfiedFlag = false;
      		for (unsigned int j = 0; j < literalsListInclause[i].size(); j++) {
        		literalIndex = literalWithPolarity(literalsListInclause[i][j]);
        		if (literals[literalIndex] == -1) {
          			unsetCount++;
          			lastUnsetLiteral = j;
        		} else if ((literals[literalIndex] == 0 && literalsListInclause[i][j] > 0) || (literals[literalIndex] == 1 && literalsListInclause[i][j] < 0)) {
          			false_count++;
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
      		} else if (false_count == literalsListInclause[i].size()) {
        		degreeAntecedent = i;
        		return RetVal::R_UNSAT;
      		}
    	}
  	} while (clauseFound);
  	degreeAntecedent = -1;
  	return RetVal::R_NORMAL;
}