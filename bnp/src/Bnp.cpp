#include "Bnp.h"
#include "Columns.h"
#include "prints.h"
#include <cmath>
#include <list>
#include <utility>
#include <vector>

using std::cout, std::endl;
using std::vector;

int Bnp::run(Data& data, const double& M, const int branching) {
  int n = data.getNItems();
  Node root;

  // Initializing the master problem
  Master rmp(n, M);

  // Initializing the columns structure with the identity matrix
  vector<vector<bool>> columns = initColumns(n, root);

  std::list<Node> tree;
  tree.push_back(root);

  int best_obj_value = n + 1;

  while (!tree.empty()) {
    // cout << tree.size() << endl;

    // Getting the branching node
    auto node = branching ? tree.begin() : std::prev(tree.end()); // 0 - dfs, 1 - bfs;

    node->lb = 9999;

    // Solving the master problem
    vector<double> solution = Bnp::solveMaster(data, M, node, rmp, columns);

    std::pair<int, int> best = { 0, 0 };

    if (!solution.empty()) {
      // If the column generation occurred without infeasible solutions 
      // Get the best pair to sep join
      best = getBestToSepJoin(*node, columns, solution, n);
      cout << "sol: " << node->lb << endl;
      cout << "best: " << best_obj_value << endl;
    }

    if (node->lb - best_obj_value <= -0.0001) {

      if (node->feasible) {
        best_obj_value = node->lb;
        cout << "best: " << best_obj_value << endl;

      } else {

        std::cout << best.first << ' ' << best.second << std::endl;

        if (!(best.first == 0 && best.second == 0)) {
          // Branching separating items
          Node sep = (*node);
          sep.items.push_back(best);

          // Pushing false in vector so we can know that we have to separate
          sep.sep_join.push_back(false);

          tree.push_back(sep);

          // Branching joining items
          Node join = (*node);
          join.items.push_back(best);

          // Pushing true in vector so we can know that we have to join
          join.sep_join.push_back(true);

          tree.push_back(join);
        }
      }
    }

    tree.erase(node);
    std::cout << tree.size() << std::endl;
  }
  cout << "solution: " << best_obj_value << endl;
  return best_obj_value;
}

vector<double> Bnp::solveMaster(Data& data, const double& M, const std::list<Node>::iterator& node, Master& rmp, vector<vector<bool>>& column_matrix) {

  int n = data.getNItems();

  vector<int> weights = data.getWeights();
  int capacity = data.getBinCapacity();

  // SepJoining the items in the master problem
  rmp.sepJoinItems(node->items, node->sep_join, column_matrix);
  rmp.solve();

  while (true) {

    if (rmp.solver.getStatus() != IloAlgorithm::Optimal) {
      rmp.unSepJoinItems(node->items, node->sep_join);
      cout << "UNOPTIMAL" << endl;
      return {};
    }

    // Get the dual variables
    IloNumArray pi = rmp.getDuals();

    // Build and solve the pricing problem
    Pricing pricing_problem(n, weights, pi, capacity);
    pricing_problem.sepJoinItems(node->items, node->sep_join);
    pricing_problem.solve();
    // ----------------------------------------------------------------------

    if (pricing_problem.solver.getStatus() != IloAlgorithm::Optimal) {
      rmp.unSepJoinItems(node->items, node->sep_join);
      cout << "UNOPTIMAL" << endl;
      return {};
    }
    if (pricing_problem.getObjValue() < -1e-5) {

      IloNumArray entering_col = pricing_problem.getColumn();
      vector<bool> bool_col = pricing_problem.getBoolColumn();

      // Adding the generated column to the column matrix
      column_matrix.push_back(bool_col);

      rmp.addNewLambda(entering_col);

      rmp.solve();

    } else {
      break;
    }
  }
  
  // Getting the objective value from the best solution
  node->lb = std::ceil(rmp.getObjValue() - 0.0001);

  // Gets the lambda values from the model
  vector<double> lambda = rmp.getSolution();

  // UnSepUnJoining items
  rmp.unSepJoinItems(node->items, node->sep_join);

  return lambda;
}
