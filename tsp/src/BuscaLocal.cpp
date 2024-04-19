#include "BuscaLocal.h"
#include "Solucao.h"
#include <algorithm>
#include <utility>

#define EPSILON 0.0005

void BuscaLocal(Solucao *s, Data *data){

    std::vector<int> metodos = {0, 1, 2, 3, 4};
    bool melhorou = false;

    while(!metodos.empty()){
        
        int BI = rand() % metodos.size();

        switch (metodos[BI]) {
            
            case 0:
                melhorou = BISwap(s, data);
                break;

            case 1:
                melhorou = BI2_Opt(s, data);
                break;

            default:
                melhorou = BIOrOpt(s, data, BI-1);
        }

        if(melhorou){
            metodos = {0, 1, 2, 3, 4};
        }else{
            metodos.erase(metodos.begin() + BI);
        }
    }
}


bool BISwap(Solucao *s, Data *data){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;

    for(int i = 1; i < s->sequencia.size()-1; i++){
        
        int a = s->sequencia[i];
        int a_next = s->sequencia[i+1];
        int a_prev = s->sequencia[i-1];

        for(int j = i+1; j < s->sequencia.size()-1; j++){
            int b = s->sequencia[j];
            int b_next = s->sequencia[j+1];
            int b_prev = s->sequencia[j-1];

            double delta;

            if(j == i+1){

                delta = -data->getDistance(a, a_prev) -data->getDistance(b, b_next) +data->getDistance(b, a_prev) +data->getDistance(a, b_next);

            }else{

                delta = -data->getDistance(a_prev, a) -data->getDistance(a_next, a) -data->getDistance(b_prev, b) -data->getDistance(b_next, b) 
                +data->getDistance(a_next, b) + data->getDistance(a_prev, b) + data->getDistance(b_prev, a) + data->getDistance(b_next, a);

            }

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
    }

    if(bestDelta + EPSILON < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        
        s->custoS = s->custoS + bestDelta;
        // std::cout << s->custoS;
        // calcula_custoS(s, data);
        // std::cout << " = " << s->custoS << std::endl;

        return true;

    }
    
    return false;
}

bool BI2_Opt(Solucao *s, Data *data){
    double bestDelta = 0;
    int best_i =0, best_j =0;

    for(int i = 0; i < s->sequencia.size()-1 ;i++){
        int a = s->sequencia[i];
        int a_next = s->sequencia[i+1];

        for(int j = i+2; j < s->sequencia.size()-1; j++){
            int b = s->sequencia[j];
            int b_next = s->sequencia[j+1];

            double delta = -data->getDistance(a_next, a) -data->getDistance(b_next, b) +data->getDistance(b_next, a_next) +data->getDistance(a, b);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i+1;
                best_j = j+1;
            }
        }
    }

    if(bestDelta + EPSILON < 0){
           
        std::reverse(s->sequencia.begin()+(best_i), s->sequencia.begin()+(best_j));
        s->custoS += bestDelta;

        // std::cout << s->custoS;
        // calcula_custoS(s, data);
        // std::cout << " = " << s->custoS << std::endl;
        return true;
    }

    return false;

}

bool BIOrOpt(Solucao *s, Data *data, int option){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;
    int n = s->sequencia.size();

        for(int i = 1; i < n-option; i++){

            int a_prev = s->sequencia[i-1];
            int a_begin = s->sequencia[i];
            int a_end = s->sequencia[i+option-1];
            int a_next = s->sequencia[i+option];

            for(int j = 1; j < n; j++){

                int b_prev = s->sequencia[j-1];
                int b = s->sequencia[j];

                if((j+option-1) >= i && i >= (j-option)){continue;}

                double delta = -data->getDistance(a_prev, a_begin) -data->getDistance(a_end, a_next) -data->getDistance(b_prev, b)
                +data->getDistance(a_prev, a_next) +data->getDistance(b_prev, a_begin) +data->getDistance(a_end, b);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }

            }
        }

        if(bestDelta + EPSILON < 0){
            // std::cout << "i: " << best_i << " j: " << best_j << std::endl;
            // std::cout << "element i: " << s->sequencia[best_i] << " element j: " << s->sequencia[best_j] << std::endl;

            Solucao s_ = *s;

            s->sequencia.insert(s->sequencia.begin()+best_j, s_.sequencia.begin()+best_i, s_.sequencia.begin()+best_i+option);

            if(best_j > best_i){
                s->sequencia.erase(s->sequencia.begin()+best_i, s->sequencia.begin()+best_i+option);
            }else{
                s->sequencia.erase(s->sequencia.begin()+best_i+option, s->sequencia.begin()+best_i+option+option);
            }

            s->custoS += bestDelta;

            // std::cout << s->custoS;
            // calcula_custoS(s, data);
            // std::cout << " = " << s->custoS << std::endl;

            return true;
        }
        
    return false;
}