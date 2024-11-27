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

    // Solving the master problem
    vector<double> solution = Bnp::solveMaster(data, M, node, rmp, columns);

    int obj_value = 999999999;
    if (!solution.empty()) {
      // Getting the objective value for bin packing from the solution
      obj_value = computeSolution(*node, solution);
      cout << "text: " << obj_value << endl;
      printVector(solution);
    }
    if (obj_value < best_obj_value) {

      if (node->feasible) {
        best_obj_value = obj_value;
        cout << "best: " << best_obj_value << endl;

      } else {

        std::pair<int, int> best = getBestToSepJoin(*node, columns, solution, n);
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

#if DEBUG
  cout << "Separating and or Joining Items... " << endl;
#endif // DEBUG

  // SepJoining the items in the master problem
  rmp.sepJoinItems(node->items, node->sep_join, node->columns, column_matrix);
  rmp.solver = IloCplex(rmp.model);
  rmp.solver.setOut(rmp.env.getNullStream());
  rmp.solve();
  cout << rmp.solver.getStatus() << endl;
#if DEBUG
  cout << "Initial lower bound: " << rmp.getObjValue() << endl;
  cout << "Initial solution: ";
  rmp.printSolution();
  cout << endl;
#endif // DEBUG

  int lambda_counter = n;

  while (true) {
    if (rmp.solver.getStatus() != IloAlgorithm::Optimal) {
      rmp.unSepJoinItems(node->items, node->sep_join);
      getchar();
      return {};
    }

    // Get the dual variables
    IloNumArray pi = rmp.getDuals();

#if DEBUG
    for (size_t i = 0; i < n; i++) {
      cout << "Dual variable of constraint " << i << " = " << pi[i] << endl;
    }
#endif // DEBUG

    // Build and solve the pricing problem
    Pricing pricing_problem(n, weights, pi, capacity);
    pricing_problem.sepJoinItems(node->items, node->sep_join);
    pricing_problem.solve();
    // ----------------------------------------------------------------------

    if (pricing_problem.getObjValue() < -1e-5) {

#if DEBUG
      cout << "Reduced cost is equal to " << pricing_problem.getObjValue() << ", which is less than 0..." << endl;
#endif // DEBUG

      IloNumArray entering_col = pricing_problem.getColumn();
      vector<bool> bool_col = pricing_problem.getBoolColumn();

      // Adding the generated column to the column matrix
      column_matrix.push_back(bool_col);
      node->columns.push_back(column_matrix.size() - 1);

#if DEBUG
      pricing_problem.printSolution();
#endif // DEBUG

      rmp.addNewLambda(entering_col, ++lambda_counter);

      rmp.solve();

    } else {
      break;
    }
  }

  // Gets the lambda values from the model
  vector<double> lambda = rmp.getSolution();

  // UnSepUnJoining items
  rmp.unSepJoinItems(node->items, node->sep_join);

  return lambda;
}
