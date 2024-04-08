#include "Construcao.h"
#include "Solucao.h"
#include <algorithm>

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

    calcula_custoS(s_, dados);
    return s_;
}

void inserir_em_s(Solucao *s,  Solucao *resto, Insercao no){

    s->sequencia.insert(std::find(s->sequencia.begin()+1, s->sequencia.end(), no.a_Removida.y), no.k_Inserido);

    resto->sequencia.erase(std::find(resto->sequencia.begin(), resto->sequencia.end(), no.k_Inserido));

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