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
    vector<pair<int,int>> arestas_proibidas;
    double cost;

    bool feasible = false;
}Node;

Node bnb(int branching, vvi cost_matrix, double tsp_heuristic, int n);

vector<int> calcula_graus(vii arestas);

vector<pair<int,int>> arestas_para_proibir(vii arestas);

void proibe_arestas(Node &no, vvi &cost_matrix);

#endif