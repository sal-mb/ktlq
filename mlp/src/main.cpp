#include "Data.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "Solucao.h"
#include "BuscaLocal.h"
#include <time.h>
#include <chrono>
#include "Subsequencia.h"

#define EPSILON 0.0005

using namespace std;

Solucao* ILS( Solucao* s, Data *data, int maxIter, int maxIterIls);

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    // time_t t;
    // srand(time(&t) + n);
    // double sumCost = 0;

    Solucao s;
    for(int i = 1; i <= 9; i++){
        s.sequencia.push_back(i);
    }
    s.sequencia.push_back(1);

    vector<vector<Subsequencia>> matrizSubSeq(10, vector<Subsequencia> (10));
    vector<vector<Subsequencia>> matrizSubSeqInv(10, vector<Subsequencia> (10));

    attMatrizSubSeq(&s, matrizSubSeq, &data);
    attMatrizSubSeqInv(&s, matrizSubSeqInv, &data);

    exibir_matrizSubSeq(matrizSubSeq, &s);
    exibir_matrizSubSeq(matrizSubSeqInv, &s);
    // auto start = chrono::high_resolution_clock::now();
    
    // auto stop = chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    // std::cout << data.getInstanceName();
    // printf(" - %.3lf %.1lf\n", (double)(duration.count())/10000, sumCost/10);

    return 0;
}


Solucao* ILS(Solucao* s, Data *data, int maxIter, int maxIterIls){

    Solucao *melhor = new Solucao;
    melhor->custoS = INFINITY;
    
    for(int i = 0; i <= maxIter; i++){

        Solucao *s_ = construcao(s, data);
        Solucao *melhorAtual = new Solucao;
        *melhorAtual = *s_;
        int iterILS = 0;

        while(iterILS <= maxIterIls){
            BuscaLocal(s_, data);
            if(s_->custoS + EPSILON < melhorAtual->custoS){
                //delete melhorAtual;
                *melhorAtual = *s_;
                //std::cout << "apos busca local: " << melhorAtual->custoS << std::endl;
                iterILS = 0;
            }
            iterILS++;
            delete s_;
            s_ = perturbacao(melhorAtual, data);
        }

        if(melhorAtual->custoS + EPSILON < melhor->custoS){
            *melhor = *melhorAtual;
        }
        delete s_;
        delete melhorAtual;
    }

    return melhor;
}