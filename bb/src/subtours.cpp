#include "data.h"
#include <algorithm>
#include <cstring>
#include <iterator>
#include <vector>
#include "subtours.h"
#include "hungarian.h"
#include <unistd.h>
void print_subtours(std::vector<std::vector<int>> *subtours){

    std::cout << "( ";

    for(int i = 0; i < subtours->size(); i++){
        std::cout << "{";

        for(int j = 0; j < subtours->at(i).size()-1; j++){
            std::cout << subtours->at(i)[j] << ", ";
        }
        if(i == subtours->size()-1){
            std::cout << subtours->at(i)[subtours->at(i).size()-1]<<"} ";
            break;
        }
        std::cout << subtours->at(i)[subtours->at(i).size()-1]<<"}, ";
    }

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
    percorreu[0] = 1;

    int percorreu_todos = 0;

    while (!percorreu_todos){
        // sleep(1);
        // printf("l:%d\n", l);
        for(c = 0; c < colunas; c++){
            
            if(copy[l][c] > 0){
                printf("l:%d, c:%d\n", l,c);
                l = c;
                copy[l][c] = -1;
                subtour.push_back(l+1);
                percorreu[l] = 1;
                break;
            }

        }

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
                }
            }
        }
    }

    return subtours;
}