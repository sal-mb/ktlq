#ifndef PRINTS_H
#define PRINTS_H
#include <iostream>
#include <vector>

using std::cout, std::endl;

void printColumns(std::vector<std::vector<bool>> columns);
void printZ_ij(std::vector<std::vector<double>> z_ij);
void printVector(std::vector<int> vector);
void printVector(std::vector<double> vector);
void printItems(std::vector<std::pair<int,int>> items);
void printSepJoin(std::vector<bool> sep_join);
#endif // !PRINTS_H
