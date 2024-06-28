#include <utility>
#include <vector>
#include "Kruskal.h"
#include "data.h"
#include "subgradiente.h"
#include "unistd.h"
#include "prints.h"

inline solucao_t melhor_solucao(double w, vector<double> lmb, vii edges, pair<int,int> best_nodes){

    solucao_t best;

    best.arestas = edges;
    best.arestas.push_back(make_pair(0, best_nodes.first));
    best.arestas.push_back(make_pair(0, best_nodes.second));

    best.penalizadores = lmb;

    best.cost = w;

    return best;
}

vector<int> calcula_graus(vii msp, int n, pair<int,int> melhores_nos){

    vector<int> graus(n, 0); //inicia os graus dos vertices com 0

    for(int i = 0; i < msp.size(); i++){
        graus[msp[i].second]++;
        graus[msp[i].first]++;
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

        cout << "Ax = b - " << acumulador << endl;
        return 0;
    }

    return (upper_bound - w) / acumulador;
}

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus){

    
    lmb[0] = 0;

    for(int i = 1; i < lmb.size(); i++){

        lmb[i] = lmb[i] + (u * (2 - graus[i]));
        //atualizando os penalizadores
    }

}

vvi altera_custos(vvi custos, vector<double> lmb){

    vvi custos_penalizados;

    for(int i = 0; i < lmb.size(); i++){
        vector<double> linha;

        for(int j = 0; j < lmb.size(); j++){
            
            linha.push_back(custos[i][j] - lmb[i] - lmb[j]);
            //aplicando os penalizadores nos custos da matriz
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

solucao_t subgradiente(double ub_heuristico, int n, vvi cost_matrix){
    // n = tamanho da instancia

    solucao_t best_solution;

    double ub = ub_heuristico;

    vector<double> lmb(n, 0); //lâmbida
    vector<double> best_lmb(n, 0); 

    int k = 0; //iterador
    double e = 1; //fator de passo
    double u = 0; //tamanho do passo

    double best = 0;
    best_lmb = lmb;
    
    vvi custos_penalizados = cost_matrix;

    //0.005 -  fator de passo minimo

    while(e >= 0.005){

        Kruskal x_(custos_penalizados);   

        double mst_cost = x_.MST(n);

        pair<int,int> melhores_nos = melhores_nos_0(custos_penalizados, mst_cost, n, x_.getEdges());

        vector<int> graus = calcula_graus(x_.getEdges(), n, melhores_nos);

        double w = mst_cost + custos_penalizados[0][melhores_nos.first] + custos_penalizados[0][melhores_nos.second];

        u = e * tamanho_do_passo(ub, w, graus);

        altera_penalizadores(lmb, u, graus);
    
        if(w > best_solution.cost){
            k = 0;

            best_solution = melhor_solucao(w, lmb, x_.getEdges(), melhores_nos);

        }else{
            k++;

            if(k >= 30){
  
                k = 0;
                e /= 2;

            }
        }

        if(u < 0.00001){
            print_subgradiente(graus);
            best_solution = melhor_solucao(w, lmb, x_.getEdges(), melhores_nos);
            break;
        }

        custos_penalizados = altera_custos(cost_matrix, lmb);
    }

    return best_solution;
}