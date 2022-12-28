#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

vector<int> &Solver::conflict_solve(vector<int> &clause, int literal) {
	vector<int> input = literalsListInclause[literalPast[literal]];
	clause.insert(clause.end(), input.begin(), input.end());
  	for (unsigned int i = 0; i < clause.size(); i++) {
    	if (clause[i] == literal + 1 || clause[i] == -literal - 1) {
      		clause.erase(clause.begin() + i);
      		i--;
    	}
  	}
	
	sort(clause.begin(), clause.end());
	clause.erase(unique(clause.begin(), clause.end()), clause.end());
	return clause;
}
