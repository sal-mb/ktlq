#include "BuscaLocal.h"

int BISwap(Solucao *s, Data *data){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;

    for(int i = 1; i < s->sequencia.size()-1; i++){
        
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i+1];
        int vi_prev = s->sequencia[i-1];

        for(int j = i; j < s->sequencia.size()-1; j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j+1];
            int vj_prev = s->sequencia[j-1];

            double delta = -data->getDistance(vi_prev, vi) -data->getDistance(vi_next, vi) -data->getDistance(vj_prev, vj) -data->getDistance(vj_next, vj) 
                +data->getDistance(vi_next, vj) + data->getDistance(vi_prev, vj) + data->getDistance(vj_prev, vi) + data->getDistance(vj_next, vi);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
    }

    if(bestDelta < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        s->custoS += bestDelta;
        return 1;

    }
    
    return 0;
}

int BIOrOpt(Solucao *s, Data *data, int option){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;

    if(option == 1){

        for(int i = 1; i < s->sequencia.size()-1; i++){
            int vi = s->sequencia[i];
            int vi_next = s->sequencia[i+1];
            int vi_prev = s->sequencia[i-1];

            for(int j = i + 1; j < s->sequencia.size(); j++){
                int vj_prev = s->sequencia[j-1];
                int vj = s->sequencia[j];

                double delta = -data->getDistance(vi, vi_prev) -data->getDistance(vi, vi_prev) +data->getDistance(vi_next, vi_prev) -data->getDistance(vj, vj_prev)  
                +data->getDistance(vj, vi) + data->getDistance(vi, vj_prev);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }

            }
        }

        if(bestDelta < 0){
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
            s->sequencia.erase(s->sequencia.begin()+best_i);
            s->custoS += bestDelta;
            return 1;

        }
        
        return 0;

    }else if(option == 2){
        
    }
    for(int i = 1; i < s->sequencia.size()-1; i++){
        
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i+1];
        int vi_prev = s->sequencia[i-1];

        for(int j = i; j < s->sequencia.size()-1; j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j+1];
            int vj_prev = s->sequencia[j-1];

            double delta = -data->getDistance(vi_prev, vi) -data->getDistance(vi_next, vi) -data->getDistance(vj_prev, vj) -data->getDistance(vj_next, vj) 
                +data->getDistance(vi_next, vj) + data->getDistance(vi_prev, vj) + data->getDistance(vj_prev, vi) + data->getDistance(vj_next, vi);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
    }

    if(bestDelta < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        s->custoS += bestDelta;
        return 1;

    }
    
    return 0;

}