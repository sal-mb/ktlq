#include "BuscaLocal.h"
#include "Solucao.h"
#include <algorithm>
#include <utility>

int BISwap(Solucao *s, Data *data){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;

    for(int i = 1; i < s->sequencia.size()-1; i++){
        
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i+1];
        int vi_prev = s->sequencia[i-1];

        for(int j = i+1; j < s->sequencia.size()-1; j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j+1];
            int vj_prev = s->sequencia[j-1];

            double delta;

            if(j == i+1){

                delta = -data->getDistance(vi, vi_prev) -data->getDistance(vj, vj_next) +data->getDistance(vj, vi_prev) +data->getDistance(vi, vj_next);

            }else{

                delta = -data->getDistance(vi_prev, vi) -data->getDistance(vi_next, vi) -data->getDistance(vj_prev, vj) -data->getDistance(vj_next, vj) 
                +data->getDistance(vi_next, vj) + data->getDistance(vi_prev, vj) + data->getDistance(vj_prev, vi) + data->getDistance(vj_next, vi);

            }

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
    }

    if(bestDelta < 0){
        std::swap(s->sequencia[best_i], s->sequencia[best_j]);
        
        s->custoS = s->custoS + bestDelta;
        std::cout << s->custoS;
        calcula_custoS(s, data);
        std::cout << " = " << s->custoS << std::endl;

        return 1;

    }
    
    return 0;
}

int BI2_Opt(Solucao *s, Data *data){
    double bestDelta = 0;
    int best_i =0, best_j =0;

    for(int i = 0; i < s->sequencia.size()-1 ;i++){
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i+1];

        for(int j = i+2; j < s->sequencia.size()-1; j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j+1];

            double delta = -data->getDistance(vi_next, vi) -data->getDistance(vj_next, vj) +data->getDistance(vj_next, vi_next) +data->getDistance(vi, vj);

            if(delta < bestDelta){
                bestDelta = delta;
                best_i = i+1;
                best_j = j+1;
            }
        }
    }

    if(bestDelta < 0){
           
        std::reverse(s->sequencia.begin()+(best_i), s->sequencia.begin()+(best_j));
        s->custoS += bestDelta;

        std::cout << s->custoS;
        calcula_custoS(s, data);
        std::cout << " = " << s->custoS << std::endl;
        return 1;
    }

    return 0;

}

int BIOrOpt(Solucao *s, Data *data, int option){
    
    double bestDelta = 0;
    int best_i =0, best_j =0;

    if(option == 1){

        for(int i = 1; i < s->sequencia.size(); i++){
            int vi = s->sequencia[i];
            int vi_next = s->sequencia[i+1];
            int vi_prev = s->sequencia[i-1];

            for(int j = 1; j < s->sequencia.size(); j++){
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

            std::cout << s->custoS;
            calcula_custoS(s, data);
            std::cout << " = " << s->custoS << std::endl;
            return 1;

        }
        
        return 0;

    }else if(option == 2){
        int best_i2 =0;

        for(int i = 1; i < s->sequencia.size()-3; i++){
            int vi_prev = s->sequencia[i-1];
            int vi = s->sequencia[i];
            int vi2 = s->sequencia[i+1];
            int vi2_next = s->sequencia[i+2];

            for(int j = i + 2; j < s->sequencia.size()-1; j++){
                int vj_prev = s->sequencia[j];
                int vj_next = s->sequencia[j+1];

                double delta = -data->getDistance(vi_prev, vi) - data->getDistance(vi2_next, vi2) - data->getDistance(vj_prev, vj_next) 
                + data->getDistance(vj_prev, vi) + data->getDistance(vj_next, vi2) + data->getDistance(vi_prev, vi2_next);

                if(delta < bestDelta){
                    bestDelta = delta;

                    best_i = i;
                    best_i2 = i+1;
                    best_j = j+1;
                }
            }
        }

        if(bestDelta < 0){
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
            s->sequencia.erase(s->sequencia.begin()+best_i);
            s->sequencia.erase(s->sequencia.begin()+best_i);

            s->custoS += bestDelta;

            std::cout << s->custoS;
            calcula_custoS(s, data);
            std::cout << " = " << s->custoS << std::endl;
            return 1;
        }
        
        return 0;

    }else if(option == 3){
        
        int best_i2 =0, best_i3 =0;

        for(int i = 1; i < s->sequencia.size()-4; i++){
            int vi_prev = s->sequencia[i-1];
            int vi = s->sequencia[i];
            int vi2 = s->sequencia[i+1];
            int vi3 = s->sequencia[i+2];
            int vi3_next = s->sequencia[i+3];

            for(int j = i + 3; j < s->sequencia.size()-1; j++){
                int vj_prev = s->sequencia[j];
                int vj_next = s->sequencia[j+1];

                double delta = -data->getDistance(vi_prev, vi) - data->getDistance(vi3_next, vi3) - data->getDistance(vj_prev, vj_next) 
                + data->getDistance(vj_prev, vi) + data->getDistance(vj_next, vi3) + data->getDistance(vi_prev, vi3_next);

                if(delta < bestDelta){
                    bestDelta = delta;

                    best_i = i;
                    best_i2 = i+1;
                    best_i3 = i+2;
                    best_j = j+1;
                }
            }
        }

        if(bestDelta < 0){
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i3]);
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
            s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
            s->sequencia.erase(s->sequencia.begin()+best_i);
            s->sequencia.erase(s->sequencia.begin()+best_i);
            s->sequencia.erase(s->sequencia.begin()+best_i);

            s->custoS += bestDelta;

            std::cout << s->custoS;
            calcula_custoS(s, data);
            std::cout << " = " << s->custoS << std::endl;
            return 1;
        }
        
        return 0;
    }
    return 0;
}