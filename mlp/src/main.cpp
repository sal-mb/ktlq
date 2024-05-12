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

Solucao* ILS( Solucao* s, Data *data, int maxIter, int maxIterIls, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    time_t t;
    srand(time(&t) + n);

    Solucao s;
    for(int i = 1; i <= n; i++){
        s.sequencia.push_back(i);
    }
    s.sequencia.push_back(1);

    vector<vector<Subsequencia>> subSeqMatrix(n+1, vector<Subsequencia> (n+1));

    double sumCost = 0;

    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i < 10; i++){

        Solucao *s_ = ILS(&s, &data, 10, n < 100 ? n : 100, subSeqMatrix);
        sumCost += s_->custoA;

        exibir_solucao(s_, &data);
        delete s_;

    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << data.getInstanceName();
    printf(" - %.3lf %.1lf\n", (double)(duration.count())/10000, sumCost/10);

    return 0;
}


Solucao* ILS(Solucao* s, Data *data, int maxIter, int maxIterIls, std::vector<std::vector<Subsequencia>> &subSeqMatrix){

    Solucao *melhor = new Solucao;
    melhor->custoA = INFINITY;
    
    for(int i = 0; i <= maxIter; i++){

        Solucao *s_ = construcao(s, data);
        Solucao *melhorAtual = new Solucao;
        *melhorAtual = *s_;
        int iterILS = 0;

        attMatrizSubSeq(s_, subSeqMatrix, data);

        while(iterILS <= maxIterIls){
            BuscaLocal(s_, data, subSeqMatrix);

            if(s_->custoA + EPSILON < melhorAtual->custoA){
                //delete melhorAtual;
                *melhorAtual = *s_;
                //std::cout << "apos busca local: " << melhorAtual->custoS << std::endl;
                iterILS = 0;
            }

            iterILS++;
            delete s_;

            s_ = perturbacao(melhorAtual, data);
            attMatrizSubSeq(s_, subSeqMatrix, data);
        }

        if(melhorAtual->custoA + EPSILON < melhor->custoA){
            *melhor = *melhorAtual;
        }
        delete s_;
        delete melhorAtual;
    }

    return melhor;
}