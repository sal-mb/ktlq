#include "bnb.h"
#include "hungarian.h"
#include "subtours.h"

void init_node(Node *node, hungarian_problem_t *p){
    node->lower_bound = hungarian_solve(p);
    node->chosen = 0;
    node->subtours = detecta_subtours(p);
    node->viable = node->subtours.size()-1 ? true : false;
}

void bnb(hungarian_problem_t *p){
    Node root;
    init_node(&root, p);
    root.forbidden_arcs.clear();

    std::list<Node> tree;
    tree.push_back(root);


}