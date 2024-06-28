#pragma once 

#include <numeric>
#include <vector>
#include "Kruskal.h"
#include "data.h"

typedef struct solucao_t{
    vii arestas;
    vector<double> penalizadores;
    double cost;

}solucao_t;

inline solucao_t melhor_solucao(double w, vector<double> lmb, vii edges, pair<int,int> best_nodes); 

solucao_t subgradiente(double ub_heuristico, int n, vvi cost_matrix);

vector<int> calcula_graus(vii msp, int n, pair<int,int> best_nodes);

double tamanho_do_passo(double upper_bound, double w, vector<int> graus);

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus);

vvi altera_custos(vvi custos, vector<double> lmb);

pair<int,int> melhores_nos_0(vvi custos, double partial_cost, int n, vii edges);
