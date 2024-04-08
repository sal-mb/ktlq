#include "Data.h"
#include <iostream>
#include <vector>
#include "Solucao.h"
#include "Construcao.h"
#include "BuscaLocal.h"

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    cout << "Dimension: " << n << endl;
    //cout << "DistanceMatrix: " << endl;
    //data.printMatrixDist();

    Solucao s, s2;

    // cout << "Exemplo de Solucao s = ";
    // for (size_t i = 1; i <= n; i++) {
    //     s.sequencia.push_back(i);
    // }
    // s.sequencia.push_back(1);
    // calcula_custoS(&s, &data);

    for(int i = 1; i <= 30; i++){
        s.sequencia.push_back(i);
    }
    s.sequencia.push_back(1);


    Solucao *s_ = construcao(&s, &data);

    exibir_solucao(s_);

    if(BIOrOpt(s_, &data, 3)){
        exibir_solucao(s_);
    }
    return 0;
}
