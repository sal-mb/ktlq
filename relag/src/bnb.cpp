#include "bnb.h"
#include <iterator>
#include <list>
#include <vector>
#include <unistd.h>

Node bnb( int branching, double** cost, double tsp_heuristic){

    //inicializacao da arvore
    Node root;
    root.forbidden_arcs.clear();

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
