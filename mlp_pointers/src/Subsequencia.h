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

static inline Subsequencia Concatena(Subsequencia &sg_1, Subsequencia &sg_2, Data *data){
    Subsequencia sg;

    sg.W = sg_1.W + sg_2.W;
    sg.T = sg_1.T + data->getDistance(sg_1.ultimo, sg_2.primeiro) + sg_2.T;
    sg.C = sg_1.C + sg_2.W * (sg_1.T + data->getDistance(sg_1.ultimo, sg_2.primeiro)) + sg_2.C;

    
    sg.primeiro = sg_1.primeiro;
    sg.ultimo = sg_2.ultimo;

    return sg;
}

void attMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, int pos, Data *data);

#endif