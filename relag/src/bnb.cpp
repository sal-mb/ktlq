#include "bnb.h"
#include "hungarian.h"
#include "subtours.h"
#include <iterator>
#include <list>
#include <vector>
#include <unistd.h>


void print_node_solution (Node *node){

    for(int i = 0; i < node->subtours.size()-1; i++){
        std::cout << node->subtours[i] +1 << " -> ";
    }
    std::cout << node->subtours[node->subtours.size()-1] +1<< std::endl;
    
}

void init_node(Node *node, hungarian_problem_t *p, double **cost){
    
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
    

    hungarian_init(p, cost_, p->num_rows, p->num_cols, HUNGARIAN_MODE_MINIMIZE_COST);
    node->lower_bound = hungarian_solve(p);

    node->subtours = detecta_subtours(p);
    node->viable = p->num_rows - (node->subtours.size() - 1) ? false : true;

    
    //deleta a matriz de custos e o hungarian_problem_t
    for (int i = 0; i < p->num_rows; i++) delete [] cost_[i];
	delete [] cost_;
    hungarian_free(p);
}

Node bnb(hungarian_problem_t *p, int branching, double** cost, double tsp_heuristic){

    //inicializacao da arvore
    Node root;
    root.forbidden_arcs.clear();
    init_node(&root, p, cost); 

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
                
                upper_bound = node->lower_bound;
                best_node = (*node);

            }else{
                for(int i = 0; i < node->subtours.size()-1; i++){
                    Node n;

                    n.forbidden_arcs = node->forbidden_arcs; //herda os arcos do nó pai

                    std::pair<int, int> forbid = {
                        node->subtours[i] ,
                        node->subtours[i+1]
                    };

                    n.forbidden_arcs.push_back(forbid); //proibe arcos novos

                    init_node(&n, p, cost); // resolve o algoritmo hungaro com as novas restricoes e determina se eh uma solucao para o tsp

                
                    if(n.lower_bound < upper_bound){
                        tree.push_back(n);
                    }
                }
            }
        }
        tree.erase(node);
    }

    return best_node;
}
