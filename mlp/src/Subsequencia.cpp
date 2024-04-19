#include "Subsequencia.h"
#include "Data.h"
#include "Solucao.h"
#include <iostream>


void exibir_subSeq(Subsequencia &subseq, Solucao *s){
    
    if(subseq.W  <= 1 ){
        std::cout << "Subsequencia: " << s->sequencia[subseq.primeiro_pos] << std::endl;
        std::cout << "W: " << subseq.W <<", T: " << subseq.T << ", C: " << subseq.C  << "\n" << std::endl;
        return;
    }

    if(subseq.primeiro_pos < subseq.ultimo_pos){
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro_pos; i < subseq.ultimo_pos; i++){
            std::cout<< s->sequencia[i] << " -> ";
        }
    }else{
        std::cout<< "Subsequencia: ";
        for(int i = subseq.primeiro_pos; i > subseq.ultimo_pos; i--){
            std::cout<< s->sequencia[i] << " -> ";
        }
    }
    std::cout<< s->sequencia[subseq.ultimo_pos] << std::endl;
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
    sg.T = sg_1.T + data->getDistance(s->sequencia[sg_1.ultimo_pos], s->sequencia[sg_2.primeiro_pos]) + sg_2.T;
    sg.C = sg_1.C + sg_2.W * (sg_1.T + data->getDistance(s->sequencia[sg_1.ultimo_pos], s->sequencia[sg_2.primeiro_pos])) + sg_2.C;

    
    sg.primeiro_pos = sg_1.primeiro_pos;
    sg.ultimo_pos = sg_2.ultimo_pos;

    return sg;
}

void attMatrizSubSeq(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix, Data *data){

    int n = s->sequencia.size();

    for(int i = 0; i < n; i++){
        subSeqMatrix[i][i].W = 1;
        subSeqMatrix[i][i].C = 0;
        subSeqMatrix[i][i].T = 0;
        subSeqMatrix[i][i].primeiro_pos = i;
        subSeqMatrix[i][i].ultimo_pos = i;
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
    // subSeqMatrix[0][0].W = 0;
    // subSeqMatrix[n-1][n-1].W = 0;
}

// void attMatrizSubSeqInv(Solucao *s, std::vector<std::vector<Subsequencia>> &subSeqMatrix,Data *data){
    
//     int n = s->sequencia.size();

//      for(int i = 0; i < n; i++){
//         subSeqMatrix[i][i].W = 1;
//         subSeqMatrix[i][i].C = 0;
//         subSeqMatrix[i][i].T = 0;
//         subSeqMatrix[i][i].primeiro_pos = (n-1)-i;
//         subSeqMatrix[i][i].ultimo_pos = (n-1)-i;
//     }

//     // for(int i = n-1; i >=0; i--){
//     //     for(int j = i-1; j > 0; j--){
//     //         subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j+1], subSeqMatrix[j][j], data, s);        
//     //     }
//     // }
//     for(int i = 0; i < n-1; i++){
//         for(int j = i+1; j < n; j++){
//             subSeqMatrix[i][j] = Concatena(subSeqMatrix[i][j-1], subSeqMatrix[j][j], data, s);        
//         }
//     }
//     subSeqMatrix[0][0].W = 0;
//     subSeqMatrix[n-1][n-1].W = 0;
// }