#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "Solucao.h"
#include <vector>
#include "Data.h"

typedef struct Aresta{
    int x;
    int y;
}Aresta;

typedef struct Insercao{
    int k_Inserido;
    Aresta a_Removida;
    double custoI;
}Insercao;

void exibir_custo_de_insercao(std::vector<Insercao> *custosInsercao);

void inserir_em_s(Solucao *s, Solucao *resto, Insercao no);

std::vector<Insercao> calcula_custo_insercao(Solucao *s, Solucao *resto, Data *dados);

#endif