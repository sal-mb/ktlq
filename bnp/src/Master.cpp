#include "Master.h"

using std::cout, std::endl;
using std::vector;

Master::Master(const int &n, const double &M) {
  this->n = n;
  this->model = IloModel(env);
  this->lambda = IloNumVarArray(env, n, 0, IloInfinity);
  this->objective_expression = IloExpr(env);
  this->constraints = IloRangeArray(env);

  for (int i = 0; i < n; i++) {
    char var_name[50];
    sprintf(var_name, "y%d", i);

    this->lambda[i].setName(var_name);
    this->objective_expression += M * this->lambda[i];

    this->constraints.add(this->lambda[i] == 1);
  }

  this->model.add(constraints);

  this->objective = IloMinimize(env, this->objective_expression);
  this->model.add(objective);

  this->solver = IloCplex(this->model);
  this->solver.setOut(env.getNullStream());
}

void Master::solve() { this->solver.solve(); }

IloNumArray Master::getDuals() {
  IloNumArray pi(this->env, this->n);
  this->solver.getDuals(pi, this->constraints);
  return pi;
}

void Master::addNewLambda(const IloNumArray &entering_col,
                          const int lambda_index) {
  char var_name[50];
  sprintf(var_name, "y%d", lambda_index);

  IloNumVar new_lambda(this->objective(1) + constraints(entering_col), 0,
                       IloInfinity);
  new_lambda.setName(var_name);

  this->lambda.add(new_lambda);
}

double Master::getObjValue() { return this->solver.getObjValue(); }

vector<double> Master::getSolution() {
  vector<double> solution(this->lambda.getSize());

  for(int i = 0; i < this->lambda.getSize(); i++){
    solution[i] = this->solver.getValue(this->lambda[i]);
  }

  return solution;
}

void Master::printSolution() {
  for (int i = 0; i < this->lambda.getSize(); i++) {
    cout << this->solver.getValue(this->lambda[i]) << " ";
  }
  cout << endl;
}
