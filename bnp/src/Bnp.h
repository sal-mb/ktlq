#ifndef BNP_H
#define BNP_H

#include "Data.h"
#include "Master.h"
#include "Pricing.h"
#include <list>

typedef struct Node {
  vector<std::pair<int, int>> items; // This vector stores the pair of items to join or separate
  vector<bool> sep_join; // This vector tells if the items needs to bem separated (0 false) or joined (1 true)
  bool feasible = false;
} Node;

namespace Bnp {

// Returns the item pair to separate/join
vector<double> solveMaster(Data& data, const double& M, const std::list<Node>::iterator &node, Master &rmp, vector<vector<bool>> &columns);
void run(Data& data, const double& M = 1e6, const int branching = 1);

} // namespace Bnp
#endif
