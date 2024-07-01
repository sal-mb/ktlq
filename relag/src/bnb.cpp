#include "bnb.h"
#include <cstdio>
#include <iterator>
#include <list>
#include <utility>
#include <vector>
#include <unistd.h>
#include "prints.h"
#include "subgradiente.h"

vector<int> calcula_graus(vii arestas){

    vector<int> graus(arestas.size(), 0);

    for(int i = 0; i < arestas.size(); i++){
        graus[arestas[i].first]++;    
        graus[arestas[i].second]++;    
    }

    return graus;
}

vector<pair<int,int>> arestas_para_proibir(vii arestas){

    vector<int> graus = calcula_graus(arestas);

    int no_maior_grau = 0;
    int maior_grau = 0;

    //acha o nó de maior grau
    for(int i = 0; i < graus.size(); i++){
        if(graus[i] > maior_grau){
            no_maior_grau = i;
            maior_grau = graus[i];
        }
    }

    vector<pair<int,int>> arestas_proibidos;

    //adiciona os arestas do no de maior grau ao vetor de arestas proibidos
    for(int i = 0; i < arestas.size(); i++){
        if(arestas[i].first == no_maior_grau || arestas[i].second == no_maior_grau){
            arestas_proibidos.push_back(make_pair(arestas[i].first, arestas[i].second));
        }
    }

    return arestas_proibidos;
}

void proibe_arestas(Node &no, vvi &cost_matrix){

    for(int i = 0; i < no.arestas_proibidos.size(); i++){
        cost_matrix[no.arestas_proibidos[i].first][no.arestas_proibidos[i].second] = 99999999;
        cost_matrix[no.arestas_proibidos[i].second][no.arestas_proibidos[i].first] = 99999999;
    }
}

Node bnb(int branching, vvi cost_matrix, double tsp_heuristic, int n){

    // n = tamanho da instancia

    //inicializacao da arvore
    vector<double> lmb(n,0);

    Node root; 
    root = subgradiente(tsp_heuristic, n, cost_matrix, lmb, root);

    std::list<Node> tree;
    tree.push_back(root);

    //definindo o upperbound a partir da solucao heuristica disponivel
    double upper_bound = tsp_heuristic;

    Node best_node;
    
    while(!tree.empty()){

        list<Node>::iterator node = branching ? tree.begin() : std::prev(tree.end()); //1 - bfs, 0 - dfs;

        if(node->cost <= upper_bound){
           
            if(node->feasible){
                
                upper_bound = node->cost;
                best_node = (*node);

            }else{
                
                vector<pair<int,int>> arestas = arestas_para_proibir(node->arestas);

                for(int i = 0; i < arestas.size(); i++){

                    // cout << arestas[i].first << " -> " << arestas[i].second;
                    Node no;

                    //herda os arestas proibidas e os penalizadores do nó pai

                    no.arestas_proibidas = node->arestas_proibidas; 
                    no.penalizadores = node->penalizadores;

                    no.arestas_proibidas.push_back(arestas[i]);

                    vvi custos_arestas_proibidos = cost_matrix;
                    proibe_arestas(no, custos_arestas_proibidos);

                    // cout << " - custo: " << custos_arestas_proibidos[arestas[i].first][arestas[i].second] << " = " << custos_arestas_proibidos[arestas[i].second][arestas[i].first] << endl;
                    no = subgradiente(tsp_heuristic, n, custos_arestas_proibidos, no.penalizadores, (*node));

                    vector<int> graus = calcula_graus(no.arestas);

                    if(no.cost < upper_bound){
                        tree.push_back(no);
                        cout << no.cost << endl;

                    }
                }  
            }
        }

        tree.erase(node);
    }

    return best_node;
}
