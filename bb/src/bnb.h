#ifndef BNB_H
#define BNB_H
#include <iostream>
#include <utility>
#include <vector>
#include "hungarian.h"
typedef struct Node{

    std::vector<std::pair<int, int>> forbidden_arcs;
    std::vector<std::vector<int>> subtours;
    double lower_bound; 
    int chosen;
    bool viable;
    
}Node;

void bnb(hungarian_problem_t *p);

void init_node(Node *node, hungarian_problem_t *p);
#endif