#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

void Solver::launch() {
  int status = CDCL();
  
  if (status == 0) {
    cout << "SAT" << endl;
    cout << endl;
    for (unsigned int i = 0; i < literalsList.size(); i++) {
      if (i != 0) {
        cout << " ";
      }

      if (literalsList[i] != -1) {
        cout << pow(-1, (literalsList[i] + 1)) * (i + 1);
      } else {
        cout << (i + 1);
      }
    }
    cout << " 0";
  } else {
    cout << "UNSAT";
  }
}