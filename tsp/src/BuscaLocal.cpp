#include "BuscaLocal.h"
#include "Solucao.h"
#include <algorithm>
#include <utility>

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

    if(bestDelta < 0){
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

    if(bestDelta < 0){
           
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

    if(option == 1){

        for(int i = 1; i < s->sequencia.size()-1; i++){
            int a = s->sequencia[i];
            int a_next = s->sequencia[i+1];
            int a_prev = s->sequencia[i-1];

            for(int j = 1; j < s->sequencia.size(); j++){
                int b_prev = s->sequencia[j-1];
                int b = s->sequencia[j];

                if(i == j-1 || i == j){continue;}

                double delta = -data->getDistance(a, a_prev) -data->getDistance(a, a_next) +data->getDistance(a_next, a_prev) -data->getDistance(b, b_prev)  
                +data->getDistance(b, a) + data->getDistance(a, b_prev);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }

            }
        }

        if(bestDelta < 0){
            if(best_j > best_i){
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
                s->sequencia.erase(s->sequencia.begin()+best_i);

            }else{
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
                s->sequencia.erase(s->sequencia.begin()+best_i+1);
            }


            s->custoS += bestDelta;

            // std::cout << s->custoS;
            // calcula_custoS(s, data);
            // std::cout << " = " << s->custoS << std::endl;
            return true;

        }
        
        return false;

    }else if(option == 2){
        int best_i2 =0;

        for(int i = 1; i < s->sequencia.size()-2; i++){
            int a_prev = s->sequencia[i-1];
            int a = s->sequencia[i];
            int a2 = s->sequencia[i+1];
            int a2_next = s->sequencia[i+2];

            for(int j = 1; j < s->sequencia.size(); j++){
                int b_prev = s->sequencia[j-1];
                int b = s->sequencia[j];

                if(i == j || i == j - 1 || i == j - 2 || i == j + 1){continue;}

                double delta = -data->getDistance(a_prev, a) - data->getDistance(a2_next, a2) - data->getDistance(b_prev, b) 
                + data->getDistance(b_prev, a) + data->getDistance(b, a2) + data->getDistance(a_prev, a2_next);

                if(delta < bestDelta){
                    bestDelta = delta;

                    best_i = i;
                    best_i2 = i+1;
                    best_j = j;
                }
            }
        }

        if(bestDelta < 0){
        
            if (best_i < best_j) {
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
                s->sequencia.erase(s->sequencia.begin()+best_i);
                s->sequencia.erase(s->sequencia.begin()+best_i);
                // std::cout << " i < j" << std::endl;
            }else{
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
                s->sequencia.erase(s->sequencia.begin()+best_i+2);
                s->sequencia.erase(s->sequencia.begin()+best_i+2);
                // std::cout << " i > j" << std::endl;

            }
            s->custoS += bestDelta;

            // std::cout << s->custoS;
            // calcula_custoS(s, data);
            // std::cout << " = " << s->custoS << std::endl;
            return true;
        }
        
        return false;

    }else if(option == 3){
        
        int best_i2 =0, best_i3 =0;

        for(int i = 1; i < s->sequencia.size()-3; i++){
            int a_prev = s->sequencia[i-1];
            int a = s->sequencia[i];
            int a2 = s->sequencia[i+1];
            int a3 = s->sequencia[i+2];
            int a3_next = s->sequencia[i+3];

            for(int j = 1; j < s->sequencia.size(); j++){
                int b_prev = s->sequencia[j-1];
                int b = s->sequencia[j];

                if(i == j || i == j - 1 || i == j - 2 || i == j - 3 || i == j + 1 || i == j + 2){continue;}

                double delta = -data->getDistance(a_prev, a) - data->getDistance(a3_next, a3) - data->getDistance(b_prev, b) 
                + data->getDistance(b_prev, a) + data->getDistance(b, a3) + data->getDistance(a_prev, a3_next);

                if(delta < bestDelta){
                    bestDelta = delta;

                    best_i = i;
                    best_i2 = i+1;
                    best_i3 = i+2;
                    best_j = j;
                }
            }
        }

        if(bestDelta < 0){
            
            if (best_i < best_j) {
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i3]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i2]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i]);
                s->sequencia.erase(s->sequencia.begin()+best_i);
                s->sequencia.erase(s->sequencia.begin()+best_i);
                s->sequencia.erase(s->sequencia.begin()+best_i);
                // std::cout << " i < j" << std::endl;
            }else{

                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i3]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i3]);
                s->sequencia.insert(s->sequencia.begin()+best_j, s->sequencia[best_i3]);
                s->sequencia.erase(s->sequencia.begin()+best_i+3);
                s->sequencia.erase(s->sequencia.begin()+best_i+3);
                s->sequencia.erase(s->sequencia.begin()+best_i+3);
                // std::cout << " i > j" << std::endl;

            }
            s->custoS += bestDelta;

            // std::cout << s->custoS;
            // calcula_custoS(s, data);
            // std::cout << " = " << s->custoS << std::endl;
            return true;
        }
        
        return false;
    }
    return false;
}