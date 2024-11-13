#ifndef BNP_H
#define BNP_H

#include "Data.h"
#include "Master.h"
#include "Pricing.h"

// items to separate/join
typedef struct best_ij{
  int i = -1;
  int j = -1;
}best_ij;

namespace Bnp{
  best_ij solveMaster(Data &data, const double &M = 1e6);
  void run(Data &data, const double &M = 1e6);
}
#endif
