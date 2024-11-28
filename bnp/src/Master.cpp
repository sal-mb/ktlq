#include "Master.h"
#include "prints.h"
#include <vector>

using std::cout, std::endl;
using std::vector;

Master::Master(const int& n, const double& M) {
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

Master::~Master() {
  this->env.end();
  cout << "Master destroyed" << endl;
}

void Master::addNewLambda(const IloNumArray& entering_col) {

  IloNumVar new_lambda(this->objective(1) + constraints(entering_col), 0,
    IloInfinity);

  this->lambda.add(new_lambda);
}

void Master::sepJoinItems(const vector<std::pair<int, int>>& items, const vector<bool>& sep_join, const vector<vector<bool>>& column_matrix) {
  for (int i = 0; i < items.size(); i++) {
    // Joining the pair items[i]
    if (sep_join[i]) {
      for (int k = n; k < column_matrix.size(); k++) {
        if (column_matrix[k][items[i].first] != column_matrix[k][items[i].second]) {
          this->lambda[k].setUB(0);
        }
      }
    } else {
      // Separatings the pair items[i]
      for (int k = n; k < column_matrix.size(); k++) {
        // Setting the lambda UB = 0 so they cant be together
        if (column_matrix[k][items[i].first] == true && column_matrix[k][items[i].second] == true) {
          this->lambda[k].setUB(0);
        }
      }
    }
  }
}

void Master::unSepJoinItems(const vector<std::pair<int, int>>& items, const vector<bool>& sep_join) {

  for (int i = 0; i < lambda.getSize(); i++) {
    lambda[i].setUB(IloInfinity);
  }
}

double Master::getObjValue() { return this->solver.getObjValue(); }

vector<double> Master::getSolution() {
  vector<double> solution(this->lambda.getSize());

  for (int i = 0; i < this->lambda.getSize(); i++) {
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
