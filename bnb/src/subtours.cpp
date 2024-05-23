#include <algorithm>
#include "subtours.h"
#include <unistd.h>
#include <vector>

bool ordena_por_tamanho(std::vector<int> a, std::vector<int> b){ return a.size() < b.size(); }

void print_subtour(std::vector<int> *subtour){
      std::cout << "{";

        for(int i = 0; i < subtour->size()-1; i++){
            std::cout << subtour->at(i) +1 << ", ";
        }
        std::cout << subtour->at(subtour->size()-1) +1<<"}";
}

void print_subtours(std::vector<std::vector<int>> *subtours){

    std::cout << "( ";

    for(int i = 0; i < subtours->size()-1; i++){

        print_subtour(&(subtours->at(i)));
        std::cout << ", ";

    }
    print_subtour(&(subtours->at(subtours->size()-1)));

    std::cout << ")";
}

std::vector<int> detecta_subtours(hungarian_problem_t *p){
    
    std::vector<std::vector<int>> subtours;
    std::vector<int> subtour;

    int linhas = p->num_rows;
    int colunas = p->num_cols;
    
    std::vector<int> percorreu(linhas, 0);

    int l = 0, c = 0;
    
    subtour.push_back(0);

    int percorreu_todos = 0;
    int achou = 0;

    while (!percorreu_todos){
        if(percorreu[l] == 0){

            for(c = 0; c < colunas; c++){
                
                if(p->assignment[l][c] == 1){
                    percorreu[l] = 1;
                    l = c;
                    subtour.push_back(l);
                    break;
                }

            }

        }else{

            std::vector<int>::iterator it;
            it = std::find(subtour.begin(), subtour.end()-1, l);

            if(it != subtour.end()-1){
    
                percorreu_todos = 1;
                std::vector<int> subtour_;
                subtour_.insert(subtour_.begin(), it, subtour.end());
                subtours.push_back(subtour_);
                if(subtour_.size() == 2){
                    achou = 1;
                    break; //se o tamanho do subtour for 2, ele ja eh o menor, entao pode terminar o loop
                }

                for(int i = 0; i < linhas; i++){
                    if(percorreu[i] == 0){
                        l = i;
                        percorreu_todos = 0;
                        subtour.push_back(l);
                        break;
                    }
                }
            }
        }
    }
    if(!achou){
        std::sort(subtours.begin(), subtours.end(), ordena_por_tamanho);
    }
    subtour = subtours[0];

    subtours.clear();
    subtours.resize(0);
    return subtour;
}