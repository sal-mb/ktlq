#include "Solucao.h"
#include "Data.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

void exibir_solucao(Solucao *s){

    std::cout << "Solução: " << std::endl;
    for(int i = 0; i < s->sequencia.size() - 1; i++){
        std::cout << s->sequencia[i] << " -> ";
    }
    std::cout << s->sequencia.back() << std::endl;

    if(s->custoS != 0){
        std::cout << "CustoS: " << s->custoS << std::endl;
    }
}

void calcula_custoS(Solucao *s, Data *dados){
    s->custoS = 0;
    
    for(int i = 0; i < s->sequencia.size() - 1; i++){
        s->custoS += dados->getDistance(s->sequencia[i], s->sequencia[i+1]);
    }

}


Solucao* gera_S_aletaoria(Solucao *s){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    Solucao *s1 = new Solucao;
    s1->sequencia = {1};


    while(s1->sequencia.size() < 4){

        int position = (generator() % (s->sequencia.size()-2)) + 1;
        int number = s->sequencia.at(position);

        if((std::find(s1->sequencia.begin(), s1->sequencia.end(), number)) == s1->sequencia.end()){
            s1->sequencia.push_back(number);
        }
        
    }

    s1->sequencia.push_back(1);

    return s1;
}


Solucao* nosRestantes(Solucao *s, Solucao *gerada){
    
    Solucao *resto = new Solucao;

    for(int i = 1; i < s->sequencia.size() - 1; i++){

       if((std::find(gerada->sequencia.begin(), gerada->sequencia.end(), s->sequencia[i])) == gerada->sequencia.end()){
            resto->sequencia.push_back(s->sequencia[i]);
       }
    }

    return resto;
}
