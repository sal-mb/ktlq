#include "Subsequencia.h"
#include "Data.h"
#include "Solucao.h"
#include <iostream>


void exibir_subSeq(Subsequencia &subseq, Solucao *s){
    
    if(subseq.W  <= 1 ){
        std::cout << "Subsequencia: " << s->sequencia[subseq.primeiro] << std::endl;
        std::cout << "W: " << subseq.W <<", T: " << subseq.T << ", C: " << subseq.C  << "\n" << std::endl;
        return;
    }

    if(subseq.primeiro < subseq.ultimo){
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro; i < subseq.ultimo; i++){
            std::cout<< s->sequencia[i] << " -> ";
        }
    }else{
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro; i > subseq.ultimo; i--){
            std::cout<< s->sequencia[i] << " -> ";
        }
    }
    std::cout<< s->sequencia[subseq.ultimo] << std::endl;
    std::cout << "W: " << subseq.W <<", T: " << subseq.T << ", C: " << subseq.C  << "\n" << std::endl;

}
void exibir_matrizSubSeq(std::vector<std::vector<Subsequencia>> &subSeqMatrix, Solucao *s){

    int n = s->sequencia.size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("[%d] [%d]", i, j);
            exibir_subSeq(subSeqMatrix[i][j], s);
        }
    }
}

Subsequencia Concatena(Subsequencia &sg_1, Subsequencia &sg_2, Data *data, Solucao *s){
    Subsequencia sg;

    sg.W = sg_1.W + sg_2.W;
    sg.T = sg_1.T + data->getDistance(sg_1.ultimo, sg_2.primeiro) + sg_2.T;
    sg.C = sg_1.C + sg_2.W * (sg_1.T + data->getDistance(sg_1.ultimo, sg_2.primeiro)) + sg_2.C;

    
    sg.primeiro = sg_1.primeiro;
    sg.ultimo = sg_2.ultimo;

    return sg;
}

void attMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, int pos, Data *data){

    int n = s->sequencia.size();

    for(int i = 0; i < n; i++){
        subSeqMatrix[i][i].W = 1;
        subSeqMatrix[i][i].C = 0;
        subSeqMatrix[i][i].T = 0;
        subSeqMatrix[i][i].primeiro = s->sequencia[i];
        subSeqMatrix[i][i].ultimo = s->sequencia[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){

            subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j-1], subSeqMatrix[j][j], data, s);        
        }
    }

    for (int i = n - 1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){

            subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j+1], subSeqMatrix[j][j], data, s);
        }
    }

    double custoac = subSeqMatrix[0][n-1].C;
}