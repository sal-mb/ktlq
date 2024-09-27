
#include "Pricing.h"

using std::cout, std::endl;
Pricing::Pricing(const int &n, const std::vector<int> &weights,
                 const IloNumArray &duals, const int &capacity) {
  
  this->n = n;
  this->x = IloBoolVarArray(env, n);
  this->model = IloModel(env);
  this->objective_expression = IloExpr(env);
  this->constraints = IloExpr(env);
  
  // Setting Objective Function
  this->objective_expression += 1;

  for (int i = 0; i < n; i++) {
    char var_name[50];
    sprintf(var_name, "x%d", i);

    this->x[i].setName(var_name);
    
    this->objective_expression -= duals[i] * this->x[i];
  }
  
  this->objective = IloMinimize(env,this->objective_expression);
  this->model.add(this->objective);

  //Setting constraints
  for(int i = 0; i < n; i++){
    this->constraints += weights[i] * this->x[i];
  }

  this->model.add(constraints <= capacity);

  this->solver = IloCplex(this->model);
  this->solver.setOut(env.getNullStream());
}

void Pricing::solve() { this->solver.solve(); }

double Pricing::getObjValue() { return this->solver.getObjValue(); }

IloNumArray Pricing::getColumn(){
  IloNumArray column(env, this->x.getSize());
 this->solver.getValues(this->x, column);
  return column;
}
