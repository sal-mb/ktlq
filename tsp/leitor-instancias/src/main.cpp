#include "Data.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include "Solucao.h"
#include "BuscaLocal.h"

using namespace std;
Solucao* S_;
Solucao* ILS( Solucao* s, Data *data, int maxIter, int maxIterIls);

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    cout << "Dimension: " << n << endl;

    Solucao s, s2;

    for(int i = 1; i <= n; i++){
        s.sequencia.push_back(i);
    }
    s.sequencia.push_back(1);

    
    Solucao *s_ = ILS(&s, &data, 50, n > 150 ? n/2 : n);

    exibir_solucao(s_);
    delete s_;

    return 0;
}


Solucao* ILS(Solucao* s, Data *data, int maxIter, int maxIterIls){

    Solucao *melhor = new Solucao;
    melhor->custoS = INFINITY;
    for(int i = 0; i < maxIter; i++){

        Solucao *s_ = construcao(s, data);
        Solucao *melhorAtual = construcao(s, data);
        int iterILS = 0;

        while(iterILS <= maxIterIls){
            BuscaLocal(s_, data);
            if(s_->custoS < melhorAtual->custoS){
                //delete melhorAtual;
                *melhorAtual = *s_;
                //std::cout << "apos busca local: " << melhorAtual->custoS << std::endl;
                iterILS = 0;
            }
            iterILS++;
            delete s_;
            s_ = perturbacao(melhorAtual, data);
        }

        if(s_->custoS < melhor->custoS){
            *melhor = *melhorAtual;
        }
        delete s_;
        delete melhorAtual;
    }

    return melhor;
}