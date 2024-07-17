#ifndef BNB_H
#define BNB_H
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include "Kruskal.h"

typedef struct Node{
    vii arestas;
    vector<double> penalizadores;
    vvi matriz_de_custo;
    double cost;

    bool feasible = false;

    // funcao para ordenar a priority_queue
    bool operator<(const Node &n) const
    {
        return cost > n.cost;
    }

}Node;

Node bnb(int branching, vvi cost_matrix, double tsp_heuristic, int n);

Node bnb_bestbound(vvi cost_matrix, double tsp_heuristic, int n);

vector<int> calcula_graus(vii arestas);

vector<pair<int,int>> arestas_para_proibir(vii arestas);

vvi proibe_arestas(vii arestas, vvi cost_matrix);

#endif
