#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "solver.hpp"

using namespace std;

int Solver::backtrack(int decisionLevel) {
vector<int> clause = literalsListInclause[degreeAntecedent];
    int conflictLevel = decisionLevel;
    int thisLevelConflictCount = 0;       
    int ConflictSolverLiteral;
    int literal;

    thisLevelConflictCount = 0;
    for (unsigned int i = 0; i < clause.size(); i++) {
        literal = literalWithPolarity(clause[i]);
        if (literalDecisionLevel[literal] == conflictLevel) {
            thisLevelConflictCount++;
        }
        if (literalDecisionLevel[literal] == conflictLevel && literalPast[literal] != -1) {
            ConflictSolverLiteral = literal;
        }
    }
    clause = ConflictSolve(clause, ConflictSolverLiteral);

    while (true) {
        thisLevelConflictCount = 0;
        for (unsigned int i = 0; i < clause.size(); i++) {
            literal = literalWithPolarity(clause[i]);
            if (literalDecisionLevel[literal] == conflictLevel) {
                thisLevelConflictCount++;
            }
            if (literalDecisionLevel[literal] == conflictLevel && literalPast[literal] != -1) {
                ConflictSolverLiteral = literal;
            }
        }
        if (thisLevelConflictCount == 1) {
            break;
        }
        clause = ConflictSolve(clause, ConflictSolverLiteral);
    }
    literalsListInclause.push_back(clause);
    for (unsigned int i = 0; i < clause.size(); i++) {
        int literalIndex = literalWithPolarity(clause[i]);
        int update;
        if (clause[i] > 0) {
            update = 1;
        } else {
            update = -1;
        }
        polarity[literalIndex] += update;
        if (frequency[literalIndex] != -1) {
            frequency[literalIndex]++;
        }
        BackTrackFrequency[literalIndex]++;
    }
    clauseCount++;
    int BacktrackeddecisionLevel = 0;
    for (unsigned int i = 0; i < clause.size(); i++) {
        int literalIndex = literalWithPolarity(clause[i]);
        int decisionLevelOnThisLevel = literalDecisionLevel[literalIndex];
        if (decisionLevelOnThisLevel != conflictLevel && decisionLevelOnThisLevel > BacktrackeddecisionLevel) {
            BacktrackeddecisionLevel = decisionLevelOnThisLevel;
        }
    }
    for (unsigned int i = 0; i < literalsList.size(); i++) {
        if (literalDecisionLevel[i] > BacktrackeddecisionLevel) {
            unfillLiteral(i);
        }
    }
    return BacktrackeddecisionLevel;
}
