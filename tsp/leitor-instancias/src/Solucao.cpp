#include "Solucao.h"
#include "Data.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
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

void exibir_custo_de_insercao(std::vector<Insercao> *custosInsercao){
    for(auto insercao : *(custosInsercao)){
        std::cout << "no inserido: " << insercao.k_Inserido << " ; aresta removida: {" << insercao.a_Removida.x << ", " << insercao.a_Removida.y << "} ; custo: " << insercao.custoI << std::endl;
    }
    printf("\n");
}

void ordena_custos(std::vector<Insercao> *custosInsercao){

  int i, j;
  int swapped;

  for(i = 0; i < custosInsercao->size()-1; i++){
    swapped = 0;

    for(j = 0; j < custosInsercao->size() - i -1;j++){

      if(custosInsercao->at(j).custoI > custosInsercao->at(j+1).custoI){
        Insercao aux = custosInsercao->at(j);
        custosInsercao->at(j) = custosInsercao->at(j+1);
        custosInsercao->at(j+1) = aux;
        swapped = 1;
      }

    }

    if(!(swapped)){
      break;
    }
  }
}

void calcula_custoS(Solucao *s, Data *dados){

    for(int i = 0; i < s->sequencia.size() - 1; i++){
        s->custoS += dados->getDistance(s->sequencia[i], s->sequencia[i+1]);
    }

}

Solucao* construcao(Solucao *s, Data *dados){

    Solucao *s_ = gera_S_aletaoria(s);
    Solucao *resto = nosRestantes(s, s_);

    while(!resto->sequencia.empty()){
        std::vector<Insercao> custosInsercoes = calcula_custo_insercao(s_, resto, dados);

        ordena_custos(&custosInsercoes);

        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custosInsercoes.size()));

        inserir_em_s(s_, resto, custosInsercoes[selecionado]);
    }

    return s_;
}

void inserir_em_s(Solucao *s,  Solucao *resto, Insercao no){


    resto->sequencia.erase(std::find(resto->sequencia.begin(), resto->sequencia.end(), no.k_Inserido));

    s->sequencia.insert(std::find(s->sequencia.begin(), s->sequencia.end(), no.a_Removida.y), no.k_Inserido);
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

std::vector<Insercao> calcula_custo_insercao(Solucao *s, Solucao *resto, Data *dados){
    std::vector<Insercao> custosInsercao((s->sequencia.size() - 1) * resto->sequencia.size());

    int l = 0;

    for(int i = 0; i < s->sequencia.size()-1; i++){
        Aresta a = {s->sequencia[i], s->sequencia[i+1]};

        for(auto k : resto->sequencia){

            custosInsercao[l].custoI = dados->getDistance(a.x, k) + dados->getDistance(k, a.y) - dados->getDistance(a.x, a.y);
            custosInsercao[l].k_Inserido = k;
            custosInsercao[l].a_Removida = a;
            l++;
        }
    }

    return custosInsercao;
}