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
#include "Construcao.h"

#define EPSILON 1

using namespace std;

Solucao ILS( Solucao &s, Data *data, int maxIter, int maxIterIls, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

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
    attMatrizSubSeq(s, subSeqMatrix, 0, &data);

    // exibir_solucao(s, &data);
    // Solucao s_ = perturbacao(s, &data);
    // exibir_solucao(s_, &data);
    double sumCost = 0;

    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i < 10; i++){

        Solucao s_parcial = ILS(s, &data, 10, n < 100 ? n : 100, subSeqMatrix);
        sumCost += s_parcial.custoA;

    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << data.getInstanceName();
    printf(" - %.3lf %.1lf\n", (double)(duration.count())/1000, sumCost/10);

}


Solucao ILS(Solucao &s, Data *data, int maxIter, int maxIterIls, std::vector<std::vector<Subsequencia>> &subSeqMatrix){

    Solucao melhor;
    melhor.custoA = INFINITY;
    
    for(int i = 0; i <= maxIter; i++){
        int iterILS = 0;

        Solucao s_ = construcao(s, data);
        attMatrizSubSeq(s_, subSeqMatrix, 0, data);

        Solucao melhorAtual = s_;

        while(iterILS <= maxIterIls){
            BuscaLocal(s_, data, subSeqMatrix);

            if(s_.custoA + EPSILON < melhorAtual.custoA){
                melhorAtual = s_;
                iterILS = 0;

            }

            iterILS++;

            s_ = perturbacao(melhorAtual, data);
            attMatrizSubSeq(s_, subSeqMatrix, 0, data);
        }

        if(melhorAtual.custoA + EPSILON < melhor.custoA){
            melhor = melhorAtual;
        }
    }

    return melhor;
}