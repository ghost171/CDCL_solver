#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

void Solver::fillLiteral(int variable, int decisionLevel, int antecedent) {
    int literal = literalWithPolarity(variable);
    int value = 0;
    if (variable > 0) {
        value = 1;
    } else {
        value = 0;
    }
    literalsList[literal] = value;
    literalDecisionLevel[literal] = decisionLevel;
    literalPast[literal] = antecedent;
    frequency[literal] = -1;
    assignedLiteralCount += 1;
}