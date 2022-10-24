#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solver {
public:
    Solver();
    int CDCL();

    void launch();

private:
    //objects
    mt19937 generator;
    bool alreadyUnsatisfied;
    int pickedVariablesCounters;
    int assignedLiteralCount;
    int degreeAntecedent;

    vector<int> literalsList;
    vector<vector<int>> literalsListInclause;
    vector<int> frequency;
    vector<int> polarity;
    vector<int> BackTrackFrequency;
    int literalCount;
    int clauseCount;
    vector<int> literalDecisionLevel;
    vector<int> literalPast;
    random_device random_generator;
    
    //functions

    int backtrack(int decisionLevel);

    int variablePropagation(int decisionLevel);
    
    void fillLiteral(int variable, int decisionLevel, int antecedent);

    void unfillLiteral(int literalIndex);

    int literalWithPolarity(int variable);

    int VariableChoice();

    vector<int> &ConflictSolve(vector<int> &input, int literal);

};