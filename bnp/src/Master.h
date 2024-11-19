#include <list>
#include <vector>
#include "prints.h"

#ifndef MASTER_H
#define MASTER_H

#include <ilcplex/ilocplex.h>

using std::vector;

class Master {
  public:
  int n;
  IloEnv env;
  IloModel model;
  IloNumVarArray lambda;
  IloRangeArray constraints;
  IloExpr objective_expression;
  IloObjective objective;
  IloCplex solver;

  // vectors to compute the branching faster
  vector<int> sep_lambdas;
  vector<int> join_lambdas;

  Master(const int& n = 0, const double& M = 1e6);
  ~Master();
  void solve();
  IloNumArray getDuals();
  void addNewLambda(const IloNumArray& entering_col, const int lambda_index);
  void printSolution();
  std::vector<double> getSolution();
void sepJoinItems(const vector<std::pair<int, int>>& items, const vector<bool>& sep_join, const vector<int> &columns, const vector<vector<bool>>& column_matrix);
  void unSepJoinItems(const vector<std::pair<int, int>> &items, const vector<bool> &sep_join);
  double getObjValue();
};
#endif
