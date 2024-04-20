#include "Construcao.h"
#include "Solucao.h"
#include <algorithm>

bool ordena_por_custo(Insercao a, Insercao b){ return a.custoI < b.custoI; }

void exibir_custo_de_insercao(std::vector<Insercao> *custosInsercao, Solucao *s){
    for(auto insercao : *(custosInsercao)){
        std::cout << "no inserido: " << insercao.k_Inserido << " ; aresta removida_pos: {" << s->sequencia[insercao.removida_pos-1] << ", " << s->sequencia[insercao.removida_pos]  << "} ; custo: " << insercao.custoI << std::endl;
    }
    printf("\n");
}

Solucao* construcao(Solucao *s, Data *dados){

    Solucao *s_ = gera_S_aletaoria(s);
    Solucao *resto = nosRestantes(s, s_);

    while(!resto->sequencia.empty()){
        std::vector<Insercao> custosInsercao = calcula_custo_insercao(s_, resto, dados);
        std::sort(custosInsercao.begin(), custosInsercao.end(), ordena_por_custo);

        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custosInsercao.size()));

        inserir_em_s(s_, resto, custosInsercao[selecionado]);
    }
    
    calcula_custoA(s_, dados);
    delete resto;
    return s_;
}

void inserir_em_s(Solucao *s,  Solucao *resto, Insercao no){

    s->sequencia.insert(s->sequencia.begin()+no.removida_pos, no.k_Inserido);

    resto->sequencia.erase(resto->sequencia.begin()+no.inserido_pos);

}

std::vector<Insercao> calcula_custo_insercao(Solucao *s, Solucao *resto, Data *dados){
    
    std::vector<Insercao> custosInsercao((s->sequencia.size()-1) * resto->sequencia.size());

    int l = 0;

    for(int i = 1; i < s->sequencia.size(); i++){
        
        int a_prev = s->sequencia[i-1];
        int a = s->sequencia[i];

        for(int j = 0; j < resto->sequencia.size(); j++){

            int k = resto->sequencia[j];
            custosInsercao[l].custoI = dados->getDistance(a_prev, k) + dados->getDistance(k, a) - dados->getDistance(a_prev, a);
            custosInsercao[l].k_Inserido = k;
            custosInsercao[l].inserido_pos = j;
            custosInsercao[l].removida_pos = i;
            l++;
        }
    }

    return custosInsercao;
}