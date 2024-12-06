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
    int lb = 99999;
    bool root = false; // Variable to know if the node is root, so i can use the combo algorithm
} Node;

namespace Bnp {

// Returns the item pair to separate/join
vector<double> solveMaster(Data& data, const double& M, const std::list<Node>::iterator& node, Master& rmp, vector<vector<bool>>& columns);
vector<double> solveMasterRoot(Data& data, const double& M, const std::list<Node>::iterator& node, Master& rmp, vector<vector<bool>>& columns);
int run(Data& data, const double& M = 1e6, const int branching = 0);

} // namespace Bnp
#endif
