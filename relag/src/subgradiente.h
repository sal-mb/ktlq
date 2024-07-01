#pragma once 

#include <numeric>
#include <vector>
#include "Kruskal.h"
#include "bnb.h"
#include "data.h"
#include "bnb.h"

inline void melhor_no(Node &best, double w, vector<double> lmb, vii edges, pair<int,int> best_nodes); 

Node subgradiente(double ub, int n, vvi cost_matrix, vector<double> lmb, Node node);

vector<int> calcula_graus_msp(vii msp, pair<int,int> best_nodes);

double tamanho_do_passo(double upper_bound, double w, vector<int> graus, Node &node);

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus);

vvi altera_custos(vvi custos, vector<double> lmb);

pair<int,int> melhores_nos_0(vvi custos, double partial_cost, int n, vii edges);
