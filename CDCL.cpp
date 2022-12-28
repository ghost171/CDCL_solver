#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include "solver.hpp"

using namespace std;

int Solver::CDCL() {
    int decisionLevel = 0;
    if (alreadyUnsatisfied)
    {
        return RetVal::R_UNSAT;
    }
    int variablePropagation_result = variablePropagation(decisionLevel);
    if (variablePropagation_result == RetVal::R_UNSAT) {
        return variablePropagation_result;
    }
    while (!allVariablesFilled()) {
        int picked_variable = chooseRightVariable(); 
        decisionLevel++;
        fillLiteral(picked_variable, decisionLevel, -1);
        while (true) {
            variablePropagation_result = variablePropagation(decisionLevel);
            if (variablePropagation_result == RetVal::R_UNSAT) {
                if (decisionLevel == 0) {
                    return variablePropagation_result;
                }
        
                decisionLevel = backtrack(decisionLevel);
            } else {
                break;
            }
        }
    }
    return RetVal::R_SAT;
}