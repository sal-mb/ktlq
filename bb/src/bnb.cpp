#include "bnb.h"
#include "hungarian.h"
#include "subtours.h"
#include <cstdio>
#include <iterator>
#include <limits>
#include <vector>
#include <unistd.h>

void print_cost_matrix(Node *node, hungarian_problem_t *p){
    std::cout << "cost matrix: "<<std::endl;

    for(int i = 0; i < p->num_rows; i++){
        for(int j = 0; j < p->num_cols; j++){
            std::cout << node->cost_[i][j]<<" ";
        }
        printf("\n");
    }
}

void print_viable(Node *node){

    if(!node->viable) return;
    for(int i = 0; i < node->subtours[0].size()-1; i++){
        std::cout << node->subtours[0][i] +1 << " -> ";
    }
    std::cout << node->subtours[0][node->subtours.size()-1] +1<< std::endl;

    std::cout << "Cost: " << node->lower_bound << std::endl;
}

void erase_node(std::list<Node>::iterator &node, hungarian_problem_t *p, std::list<Node> &tree){
    for (int i = 0; i < p->num_rows; i++) delete [] node->cost_[i];
	delete [] node->cost_;
    tree.erase(node);
}

void erase_tree(std::list<Node> &tree);

void init_cost(Node *node, hungarian_problem_t *p, double** cost){
    double **cost_ = new double*[p->num_rows]; //copia matriz custo original
	for (int i = 0; i < p->num_rows; i++){
		cost_[i] = new double[p->num_cols];
		for (int j = 0; j < p->num_cols; j++){
			cost_[i][j] = cost[i][j];
		}
	}

    for(int i = 0; i < node->forbidden_arcs.size(); i++){ //proibe os arcos na matrix copiada
        std::pair<int,int> forbid = node->forbidden_arcs[i]; 
        cost_[forbid.first][forbid.second] = 99999999;
    }
    
    node->cost_ = cost_;
}

void init_node(std::list<Node>::iterator &node, hungarian_problem_t *p){

    hungarian_init(p, node->cost_, p->num_rows, p->num_cols, HUNGARIAN_MODE_MINIMIZE_COST);
    node->lower_bound = hungarian_solve(p);

    node->chosen = 0;
    node->subtours = detecta_subtours(p);
    node->viable = node->subtours.size()-1 ? false : true;
}

void bnb(hungarian_problem_t *p, int branching, double** cost){

    Node root;
    root.forbidden_arcs.clear();
    init_cost(&root, p, cost);
    root.chosen = 9999;
    std::list<Node> tree;
    tree.push_back(root);

    std::list<Node>::iterator ri = tree.begin();
    
    double upper_bound = 2086;

    std::vector<Node> viable_solutions;

    while(1){
        printf("tamanho: %zu\n", tree.size());
        std::list<Node>::iterator node = branching ? tree.begin() : std::prev(tree.end()); //1 - bfs, 0 - dfs;

        init_node(node, p); // resolve o algoritmo hungaro com as restricoes e determina se eh uma solucao para o tsp

        if(node->lower_bound < upper_bound){
            
            if(node->viable){
                upper_bound = node->lower_bound;
                print_viable(&(*node));
                break;

            }else{
                for(int i = 0; i < node->subtours[0].size()-1; i++){
                    Node n;
                    n.forbidden_arcs = node->forbidden_arcs;

                    std::pair<int, int> forbid = {
                        node->subtours[0][i] ,
                        node->subtours[0][i+1]
                    };
                    
                    n.forbidden_arcs.push_back(forbid);

                    init_cost(&n, p, node->cost_);
                    
                    tree.push_back(n);
                }
            }
        }

        erase_node(node, p, tree);
    }

    erase_tree(tree);
}