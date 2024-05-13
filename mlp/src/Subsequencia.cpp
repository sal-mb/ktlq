#include "Subsequencia.h"
#include "Data.h"
#include "Solucao.h"
#include <iostream>


void exibir_subSeq(Subsequencia &subseq, Solucao &s){
    
    if(subseq.W  <= 1 ){
        std::cout << "Subsequencia: " << s.sequencia[subseq.primeiro] << std::endl;
        std::cout << "W: " << subseq.W <<", T: " << subseq.T << ", C: " << subseq.C  << "\n" << std::endl;
        return;
    }

    if(subseq.primeiro < subseq.ultimo){
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro; i < subseq.ultimo; i++){
            std::cout<< s.sequencia[i] << " -> ";
        }
    }else{
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro; i > subseq.ultimo; i--){
            std::cout<< s.sequencia[i] << " -> ";
        }
    }
    std::cout<< s.sequencia[subseq.ultimo] << std::endl;
    std::cout << "W: " << subseq.W <<", T: " << subseq.T << ", C: " << subseq.C  << "\n" << std::endl;

}
void exibir_matrizSubSeq(std::vector<std::vector<Subsequencia>> &subSeqMatrix, Solucao &s){

    int n = s.sequencia.size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("[%d] [%d]", i, j);
            exibir_subSeq(subSeqMatrix[i][j], s);
        }
    }
}

void attMatrizSubSeq(Solucao &s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, int pos, Data *data){

    int n = s.sequencia.size();

    for(int i = pos; i < n; i++){
        subSeqMatrix[i][i].W = 1;
        subSeqMatrix[i][i].C = 0;
        subSeqMatrix[i][i].T = 0;
        subSeqMatrix[i][i].primeiro = s.sequencia[i];
        subSeqMatrix[i][i].ultimo = s.sequencia[i];
    }

    for(int i = 0; i < n; i++){
        int j;

        if(i >= pos){ //valores antes da posicao minima nao sao alterados
            j = i+1;
        }else{
            j = pos; //por isso se i < pos, basta alterar de pos para frente
        }

        while(j < n){

            subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j-1], subSeqMatrix[j][j], data);       

            j++; 
        }
    }

    for (int i = n - 1; i >= pos; i--){//basta ir ate a pos minima de tras pra frente, pois a partir dela nd foi alterado
        for(int j = i - 1; j >= 0; j--){

            subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j+1], subSeqMatrix[j][j], data);
        }
    }

    s.custoA = subSeqMatrix[0][n-1].C;
}