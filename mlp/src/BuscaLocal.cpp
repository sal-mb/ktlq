#include "BuscaLocal.h"
#include "Solucao.h"
#include <algorithm>
#include <utility>
#include "Subsequencia.h"

#define EPSILON 0.0005

void BuscaLocal(Solucao *s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix){

    std::vector<int> metodos = {0, 1, 2, 3, 4};
    bool melhorou = false;

    while(!metodos.empty()){
        
        int BI = rand() % metodos.size();

        switch (metodos[BI]) {
            
            case 0:
                melhorou = BISwap(s, data, subSeqMatrix);
                break;

            case 1:
                melhorou = BI2_Opt(s, data, subSeqMatrix);
                break;

            default:
                melhorou = BIOrOpt(s, data, metodos[BI]-1, subSeqMatrix);
        }

        if(melhorou){
            metodos = {0, 1, 2, 3, 4};
        }else{
            metodos.erase(metodos.begin() + BI);
        }
    }
}


bool BISwap(Solucao *s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;
    int n = s->sequencia.size();
    Subsequencia result;

    for(int i = 1; i < n-1; i++){
        
        Subsequencia subseq_i = subSeqMatrix[i][i];
        Subsequencia prev_i = subSeqMatrix[0][i-1];

        for(int j = i+1; j < n-1; j++){
            
            // std::cout << "busca local 1" << std::endl;

            Subsequencia prev_j = subSeqMatrix[i+1][j-1];
            Subsequencia subseq_j = subSeqMatrix[j][j];
            Subsequencia next_j = subSeqMatrix[j+1][n-1];

            if(j == i+1){
                
                result = Concatena(prev_i, subseq_j, data, s);
                result = Concatena(result, subseq_i, data, s);
                result = Concatena(result, next_j, data, s);

            }else{

                result = Concatena(prev_i, subseq_j, data, s);
                result = Concatena(result, prev_j, data, s);
                result = Concatena(result, subseq_i, data, s);
                result = Concatena(result, next_j, data, s);

            }

            double delta = result.C - s->custoA;

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    
    if(bestDelta + EPSILON < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        s->custoA += bestDelta;

        // std::cout << s->custoA;
        // calcula_custoA(s, data);
        // std::cout << " = " << s->custoA << std::endl;

        attMatrizSubSeq(s, subSeqMatrix, best_i, data);

        return true;

    }
    
    return false;
}

bool BI2_Opt(Solucao *s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix){
    double bestDelta = 0;
    int best_i =0, best_j =0;
    int n = s->sequencia.size();
    Subsequencia result;
    
    for(int i = 0; i < n-1 ;i++){
        
        Subsequencia subseq_i = subSeqMatrix[0][i];

        for(int j = i+2; j < n-1; j++){
            
            // std::cout << "busca local 2" << std::endl;

            Subsequencia inv = subSeqMatrix[j][i+1];
            Subsequencia next_j = subSeqMatrix[j+1][n-1];
            
            result = Concatena(subseq_i, inv, data, s);
            result = Concatena(result, next_j, data, s);

            double delta = result.C - s->custoA;

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i+1;
                best_j = j+1;
            }
        }
    }

    if(bestDelta + EPSILON < 0){
           
        std::reverse(s->sequencia.begin()+(best_i), s->sequencia.begin()+(best_j));
        s->custoA += bestDelta;

        // std::cout << s->custoA;
        // calcula_custoA(s, data);
        // std::cout << " = " << s->custoA << std::endl;

        attMatrizSubSeq(s, subSeqMatrix, best_i, data);

        return true;

    }

    return false;

}

bool BIOrOpt(Solucao *s, Data *data, int option, std::vector<std::vector<Subsequencia>> &subSeqMatrix){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;
    int n = s->sequencia.size();
    Subsequencia result;
    

        for(int i = 1; i < n-option; i++){
            Subsequencia prev_i = subSeqMatrix[0][i-1];
            Subsequencia subseq_i= subSeqMatrix[i][i+option-1];
            Subsequencia next_i = subSeqMatrix[i+option][n-1];

            for(int j = 1; j < n; j++){

                if((j+option-1) >= i && i >= (j-option)){ continue; }

                //std::cout << "busca local 3, i: " << i << " j: " << j << ", option: " <<<< std::endl;
                if(i < j){
                    
                    Subsequencia i_to_j = subSeqMatrix[i+option][j-1];
                    Subsequencia next_j = subSeqMatrix[j][n-1];

                    result = Concatena(prev_i, i_to_j, data, s);
                    result = Concatena(result, subseq_i, data, s);
                    result = Concatena(result, next_j, data, s);

                }else{

                    Subsequencia prev_j = subSeqMatrix[0][j-1];
                    Subsequencia j_to_i = subSeqMatrix[j][i-1];

                    result = Concatena(prev_j, subseq_i, data, s);
                    result = Concatena(result, j_to_i, data, s);
                    result = Concatena(result, next_i, data, s); 
                }

                double delta = result.C - s->custoA;

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }

            }
        }
        

        if(bestDelta + EPSILON < 0){
            // std::cout << "i: " << best_i << " j: " << best_j << std::endl;
            // std::cout << "element i: " << s->sequencia[best_i] << " element j: " << s->sequencia[best_j] << std::endl;

            Solucao s_ = *s;

            s->sequencia.insert(s->sequencia.begin()+best_j, s_.sequencia.begin()+best_i, s_.sequencia.begin()+best_i+option);

            if(best_j > best_i){
                s->sequencia.erase(s->sequencia.begin()+best_i, s->sequencia.begin()+best_i+option);
                attMatrizSubSeq(s, subSeqMatrix, best_i, data);

            }else{
                s->sequencia.erase(s->sequencia.begin()+best_i+option, s->sequencia.begin()+best_i+option+option);
                attMatrizSubSeq(s, subSeqMatrix, best_j, data);

            }

            s->custoA += bestDelta;

            // std::cout << s->custoA;
            // calcula_custoA(s, data);
            // std::cout << " = " << s->custoA << std::endl;

            // attMatrizSubSeq(s, subSeqMatrix, data);

            return true;

        }
        
    
    return false;
}