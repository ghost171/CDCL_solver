#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

void Solver::unfillLiteral(int literalIndex) {
    literalsList[literalIndex] = -1;
    literalDecisionLevel[literalIndex] = -1;
    literalPast[literalIndex] = -1;
    frequency[literalIndex] = BackTrackFrequency[literalIndex]; 
    assignedLiteralCount -= 1;
}