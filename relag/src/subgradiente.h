#pragma once 

#include <numeric>
#include <vector>
#include "Kruskal.h"
#include "data.h"

typedef struct solucao_t{
    vii sequencia;
    double cost;

}solucao_t;

vector<double> subgradiente(double ub_heuristico, Data *data, vvi cost_matrix);

vector<int> calcula_graus(vii msp, int n, pair<int,int> best_nodes);

double tamanho_do_passo(double upper_bound, double w, vector<int> graus);

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus);

vvi altera_custos(vvi custos, vector<double> lmb);

pair<int,int> melhores_nos_0(vvi custos, double partial_cost, int n, vii edges);
