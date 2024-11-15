
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

  this->objective = IloMinimize(env, this->objective_expression);
  this->model.add(this->objective);

  // Setting constraints
  for (int i = 0; i < n; i++) {
    this->constraints += weights[i] * this->x[i];
  }

  this->model.add(constraints <= capacity);

  this->solver = IloCplex(this->model);
  this->solver.setOut(env.getNullStream());
}

Pricing::~Pricing(){
  this->env.end();
}

void Pricing::solve() { this->solver.solve(); }

double Pricing::getObjValue() { return this->solver.getObjValue(); }

IloNumArray Pricing::getColumn() {
  IloNumArray column(env, this->x.getSize());
  this->solver.getValues(this->x, column);
  return column;
}

void Pricing::sepJoinItems(vector<std::pair<int,int>> items, vector<bool> sep_join){


  for(int i = 0; i < items.size(); i++){
    if(sep_join[i]){
      // Joining items
      this->model.add(this->x[items[i].first] == this->x[items[i].second]);     

    }else{
      // Separating items
      this->model.add(( this->x[items[i].first] + this->x[items[i].second] )<= 1);     

    }
  }
}

vector<bool> Pricing::getBoolColumn() {
  IloNumArray column(env, this->x.getSize());
  vector<bool> bool_column(n);

  this->solver.getValues(this->x, column);
  for(int i = 0; i < n; i++){
    bool_column[i] = column[i] < 0.5 ? false : true;
  }
  return bool_column;
}

void Pricing::printSolution() {
  for (int i = 0; i < this->x.getSize(); i++) {
    cout << this->solver.getValue(this->x[i]) << " ";
  }
  cout << endl;
}
