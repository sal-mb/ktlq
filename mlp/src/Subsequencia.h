#ifndef SUBSEQUENCIA_H
#define SUBSEQUENCIA_H

#include "Solucao.h"
#include <vector>

typedef struct Subsequencia{
    double T, C;
    int W;
    int primeiro, ultimo;
}Subsequencia;

void exibir_subSeq(Subsequencia &subseq, Solucao *s);

void exibir_matrizSubSeq(std::vector<std::vector<Subsequencia>> &subSeqMatrix, Solucao *s);

Subsequencia Concatena(Subsequencia &sg_1, Subsequencia &sg_2, Data *data, Solucao *s);

void attMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, int pos, Data *data);

void upMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, int pos, Data *data);
#endif