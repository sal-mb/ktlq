#include "Construcao.h"
#include "Data.h"
#include "Solucao.h"
#include "Subsequencia.h"
#include <algorithm>
#include <cstdlib>

bool ordena_por_custo(Insercao a, Insercao b){ return a.custo < b.custo; }

Solucao construcao(Solucao &s, Data *dados){
    Solucao s_;
    Solucao cl = s;

    s_.sequencia.push_back(1);

    cl.sequencia.pop_back();
    cl.sequencia.erase(cl.sequencia.begin());

    int r = 1;
    while(!cl.sequencia.empty()){

        std::vector<Insercao> custos_cl_r = calcula_custo_em_relacao_a_r(cl, r, dados);

        std::sort(custos_cl_r.begin(), custos_cl_r.end(), ordena_por_custo);

        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custos_cl_r.size()));

        s_.sequencia.push_back(cl.sequencia[selecionado]);
        
        r = cl.sequencia[selecionado];

        cl.sequencia.erase(cl.sequencia.begin()+selecionado);
    }

    s_.sequencia.push_back(1);

    return s_;
}

std::vector<Insercao> calcula_custo_em_relacao_a_r(Solucao &cl, int r, Data *dados){

    std::vector<Insercao> custos_cl_r;
    int n = cl.sequencia.size();

    for(int i = 0; i < n; i++){
        Insercao no_atual;

        no_atual.no = cl.sequencia[i];
        no_atual.custo = dados->getDistance(r, no_atual.no);

        custos_cl_r.push_back(no_atual);
    }

    return custos_cl_r;
}