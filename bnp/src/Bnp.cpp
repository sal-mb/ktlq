#include "Bnp.h"

using std::cout, std::endl;
using std::vector;


void Bnp::run(Data &data, const double &M){
   
}

best_ij Bnp::solveMaster(Data &data, const double &M) {

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

  // Stores the all columns
  vector<vector<bool>> columns(n, vector<bool>(pow(2, n)));

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

      //cout << endl << "Entering column:" << endl;
      for (size_t i = 0; i < n; i++) {
        columns[i][lambda_counter] = entering_col[i] < 0.5 ? false : true;
      }
      //cout << endl;

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

  // Matrix to help getting the best itens to join or separate
  vector<vector<double>> z_ij(n, vector<double>(n));

  double best_z = 1;

  best_ij best = {.i = -1, .j = -1};

  for (int i = 0; i < n; i++) {

    for (int j = i + 1; j < n; j++) {

      for (int k = n; k < lambda.size(); k++) {
        if (columns[i][k] == true && columns[j][k] == true) {

          z_ij[i][j] += lambda[k];

          if (std::abs(z_ij[i][j] - 0.5) < best_z) {

            best_z = std::abs(z_ij[i][j] - 0.5);
            best.i = i;
            best.j = j;
          }
        }
      }
    }
  }
  
  cout << "i: " << best.i << ",j: " << best.j << endl;

  vector<int> prohibit;

  for(int i = n; i < lambda.size(); i++){
    if(columns[best.i][i] == true && columns[best.j][i] == true){
      rmp.lambda[i].setUB(0.0);
    }
  }
  rmp.solve();
  rmp.printSolution();
  return best;
}


