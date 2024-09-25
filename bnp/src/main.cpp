#include "Data.h"
#include "Master.h"
#include "Pricing.h"
#include <cstdlib>
#include <ilcplex/ilocplex.h>
#include <vector>

using std::cout, std::endl, std::vector;

int main(int argc, char* argv[]) {
 const double M = 1e6;
 // vector<int> weight = {2, 1, 3, 3, 5};
 // int capacity = 7;
 // int n = weight.size();
  
  Data data;
  data.readData(argv[1]);
  
  int n = data.getNItems();
  vector<int> weights = data.getWeights();
  int capacity = data.getBinCapacity();
  Master rmp(n, M);

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

    pricing_problem.solve();
    // ----------------------------------------------------------------------

    if (pricing_problem.getObjValue() < -1e-5) {

      cout << "Reduced cost is equal to " << pricing_problem.getObjValue()
           << ", which is less than 0..." << endl;

      IloNumArray entering_col = pricing_problem.getColumn();

      cout << endl << "Entering column:" << endl;
      for (size_t i = 0; i < n; i++) {
        cout << (entering_col[i] < 0.5 ? 0 : 1) << endl;
      }
      cout << endl;

      rmp.addNewLambda(entering_col, ++lambda_counter);
      cout << "Solving the RMP again..." << endl;

      rmp.solve();

    } else {
      cout << "No column with negative reduced costs found. The current basis "
              "is optimal"
           << endl;
      cout << "Final master problem: " << endl;

      rmp.printSolution();
      system("cat model.lp");
      break;
    }
  }

  // cout << endl;
  // cout << "Forcing items 1 and 2 to be separated in the master (for
  // branch-and-price only): " << endl;
  // // 0 1 2 3 4 5 6 7 8 9 10 11
  // //
  // // 1 0 0 0 0 1 1 1 0 1  0  0
  // // 0 1 0 0 0 1 1 0 0 0  1  1
  // // 0 0 1 0 0 1 0 1 1 0  0  1
  // // 0 0 0 1 0 0 1 0 1 0  0  1
  // // 0 0 0 0 1 0 0 0 0 1  1  0

  // // itens 1 and 2 are together only on columns 5 and 11
  // lambda[11].setUB(0.0);
  // lambda[5].setUB(0.0);

  // // to allow them again:
  // // lambda[5].setUB(IloInfinity);
  // // lambda[11].setUB(IloInfinity);

  // rmp.solve();

  // for (size_t j = 0; j < lambda.getSize(); j++)
  // {
  // 	cout << rmp.getValue(lambda[j]) << " ";
  // }
  // cout << endl;

  return 0;
}
