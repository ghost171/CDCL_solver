#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

int Solver::backtrack(int decisionLevel) {
	vector<int> learntClause = literalsListInclause[degreeAntecedent];
	int conflictLevel = decisionLevel;
	int thisLevelCount = 0;
	int ConflictSolverLiteral;
	int literal;

  	do {
    	thisLevelCount = 0;
    	for (unsigned int i = 0; i < learntClause.size(); i++) {
      		literal = literalWithPolarity(learntClause[i]);
      		if (literalDecisionLevel[literal] == conflictLevel) {
        		thisLevelCount++;
      		}
      
      		if (literalDecisionLevel[literal] == conflictLevel && literalPast[literal] != -1) {
        		ConflictSolverLiteral = literal;
      		}
    	}
    
    	if (thisLevelCount == 1) {
      		break;
    	}
    
    	learntClause = conflict_solve(learntClause, ConflictSolverLiteral);
  	} while (true);
  	literalsListInclause.push_back(learntClause);
  	for (unsigned int i = 0; i < learntClause.size(); i++) {
    	int literalIndex = literalWithPolarity(learntClause[i]);
		int  update = 0;
		if (learntClause[i] > 0) {
			update = 1;
		} else {
			update = -1;
		}
    	polarity[literalIndex] += update;
    
    	if (frequency[literalIndex] != -1) {
      		frequency[literalIndex]++;
    	}
    	nonPolarFrequency[literalIndex]++;
  	}
  	clauseCount++;
  	int backtrackedDecisionLevel = 0;
  	for (unsigned int i = 0; i < learntClause.size(); i++) {
    	int literalIndex = literalWithPolarity(learntClause[i]);
    	int decisionLevelOnThisLevel = literalDecisionLevel[literalIndex];
    	if (decisionLevelOnThisLevel != conflictLevel && decisionLevelOnThisLevel > backtrackedDecisionLevel) {
      		backtrackedDecisionLevel = decisionLevelOnThisLevel;
    	}
  	}
  	for (unsigned int i = 0; i < literals.size(); i++) {
		if (literalDecisionLevel[i] > backtrackedDecisionLevel) {
			unfillLiteral(i);
		}
  	}
  	return backtrackedDecisionLevel;
}