#include "Columns.h"
#include <cstdlib>
vector<vector<bool>> initColumns(const int n, Node &node) {
  vector<vector<bool>> columns(n, vector<bool>(n));

  for (int i = 0; i < n; i++) {
    node.columns.push_back(i);
    columns[i][i] = 1;
  }
  return columns;
}

std::pair<int, int> getBestToSepJoin(const Node &node, const vector<vector<bool>>& columns, const vector<double>& lambda, const int& n) {

  vector<vector<double>> z_ij(n, vector<double>(n, 0));

  double best_z = 1;

  std::pair<int, int> best = std::make_pair(0, 0);

  for (int i = 0; i < n; i++) {

    for (int j = i + 1; j < n; j++) {

      for (auto k : node.columns) {
        if (columns[k][i] == true && columns[k][j] == true) {

          z_ij[i][j] += lambda[k];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {

      if (std::abs(z_ij[i][j] - 0.5) < best_z) {

        best_z = std::abs(z_ij[i][j] - 0.5);
        best.first = i;
        best.second = j;
      }
    }
  }
  return best;
}

double computeSolution(Node& node, const vector<double>& solution) {

  double obj_value = 0;

  node.feasible = true;

  for (auto k : solution) {
    if (k > 0) {
      obj_value += k;
      // if (k != 1) {
      // node.feasible = false;
      //}
    }
  }
  node.feasible = std::ceil(obj_value) - obj_value < 0.001;

  return obj_value;
}
