#include "Data.h"
#include "Master.h"
#include <cstdlib>
#include <ilcplex/ilocplex.h>
#include <vector>
#include "Combo.h"
#include "Bnp.h"

using std::cout, std::endl, std::vector;

int main(int argc, char *argv[]) {
  const double M = 1e6;
  // vector<int> weight = {2, 1, 3, 3, 5};
  // int capacity = 7;
  // int n = weight.size();
  Data data;
  data.readData(argv[1]);
  data.printData();

  Bnp::run(data);

  return 0;
}
