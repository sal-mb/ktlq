#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <vector>
#include "Data.h"

typedef struct Aresta{
    int x;
    int y;
}Aresta;

typedef struct Solucao{
    std::vector<int> sequencia;
    double custoS = 0;
} Solucao;

typedef struct Insercao{
    int k_Inserido;
    Aresta a_Removida;
    double custoI;
}Insercao;

void exibir_solucao(Solucao *s);

void exibir_custo_de_insercao(std::vector<Insercao> *custosInsercao);

void ordena_custos(std::vector<Insercao> *custosInsercao);

void calcula_custoS(Solucao *s, Data *dados);

Solucao* construcao(Solucao *s, Data *dados);

void inserir_em_s(Solucao *s, Solucao *resto, Insercao no);

Solucao* gera_S_aletaoria(Solucao *s);

Solucao* nosRestantes(Solucao *s, Solucao *gerada);

std::vector<Insercao> calcula_custo_insercao(Solucao *s, Solucao *resto, Data *dados);



#endif