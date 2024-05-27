#ifndef BNB_H
#define BNB_H
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include "hungarian.h"

typedef struct Node{

    std::vector<std::pair<int, int>> forbidden_arcs;
    std::vector<int> subtours;
    double lower_bound = 0; 
    bool viable = false;
    
}Node;

Node bnb(hungarian_problem_t *p, int branching, double** cost, double tsp_heuristic);

void init_node(Node *node, hungarian_problem_t *p, double** cost);

void print_node_solution (Node *node);

#endif