#ifndef PRICING_H
#define PRICING_H

#include <ilcplex/ilocplex.h>
#include <vector>

using std::vector;

class Pricing {
public:
  int n;
  IloEnv env;
  IloModel model;
  IloBoolVarArray x;
  IloExpr constraints;
  IloExpr objective_expression;
  IloObjective objective;
  IloCplex solver;

  Pricing(const int &n = 0, const std::vector<int> &weights = {},
          const IloNumArray &duals = {}, const int &capacity = 0);
  ~Pricing();
  void solve();
  double getObjValue();
  IloNumArray getColumn();
  vector<bool> getBoolColumn();
  void sepJoinItems(vector<std::pair<int,int>> items, vector<bool> sep_join);
  void printSolution();
};
#endif
