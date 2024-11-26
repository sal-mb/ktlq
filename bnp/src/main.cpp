#include "Bnp.h"
#include "Combo.h"
#include "Data.h"
#include "Master.h"
#include "chrono"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <ilcplex/ilocplex.h>
#include <vector>

using std::cout, std::endl, std::vector;

int main(int argc, char* argv[]) {

  std::fstream fs;
  fs.open("t", std::fstream::app);
  const double M = 1e6;
  // vector<int> weight = {2, 1, 3, 3, 5};
  // int capacity = 7;
  // int n = weight.size();

  Data data;
  data.readData(argv[1]);
  data.printData();

  auto start = std::chrono::high_resolution_clock::now();

  int best_value = Bnp::run(data);

  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  fs << "bins: " << best_value << endl;
  fs << "duration: " << (double)duration.count()/1000 << endl; 
  return 0;
}
