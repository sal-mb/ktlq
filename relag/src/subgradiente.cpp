#include <utility>
#include <vector>
#include "Kruskal.h"
#include "subgradiente.h"


inline void melhor_no(Node &best, double w, vector<double> lmb, vii edges, pair<int,int> best_nodes){

    best.arestas = edges;
    best.arestas.push_back(make_pair(0, best_nodes.first));
    best.arestas.push_back(make_pair(0, best_nodes.second));

    best.penalizadores = lmb;

    best.cost = w;
}

vector<int> calcula_graus_mst(vii mst, pair<int,int> melhores_nos){

    vector<int> graus(mst.size()+2, 0); //inicia os graus dos vertices com 0

    for(int i = 0; i < mst.size(); i++){
        graus[mst[i].second]++;
        graus[mst[i].first]++;
    }

    
    graus[melhores_nos.first]++;
    graus[melhores_nos.second]++;

    graus[0] += 2;

    return graus;
}

double tamanho_do_passo(double upper_bound, double w, vector<int> graus){
    int acumulador = 0;

    for(int i = 0; i < graus.size(); i++){
        acumulador += ((2 - graus[i]) * (2 - graus[i])); 
    }

    if(acumulador == 0){
        //criteiro de parada Ax = b

        return 0;
    }

    return (upper_bound - w) / acumulador;
}

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus){

    
    lmb[0] = 0;

    for(int i = 1; i < lmb.size(); i++){
        //atualizando os penalizadores
        lmb[i] = lmb[i] + (u * (2 - graus[i]));

        //---------------------------------------------
    }

}

vvi altera_custos(vvi custos, vector<double> lmb){

    vvi custos_penalizados;

    for(int i = 0; i < lmb.size(); i++){
        vector<double> linha;

        for(int j = 0; j < lmb.size(); j++){
            
            //aplicando os penalizadores nos custos da matriz
            linha.push_back(custos[i][j] - lmb[i] - lmb[j]);

            //---------------------------------------------------
        }

        custos_penalizados.push_back(linha);
    }

    return custos_penalizados;
}

pair<int,int> melhores_nos_0(vvi custos, double w, int n, vii edges){
    //retorna os 2 nos mais proximos do no 0

    double custo_no_1 = custos[0][0];
    double custo_no_2 = custos[0][0];

    int best_node_1 = 0;
    int best_node_2 = 0;

    for(int i = 1; i < n; i++){
        if(custos[0][i] < custo_no_1){
            custo_no_1 = custos[0][i];
            best_node_1 = i;
        }
    }

    for(int i = 1; i < n; i++){
        if(custos[0][i] < custo_no_2 && i != best_node_1){
            custo_no_2 = custos[0][i];
            best_node_2 = i;
        }
    }

    return make_pair(best_node_1, best_node_2);
}

Node subgradiente(double ub, int n, vvi cost_matrix, vector<double> lmb){
    // n = tamanho da instancia

    //comecando o custo do melhor no com 0

    Node best_node;
    best_node.cost = 0;
    
    int k = 0; //iterador
    double e = 1; //fator de passo
    double u = 0; //tamanho do passo

    vvi custos_penalizados = altera_custos(cost_matrix, lmb);

    //-----------------------------------------------------------------------

    //0.005 -  fator de passo minimo

    while(e >= 0.005){
        
        Kruskal x_(custos_penalizados);   

        double mst_cost = x_.MST(n);

        pair<int,int> melhores_nos = melhores_nos_0(custos_penalizados, mst_cost, n, x_.getEdges());

        vector<int> graus = calcula_graus_mst(x_.getEdges(), melhores_nos);

        double w = mst_cost + custos_penalizados[0][melhores_nos.first] + custos_penalizados[0][melhores_nos.second];
        
        if(w > best_node.cost){
            k = 0;

            melhor_no(best_node, w, lmb, x_.getEdges(), melhores_nos);

        }else{
            k++;

            if(k >= 30){
                k = 0;
                e /= 2;
            }
        }

        u = e * tamanho_do_passo(ub, w, graus);

        if(u < 0.00001){

            melhor_no(best_node, w, lmb, x_.getEdges(), melhores_nos);
            best_node.feasible = true;
            break;
        
        }else if(ub - best_node.cost < 0.9999){
            best_node.cost = 999999999;
            break;

        }

        altera_penalizadores(lmb, u, graus);

        custos_penalizados = altera_custos(cost_matrix, lmb);
    }

    
    return best_node;
}
