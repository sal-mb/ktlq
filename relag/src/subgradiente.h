#pragma once 

#include <numeric>
#include <vector>
#include "Kruskal.h"
#include "data.h"

typedef struct solucao_t{
    vii sequencia;
    double cost;

}solucao_t;

vector<double> subgradiente(double heuristic_ub, Data *data, vvi cost_matrix);

vector<int> calcula_graus(vii msp, int n);

double tamanho_do_passo(double upper_bound, double w, vector<int> graus);

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus);

vvi altera_custos(vvi custos, vector<double> lmb);

pair<int,int> insere_no_0(vvi custos, double partial_cost, Data *data, vii edges);
