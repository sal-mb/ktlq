#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>
#include "Data.h"

typedef struct Solucao{
    std::vector<int> sequencia;
    double custoS = 0; //custo da solução
    double custoA = 0; //custo acumulado da solução

} Solucao;

void exibir_solucao(Solucao &s, Data *dados);

void calcula_custoS(Solucao &s, Data *dados);

void calcula_custoA(Solucao &s, Data *dados);

Solucao perturbacao(Solucao &s, Data *data);

#endif