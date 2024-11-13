#ifndef PRICING_H
#define PRICING_H

#include <ilcplex/ilocplex.h>
#include <vector>

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

  void solve();
  double getObjValue();
  IloNumArray getColumn();
  void printSolution();
};
#endif
