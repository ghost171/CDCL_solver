#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

int Solver::chooseRightVariable() {
	uniform_int_distribution<int> chooseBranch(1, 10);
	uniform_int_distribution<int> chooseLiteral(0, literalCount - 1);
	int randomValue = chooseBranch(generator); 
	bool LimitOfAttempts = false;
	int counterOfAttempts = 0;
  	
	do {
    	if (randomValue > 4 || AssignedLiteralCount < literalCount / 2 || LimitOfAttempts) {
      		pickedVariablesCounters++;
      		if (pickedVariablesCounters == 20 * literalCount) {
        		for (unsigned int i = 0; i < literals.size(); i++) {
          			nonPolarFrequency[i] /= 2;
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
      		while (counterOfAttempts < 10 * literalCount) {
        		int variable = chooseLiteral(generator);
        		if (frequency[variable] != -1) {
          			if (polarity[variable] >= 0) {
            			return variable + 1;
          			}
          		return -variable - 1;
        		}
        		counterOfAttempts++;
      		}
      		LimitOfAttempts = true;
    	}
  	} while (LimitOfAttempts);
  	return 0;
}