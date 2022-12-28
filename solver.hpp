#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

enum RetVal {
  R_SAT,
  R_UNSAT,
  R_NORMAL
};

class Solver {
private:
  vector<int> literals;
  vector<vector<int>> literalsListInclause;
  vector<int> frequency;
  vector<int> polarity;
  vector<int> nonPolarFrequency;
  int literalCount;
  int clauseCount;
  int degreeAntecedent;
  vector<int> literalDecisionLevel;
  vector<int> literalPast;
  
  int AssignedLiteralCount;
  bool alreadyUnsatisfied;
  int pickedVariablesCounters;
  random_device randomVariables;
  mt19937 generator;
  int variablePropagation(int);
  void fillLiteral(int, int, int);
  void unfillLiteral(int);
  int literalWithPolarity(int);
  int backtrack(int);
  vector<int> &conflict_solve(vector<int> &,int);
  int chooseRightVariable();
  bool allVariablesFilled();
  void result(int);

public:
  Solver() : generator(randomVariables()) {}
  void init(string &);
  int CDCL();
  void launch();
};