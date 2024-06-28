#ifndef BNB_H
#define BNB_H
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <list>

typedef struct Node{

    std::vector<std::pair<int, int>> forbidden_arcs;
    std::vector<int> subtours;
    double lower_bound = 0; 
    bool viable = false;
    
}Node;

Node bnb(int branching, double** cost, double tsp_heuristic);

#endif