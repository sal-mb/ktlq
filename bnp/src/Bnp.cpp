#include "Bnp.h"
#include "prints.h"
#include <list>
#include <utility>
#include <vector>
#include "Columns.h"

using std::cout, std::endl;
using std::vector;

void Bnp::run(Data& data, const double& M, const int branching) {
  int n = data.getNItems();
  Node root;

  std::list<Node> tree;
  tree.push_back(root);

  Node best_node;
  
  // Initializing the master problem 
  Master rmp(n, M);

  // Initializing the columns structure with the identity matrix
  vector<vector<bool>> columns = initColumns(n);

  while (!tree.empty()) {
    cout << "run start" << endl;
    getchar();
    // Getting the branching node
    std::list<Node>::iterator node = branching ? tree.begin() : std::prev(tree.end()); // 0 - bfs, 1 - dfs;
    
    // Solving the master problem
    vector<double> solution = Bnp::solveMaster(data, M, node, rmp, columns);
    cout << "solution: " << endl; 
    printVector(solution);
    getchar();

    // Branching separating items
    std::pair<int,int> best = getBestToSepJoin(columns, solution, n);
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

    tree.erase(node);
  }
}

vector<double> Bnp::solveMaster(Data& data, const double& M, const std::list<Node>::iterator& node, Master& rmp, vector<vector<bool>>& columns) {

  int n = data.getNItems();

  vector<int> weights = data.getWeights();
  int capacity = data.getBinCapacity();

  cout << "Separating and or Joining Items... " << endl;
  
  // SepJoining the items in the master problem
  rmp.sepJoinItems(node->items, node->sep_join,columns);

  rmp.solve();

  cout << "Initial lower bound: " << rmp.getObjValue() << endl;

  cout << "Initial solution: ";

  rmp.printSolution();

  cout << endl;

  int lambda_counter = n;

  while (true) {

    // Get the dual variables
    IloNumArray pi = rmp.getDuals();

    for (size_t i = 0; i < n; i++) {
      cout << "Dual variable of constraint " << i << " = " << pi[i] << endl;
    }

    // Build and solve the pricing problem
    Pricing pricing_problem(n, weights, pi, capacity);
    pricing_problem.sepJoinItems(node->items, node->sep_join);
    pricing_problem.solve();
    // ----------------------------------------------------------------------

    if (pricing_problem.getObjValue() < -1e-5) {

      cout << "Reduced cost is equal to " << pricing_problem.getObjValue()
           << ", which is less than 0..." << endl;

      IloNumArray entering_col = pricing_problem.getColumn();
      vector<bool> bool_col = pricing_problem.getBoolColumn();
      // Adding the generated column to the column matrix

      columns.push_back(bool_col);
      printColumns(columns);
      getchar();

      pricing_problem.printSolution();

      rmp.addNewLambda(entering_col, ++lambda_counter);
      cout << "Solving the RMP again..." << endl;

      rmp.solve();

    } else {
      cout << "No column with negative reduced costs found. The current basis "
              "is optimal"
           << endl;
      cout << "Final master problem: " << endl;

      rmp.printSolution();
      break;
    }
  }

  // Gets the lambda values from the model
  vector<double> lambda = rmp.getSolution();

  return lambda;
}
