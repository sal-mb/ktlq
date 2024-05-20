#include <algorithm>
#include "subtours.h"
#include <unistd.h>

bool ordena_por_tamanho(std::vector<int> a, std::vector<int> b){ return a.size() < b.size(); }

void print_subtour(std::vector<int> *subtour){
      std::cout << "{";

        for(int i = 0; i < subtour->size()-1; i++){
            std::cout << subtour->at(i) << ", ";
        }
        std::cout << subtour->at(subtour->size()-1)<<"}";
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

std::vector<std::vector<int>> detecta_subtours(hungarian_problem_t *p){
    
    std::vector<std::vector<int>> subtours;
    std::vector<int> subtour;

    int linhas = p->num_rows;
    int colunas = p->num_cols;

    int copy[linhas][colunas];

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            copy[i][j] = p->assignment[i][j];
        }
    }

    std::vector<int> percorreu(linhas, 0);

    int l = 0, c = 0;
    
    subtour.push_back(1);
    int percorreu_todos = 0;

    while (!percorreu_todos){
        if(percorreu[l] == 0){
            for(c = 0; c < colunas; c++){
                
                if(copy[l][c] > 0){
                    percorreu[l] = 1;
                    l = c;
                    subtour.push_back(l+1);
                    break;
                }

            }

        }else{

            std::vector<int>::iterator it;
            it = std::find(subtour.begin(), subtour.end()-1, l+1);


            if(it != subtour.end()-1){
    
                percorreu_todos = 1;
                std::vector<int> subtour_;
                subtour_.insert(subtour_.begin(), it, subtour.end());
                subtours.push_back(subtour_);
                
                for(int i = 0; i < percorreu.size(); i++){
                    if(percorreu[i] == 0){
                        l = i;
                        percorreu_todos = 0;
                        subtour.push_back(l+1);
                        break;
                    }
                }
            }
        }
    }

    std::sort(subtours.begin(), subtours.end(), ordena_por_tamanho);

    return subtours;
}