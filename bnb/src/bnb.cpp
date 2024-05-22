#include "bnb.h"
#include "hungarian.h"
#include "subtours.h"
#include <cstdio>
#include <iterator>
#include <list>
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
    for(int i = 0; i < node->subtours.size()-1; i++){
        std::cout << node->subtours[i] +1 << " -> ";
    }
    std::cout << node->subtours[node->subtours.size()-1] +1<< std::endl;
    
}

void erase_node(std::list<Node>::iterator &node, hungarian_problem_t *p, std::list<Node> *tree){
    for (int i = 0; i < p->num_rows; i++) delete [] node->cost_[i];
	delete [] node->cost_;
    tree->erase(node);
}

void erase_tree(std::list<Node> *tree, hungarian_problem_t *p){
    while(!tree->empty()){
        std::list<Node>::iterator node = tree->begin();
        erase_node(node, p, tree);
    }
}

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

void init_node(Node *node, hungarian_problem_t *p){

    hungarian_init(p, node->cost_, p->num_rows, p->num_cols, HUNGARIAN_MODE_MINIMIZE_COST);
    node->lower_bound = hungarian_solve(p);

    node->subtours = detecta_subtours(p);
    node->viable = p->num_rows - (node->subtours.size() - 1) ? false : true;
}

Node bnb(hungarian_problem_t *p, int branching, double** cost, double tsp_heuristic){

    //inicializacao da arvore
    Node root;
    root.forbidden_arcs.clear();
    init_cost(&root, p, cost); //copia a matriz de custos para guardar a original

    init_node(&root, p);

    std::list<Node> tree;
    tree.push_back(root);

    //definindo o upperbound a partir da solucao heuristica disponivel
    double upper_bound = tsp_heuristic + 1;

    Node best_node;
    
    while(!tree.empty()){
        std::cout << tree.size() << std::endl;
        std::list<Node>::iterator node = branching ? tree.begin() : std::prev(tree.end()); //1 - bfs, 0 - dfs;

        if(node->lower_bound < upper_bound){
           
            if(node->viable){
                //caso o custo da solucao encontrada seja menor que o da heuristica
                //entao ela eh a otima
                //n sei se posso afirmar isso tqv
                upper_bound = node->lower_bound;
                best_node = (*node);

            }else{
                for(int i = 0; i < node->subtours.size()-1; i++){
                    Node n;
                
                    std::pair<int, int> forbid = {
                        node->subtours[i] ,
                        node->subtours[i+1]
                    };

                    n.forbidden_arcs.push_back(forbid); //proibe arcos novos
                    init_cost(&n, p, node->cost_); //define a matriz de custos dos nós com as novas restricoes, herdando a matriz do pai
                    init_node(&n, p); // resolve o algoritmo hungaro com as restricoes e determina se eh uma solucao para o tsp

                
                    if(n.lower_bound < upper_bound){
                        tree.push_back(n);
                    }
                }
            }
        }
        erase_node(node, p, &tree);
    }

    return best_node;
}
