#include "Columns.h"
#include <cstdlib>
vector<vector<bool>> initColumns(const int n){
  vector<vector<bool>> columns(n, vector<bool>(n));

  for(int i = 0; i < n; i++){
    columns[i][i] = 1;
  }
  return columns;
}

std::pair<int,int> getBestToSepJoin(const vector<vector<bool>> &columns, const vector<double> &lambda, const int &n){

  vector<vector<double>> z_ij(n, vector<double>(n));

  double best_z = 1;

  std::pair<int, int> best = std::make_pair(0, 0);

  for (int i = 0; i < n; i++) {

    for (int j = i + 1; j < n; j++) {

      for (int k = n; k < lambda.size(); k++) {
        if (columns[k][i] == true && columns[k][j] == true) {

          z_ij[i][j] += lambda[k];

          if (std::abs(z_ij[i][j] - 0.5) < best_z) {

            best_z = std::abs(z_ij[i][j] - 0.5);
            best.first = i;
            best.second = j;
          }
        }
      }
    }
  }
  return best;
}

int computeSolution(Node &node,const vector<double> &solution){
  
  // Objetive value for the bin packing problem
  int value = 0; 
  
  node.feasible = true;

  for(auto k : solution){
    // If lambda[k] is a potential bin
    if(k > 0){
      value++;
      if(k != 1){
        node.feasible = false;
      }
    }
  }

  return value;
}


