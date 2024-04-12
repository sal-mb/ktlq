#ifndef SUBSEQUENCIA_H
#define SUBSEQUENCIA_H

#include "Solucao.h"
#include <vector>

typedef struct Subsequencia{
    double T, C;
    int W;
    int primeiro_pos, ultimo_pos;
}Subsequencia;

void exibir_subSeq(Subsequencia &subseq, Solucao *s);

void exibir_matrizSubSeq(std::vector<std::vector<Subsequencia>> &subSeqMatrix, Solucao *s);

Subsequencia Concatena(Subsequencia &sg_1, Subsequencia &sg_2, Data *data);

void attMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, Data *data);

void attMatrizSubSeqInv(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, Data *data);

#endif