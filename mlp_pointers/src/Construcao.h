#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "Solucao.h"
#include <vector>
#include "Data.h"


typedef struct Insercao{
    int no;
    double custo; //custo em relacao a r
}Insercao;

Solucao* construcao(Solucao *s, Data *dados);

std::vector<Insercao> calcula_custo_em_relacao_a_r(Solucao *cl, int r, Data *dados);

#endif