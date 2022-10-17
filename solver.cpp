#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solver {
public:
  Solver() : generator(random_generator()), alreadyUnsatisfied(false), pickedVariablesCounters(0),  assignedLiteralCount(0), degreeAntecedent(-1) {
    char p;
    string line;

    while (true) {
      cin >> p;
      if (p == '%')
      {
        getline(cin, line); 
      } else {
        cin >> line;
        break;
      }
    }
    cin >> literalCount;
    cin >> clauseCount;
    literalsList.clear();
    literalsList.resize(literalCount, -1);
    frequency.clear();
    frequency.resize(literalCount, 0);
    polarity.clear();
    polarity.resize(literalCount, 0);
    literalsListInclause.clear();
    literalsListInclause.resize(clauseCount);
    literalPast.clear();
    literalPast.resize(literalCount, -1);
    literalDecisionLevel.clear();
    literalDecisionLevel.resize(literalCount, -1);

    int literal;
    int NumberOfVariablesInclause = 0; 
    for (int i = 0; i < clauseCount; i++) {
      NumberOfVariablesInclause = 0;
      while (true) {
        cin >> literal;
        if (literal > 0) {
          literalsListInclause[i].push_back(literal);
          frequency[literal - 1]++;
          polarity[literal - 1]++;
        } else if (literal < 0) {
          literalsListInclause[i].push_back(literal); 
          frequency[-1 - literal]++;
          polarity[-1 - literal]--;
        } else {
          if (NumberOfVariablesInclause == 0)
          {
            alreadyUnsatisfied = true;
          }
          break; 
        }
        NumberOfVariablesInclause++;
      }
    }
    BackTrackFrequency = frequency;
  }

  int CDCL() {
    int decisionLevel = 0; 
    if (alreadyUnsatisfied) {
      return 1;
    }
    int prop = variablePropagation(decisionLevel);
    if (prop == 1) {
      return prop;
    }

    while (!(literalCount == assignedLiteralCount)) {
      int literal = VariableChoice(); 
      
      decisionLevel++;
      fullLiteral(literal, decisionLevel, -1);
      while (true) {
        prop = variablePropagation(decisionLevel);
        if (prop == 1) {
          if (decisionLevel == 0) {
            return prop;
          }
          decisionLevel = backtrack(decisionLevel);
        } else {
          break;
        }
      }
    }
    return 0;
  }

  void launch() {
    int status = CDCL();
    
    if (status == 0) {
      cout << "SAT" << endl;
      cout << endl;
      for (int i = 0; i < literalsList.size(); i++) {
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

private:
  //objects
  vector<int> literalsList;
  vector<vector<int>> literalsListInclause;
  vector<int> frequency;
  vector<int> polarity;
  vector<int> BackTrackFrequency;
  int literalCount;
  int clauseCount;
  int degreeAntecedent;
  vector<int> literalDecisionLevel;
  vector<int> literalPast;
  int assignedLiteralCount;
  bool alreadyUnsatisfied;
  int pickedVariablesCounters;
  random_device random_generator;
  mt19937 generator;
  
  //functions

  int variablePropagation(int decisionLevel) {
    bool clauseFound = false;
    int falseCount = 0;
    int unsetCount = 0;
    int literalIndex;
    bool satisfiedFlag = false;
    int lastUnsetLiteral = -1;
    
    clauseFound = false;
    for (int i = 0; i < literalsListInclause.size() && !clauseFound; i++) {
      falseCount = 0;
      unsetCount = 0;
      satisfiedFlag = false;
      for (int j = 0; j < literalsListInclause[i].size(); j++) {
        literalIndex =
            literalWithPolarity(literalsListInclause[i][j]);
        if (literalsList[literalIndex] == -1) {
          unsetCount++;
          lastUnsetLiteral = j;
        } else if ((literalsList[literalIndex] == 0 && literalsListInclause[i][j] > 0) || (literalsList[literalIndex] == 1 && literalsListInclause[i][j] < 0)) {
          falseCount++;
        } else {
          satisfiedFlag = true;
          break;
        }
      }
      if (satisfiedFlag) {
        continue;
      }
      if (unsetCount == 1) {
        fullLiteral(literalsListInclause[i][lastUnsetLiteral], decisionLevel, i);
        clauseFound = true;
        break;
      } else if (falseCount == literalsListInclause[i].size()) {
        degreeAntecedent = i;
        return 1;
      }
    }

    while (clauseFound) {
      clauseFound = false;
      for (int i = 0; i < literalsListInclause.size() && !clauseFound; i++) {
        falseCount = 0;
        unsetCount = 0;
        satisfiedFlag = false;
        for (int j = 0; j < literalsListInclause[i].size(); j++) {
          literalIndex =
              literalWithPolarity(literalsListInclause[i][j]);
          if (literalsList[literalIndex] == -1) {
            unsetCount++;
            lastUnsetLiteral = j;
          } else if ((literalsList[literalIndex] == 0 && literalsListInclause[i][j] > 0) || (literalsList[literalIndex] == 1 && literalsListInclause[i][j] < 0)) {
            falseCount++;
          } else {
            satisfiedFlag = true;
            break;
          }
        }
        if (satisfiedFlag) {
          continue;
        }
        if (unsetCount == 1) {
          fullLiteral(literalsListInclause[i][lastUnsetLiteral],
                        decisionLevel, i);
          clauseFound = true;
          break;
        } else if (falseCount == literalsListInclause[i].size()) {
          degreeAntecedent = i;
          return 1;
        }
      }
    }

    degreeAntecedent = -1;
    return 2;
  }

  void fullLiteral(int variable, int decisionLevel, int antecedent) {
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

  void unfullLiteral(int literalIndex) {
    literalsList[literalIndex] = -1;
    literalDecisionLevel[literalIndex] = -1;
    literalPast[literalIndex] = -1;
    frequency[literalIndex] = BackTrackFrequency[literalIndex]; 
    assignedLiteralCount -= 1;
  }

  int literalWithPolarity(int variable) {
    if (variable > 0) {
      return variable - 1;
    } else {
      return -variable - 1;
    }
  }


  int backtrack(int decisionLevel) {
    vector<int> clause = literalsListInclause[degreeAntecedent];
    int conflictLevel = decisionLevel;
    int thisLevelConflictCount = 0;       
    int ConflictSolverLiteral;
    int literal;

    thisLevelConflictCount = 0;
    for (int i = 0; i < clause.size(); i++) {
      literal = literalWithPolarity(clause[i]);
      if (literalDecisionLevel[literal] == conflictLevel) {
        thisLevelConflictCount++;
      }
      if (literalDecisionLevel[literal] == conflictLevel &&
          literalPast[literal] != -1) {
        ConflictSolverLiteral = literal;
      }
    }
    clause = ConflictSolve(clause, ConflictSolverLiteral);

    while (true) {
      thisLevelConflictCount = 0;
      for (int i = 0; i < clause.size(); i++) {
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
    for (int i = 0; i < clause.size(); i++) {
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
    for (int i = 0; i < clause.size(); i++) {
      int literalIndex = literalWithPolarity(clause[i]);
      int decisionLevelOnThisLevel = literalDecisionLevel[literalIndex];
      if (decisionLevelOnThisLevel != conflictLevel && decisionLevelOnThisLevel > BacktrackeddecisionLevel) {
        BacktrackeddecisionLevel = decisionLevelOnThisLevel;
      }
    }
    for (int i = 0; i < literalsList.size(); i++) {
      if (literalDecisionLevel[i] > BacktrackeddecisionLevel) {
        unfullLiteral(i);
      }
    }
    return BacktrackeddecisionLevel;
  }

  vector<int> &ConflictSolve(vector<int> &input, int literal) {
    vector<int> input_2 = literalsListInclause[literalPast[literal]];
    input.insert(input.end(), input_2.begin(), input_2.end());
    for (int i = 0; i < input.size(); i++) {
      if (input[i] == literal + 1 || input[i] == -literal - 1) {
        input.erase(input.begin() + i);
        i--;
      }
    }
    sort(input.begin(), input.end());
    input.erase(unique(input.begin(), input.end()), input.end());
    return input;
  }

  int VariableChoice() {
    bool too_many_attempts = false;
    int attempts = 0;
    uniform_int_distribution<int> chooseBranch(1, 11);
    uniform_int_distribution<int> chooseVariable(0, literalCount);
    int BranchChosen = chooseBranch(generator);
    if (BranchChosen > 4 || assignedLiteralCount < literalCount / 2 || too_many_attempts) {
      pickedVariablesCounters++;
      if (pickedVariablesCounters == 20 * literalCount) {
        for (int i = 0; i < literalsList.size(); i++) {
          BackTrackFrequency[i] /= 2;
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
      while (attempts < 10 * literalCount) {
        int variable = chooseVariable(generator);
        if (frequency[variable] != -1) {
          if (polarity[variable] >= 0) {
            return variable + 1;
          }
          return -variable - 1;
        }
        attempts++;
      }
      too_many_attempts = true;
    }
    while (too_many_attempts) {
      if (BranchChosen > 4 || assignedLiteralCount < literalCount / 2 || too_many_attempts) {
        pickedVariablesCounters++;
        if (pickedVariablesCounters == 20 * literalCount) {
          for (int i = 0; i < literalsList.size(); i++) {
            BackTrackFrequency[i] /= 2;
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
        while (attempts < 10 * literalCount) {
          int variable = chooseVariable(generator);
          if (frequency[variable] != -1) {
            if (polarity[variable] >= 0) {
              return variable + 1;
            }
            return -variable - 1;
          }
          attempts++;
        }
        too_many_attempts = true;
      }
    }
    return 0;
  }

  

};


int main() {
  Solver solver;
  solver.launch();
  return 0;
}
