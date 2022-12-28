#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

void Solver::init(string &filename) {
	
	AssignedLiteralCount = 0;
	degreeAntecedent = -1;
	pickedVariablesCounters = 0;
	alreadyUnsatisfied = false;

	char c;
  	string s;
  	std::ifstream myfile;
  	myfile.open(filename);

  	while (true) {
    	myfile >> c;
    	if (c == 'c') {
      		getline(myfile, s);
    	} else {
      		myfile >> s;
      		break;
    	}
  	}
  	myfile >> literalCount;
  	myfile >> clauseCount;

	literals.clear();
	literals.resize(literalCount, -1);
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
  	int literalCountInСlause = 0;
  	for (int i = 0; i < clauseCount; i++) {
    	literalCountInСlause = 0;
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
        		if (literalCountInСlause == 0) {
          			alreadyUnsatisfied = true;
        		}
        		break;
      		}
      		literalCountInСlause++;
    	}
  	}
  	myfile.close();
  	nonPolarFrequency = frequency; 
}

bool Solver::allVariablesFilled() {
	return literalCount == AssignedLiteralCount;
}

void Solver::launch() {
  	int StateOfResult = CDCL();
  	result(StateOfResult);
}

int main(int argc, char *argv[]) {
  	Solver solver;
  	string file_name = argv[1];
  	solver.init(file_name);
  	solver.launch();
  	return 0;
}
