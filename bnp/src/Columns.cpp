#include "Columns.h"
#include <cstdlib>
vector<vector<bool>> initColumns(const int n, Node& node) {
  vector<vector<bool>> columns(n, vector<bool>(n));

  for (int i = 0; i < n; i++) {
    node.columns.push_back(i);
    columns[i][i] = 1;
  }
  return columns;
}

std::pair<int, int> getBestToSepJoin(Node& node, const vector<vector<bool>>& columns, const vector<double>& lambda, const int& n) {

  vector<vector<double>> z_ij(n, vector<double>(n, 0));

  double best_z = 0.5;

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

      if (std::abs(z_ij[i][j] - 0.5) <= best_z) {

        best_z = std::abs(z_ij[i][j] - 0.5);
        best.first = i;
        best.second = j;
      }
    }
  }
  if (std::abs(0.5 - best_z) <= 0.001) {
    best = { 0, 0 };
    node.feasible = true;
  }

  return best;
}

int computeSolution(Node& node, const vector<double>& solution) {

  double obj_value = 0;

  for (auto k : solution) {
    if (k > 0) {
      obj_value += k;
    }
  }

  return std::ceil(obj_value);
}
