#ifndef PRINTS_H
#define PRINTS_H

#include "subgradiente.h"

void print_best_nodes_0(pair<int,int> best_nodes, vvi cost_matrix);

void print_edges(vii edges);

void print_penalizadores(vector<double> lmb);

void print_subgradiente(vector<int> graus);

void print_matriz_de_custo(vvi cost);

void print_solution(solucao_t s);

#endif
