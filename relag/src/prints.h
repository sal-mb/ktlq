#pragma once

#include "subgradiente.h"

void print_edges(vii edges, Data *data){
    for(int i = 0; i < edges.size(); i++){
        cout << edges[i].first << " -> " << edges[i].second << " / "; 
    }
};
void print_penalizadores(vector<double> lmb){

	for(int i = 0; i < lmb.size(); i++){
		cout << lmb[i] << endl;
	}
    
};

void print_subgradiente(vector<int> graus){

	for(int i = 0; i < graus.size(); i++){
		cout << graus[i] << endl;
	}
    
};
