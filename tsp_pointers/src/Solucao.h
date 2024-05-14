#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>
#include "Data.h"

typedef struct Solucao{
    std::vector<int> sequencia;
    double custoS = 0;
} Solucao;

void exibir_solucao(Solucao *s);


void calcula_custoS(Solucao *s, Data *dados);

Solucao* construcao(Solucao *s, Data *dados);

Solucao* gera_S_aletaoria(Solucao *s);

Solucao* nosRestantes(Solucao *s, Solucao *gerada);

Solucao* perturbacao(Solucao *s, Data *data);

#endif