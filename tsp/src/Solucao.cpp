#include "Solucao.h"
#include "Data.h"
#include <algorithm>
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

    Solucao *s1 = new Solucao;
    s1->sequencia = {1};


    while(s1->sequencia.size() < 4){

        int position = (rand() % (s->sequencia.size()-2)) + 1;
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

Solucao* perturbacao(Solucao *s, Data *data){

    Solucao *perturbada = new Solucao;
    *perturbada = *s;

    std::vector<int> bloco1, bloco2;
    int size_b1, size_b2;

    size_b1 = rand() % (perturbada->sequencia.size()/10) + 2;
    size_b2 = rand() % (perturbada->sequencia.size()/10) + 2;

    bloco1.reserve(size_b1);
    bloco2.reserve(size_b2);


    int posicao_b1, posicao_b2;

    posicao_b1 = (rand() % (perturbada->sequencia.size() - (size_b1+1))) + 1;

    posicao_b2 = (rand() % (perturbada->sequencia.size() - (size_b2+1))) + 1;

    while(posicao_b2 < posicao_b1+size_b1 && posicao_b1 < posicao_b2+size_b2){
        posicao_b2 = (rand() % (perturbada->sequencia.size() - (size_b2+1))) + 1;
    }

    // std::cout << "[b1] posicao: " << posicao_b1 << ", tamanho: " << size_b1 << std::endl; 
    // std::cout << "[b2] posicao: " << posicao_b2 << ", tamanho: " << size_b2 << std::endl; 
    

    for(int i = 0; i < size_b1; i++){
        bloco1.push_back(perturbada->sequencia[posicao_b1+i]);
    }
    for(int i = 0; i < size_b2; i++){
        bloco2.push_back(perturbada->sequencia[posicao_b2+i]);
    }
    

    if(posicao_b1 > posicao_b2){

        perturbada->sequencia.erase(perturbada->sequencia.begin()+posicao_b1, perturbada->sequencia.begin()+posicao_b1+size_b1);
        perturbada->sequencia.insert(perturbada->sequencia.begin()+posicao_b1, bloco2.begin(), bloco2.end());
        perturbada->sequencia.erase(perturbada->sequencia.begin()+posicao_b2, perturbada->sequencia.begin()+posicao_b2+size_b2);
        perturbada->sequencia.insert(perturbada->sequencia.begin()+posicao_b2, bloco1.begin(), bloco1.end());
    }else{

        perturbada->sequencia.erase(perturbada->sequencia.begin()+posicao_b2, perturbada->sequencia.begin()+posicao_b2+size_b2);
        perturbada->sequencia.insert(perturbada->sequencia.begin()+posicao_b2, bloco1.begin(), bloco1.end());
        perturbada->sequencia.erase(perturbada->sequencia.begin()+posicao_b1, perturbada->sequencia.begin()+posicao_b1+size_b1);
        perturbada->sequencia.insert(perturbada->sequencia.begin()+posicao_b1, bloco2.begin(), bloco2.end());
    }
    
    calcula_custoS(perturbada, data);
    return perturbada;

}
