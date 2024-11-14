#ifndef COLUMNS_H
#define COLUMNS_H

#include <vector>
using std::vector;

vector<vector<bool>> initColumns(const int n);
std::pair<int,int> getBestToSepJoin(const vector<vector<bool>> &columns, const vector<double> &lambda, const int &n);

#endif // !COLUMNS_h
