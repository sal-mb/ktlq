#include <vector>
#include "Kruskal.h"
#include "data.h"

vector<int> calcula_graus(vii msp, int n){

    vector<int> graus(n, 0); //inicia os graus dos vertices com 0

    for(int i = 0; i < msp.size(); i++){
        graus[msp[i].second]++;
        graus[msp[i].first]++;
    }

    return graus;
}

inline double tamanho_do_passo(double upper_bound, double w, vector<int> graus){
    int acumulador = 0;

    for(int i = 0; i < graus.size(); i++){
        acumulador += (2 - graus[i]) * (2 - graus[i]); 
    }

    return (upper_bound - w) / acumulador;
}

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus){

    for(int i = 0; i < lmb.size(); i++){

        lmb[i] = u * (2 - graus[i]);
    }
}

inline vvi altera_custos(vvi custos, vector<double> lmb){

    vvi custos_penalizados;

    for(int i = 0; i < lmb.size(); i++){
        vector<double> linha;

        for(int j = 0; j < lmb.size(); j++){

            linha.push_back(custos[i][j] -lmb[i] -lmb[j]);

        }

        custos_penalizados.push_back(linha);
    }

    return custos_penalizados;
}

vector<double> subgradiente(double heuristic_ub, Data *data, vvi cost_matrix){
    int n = data->getDimension(); //tamanho da instancia

    double ub = heuristic_ub;

    vector<double> lmb(n, 0); //lâmbida
    vector<double> best_lmb(n, 0); 

    int k = 0; //iterador
    int e = 1; //fator de passo
    double u = 1; //tamanho do passo

    double best = 0;
    best_lmb = lmb;
    
    vvi custos_penalizados = cost_matrix;

    //0.01 -  fator de passo minimo

    while(e >= 0.005){

        Kruskal x_(custos_penalizados);   
        double w = x_.MST(n);

        vector<int> graus = calcula_graus(x_.getEdges(), n);
        cout << "w: " << w << endl;

        u = e * tamanho_do_passo(ub, w, graus);

        altera_penalizadores(lmb, u, graus);

        if(w > best){
            best = w;
            best_lmb = lmb;
            k = 0;

        }else{
            k++;

            if(k >= 100){
                k = 0;
                e /= 2;
            }
        }

        custos_penalizados = altera_custos(cost_matrix, lmb);
    }

    return best_lmb;
}