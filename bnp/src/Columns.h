#ifndef COLUMNS_H
#define COLUMNS_H

#include <vector>
#include "Bnp.h"
using std::vector;

vector<vector<bool>> initColumns(const int n, Node &node);
std::pair<int,int> getBestToSepJoin(const Node &node, const vector<vector<bool>> &columns, const vector<double> &lambda, const int &n);
double computeSolution(Node &node, const vector<double> &solution);

#endif // !COLUMNS_h
