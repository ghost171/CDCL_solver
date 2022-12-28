#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

void Solver::result(int StateOfResult) {
  	if (StateOfResult == RetVal::R_SAT)
  	{
    	cout << "SAT" << endl;
    	for (unsigned int i = 0; i < literals.size(); i++) {
      		if (i != 0) {
        		cout << " ";
      		}
      		if (literals[i] != -1) {
        		cout << pow(-1, (literals[i] + 1)) * (i + 1);
      		} else {
        		cout << (i + 1);
      		}
    	}
    	cout << " 0";
	} else {
    	cout << "UNSAT";
  	}
}