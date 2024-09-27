#ifndef MASTER_H
#define MASTER_H

#include <ilcplex/ilocplex.h>

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

  Master(const int &n = 0, const double &M = 1e6);

  void solve();
  IloNumArray getDuals();
  void addNewLambda(const IloNumArray &entering_col, const int lambda_index);
  void printSolution();
  double getObjValue();
};
#endif
