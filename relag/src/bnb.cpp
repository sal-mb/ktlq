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

vector<pair<int,int>> arcos_para_proibir(vii arestas){

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

    vector<pair<int,int>> arcos_proibidos;

    //adiciona os arcos do no de maior grau ao vetor de arcos proibidos
    for(int i = 0; i < arestas.size(); i++){
        if(arestas[i].first == no_maior_grau || arestas[i].second == no_maior_grau){
            arcos_proibidos.push_back(make_pair(arestas[i].first, arestas[i].second));
        }
    }

    return arcos_proibidos;
}

void proibe_arcos(Node &no, vvi &cost_matrix){

    for(int i = 0; i < no.arcos_proibidos.size(); i++){
        cost_matrix[no.arcos_proibidos[i].first][no.arcos_proibidos[i].second] = 99999999;
    }
    
    //associa a nova matriz de custos ao no
    no.matriz_de_custos = cost_matrix;
}

Node bnb(int branching, vvi cost_matrix, double tsp_heuristic, int n){

    // n = tamanho da instancia

    //inicializacao da arvore
    vector<double> lmb(n,0);

    Node root = subgradiente(tsp_heuristic, n, cost_matrix, lmb);

    std::list<Node> tree;
    tree.push_back(root);

    //definindo o upperbound a partir da solucao heuristica disponivel
    double upper_bound = tsp_heuristic;

    Node best_node;
    
    while(!tree.empty()){
        cout << tree.size() << endl;
        sleep(1);
        list<Node>::iterator node = branching ? tree.begin() : std::prev(tree.end()); //1 - bfs, 0 - dfs;

        if(node->cost <= upper_bound){
           
            if(node->feasible){
                
                upper_bound = node->cost;
                best_node = (*node);

            }else{
                
                vector<pair<int,int>> arcos = arcos_para_proibir(node->arestas);

                for(int i = 0; i < arcos.size(); i++){
                    cout << arcos[i].first << " -> " << arcos[i].second << " / ";
                    sleep(1); 
                    Node no;

                    //herda os arcos proibidos e os penalizadores do nó pai

                    no.arcos_proibidos = node->arcos_proibidos; 
                    no.penalizadores = node->penalizadores;

                    no.arcos_proibidos.push_back(arcos[i]);

                    vvi custos_arcos_proibidos = cost_matrix;
                    proibe_arcos(no, custos_arcos_proibidos);

                    no = subgradiente(upper_bound, n, no.matriz_de_custos, no.penalizadores);

                    if(no.cost < upper_bound){
                        tree.push_back(no);
                        // print_subgradiente(calcula_graus(no.arestas));
                        // print_no(no);
                    }
                    getchar();
                }  
            }
        }
        tree.erase(node);
    }

    return best_node;
}
