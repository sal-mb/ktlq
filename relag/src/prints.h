#pragma once

#include "subgradiente.h"

void print_edges(vii edges, Data *data){


	cout << "\n ------ edges ------ \n " << endl;	
    for(int i = 0; i < edges.size(); i++){
        cout << edges[i].first << " -> " << edges[i].second << " / "; 
    }
};

void print_penalizadores(vector<double> lmb){

	cout << "\n ------ penalizadores ------ \n " << endl;	

	for(int i = 0; i < lmb.size(); i++){
		cout << lmb[i] << " _ ";
	}
	cout << "\n";
    
};

void print_subgradiente(vector<int> graus){
	
	cout << "\n ------ subgradiente ------ \n " << endl;	
	for(int i = 0; i < graus.size(); i++){
		cout << 2 - graus[i] << " _ ";
	}
    
	cout << "\n";

};

void print_matriz_de_custo(vvi cost){

	cout << "\n------ matriz de custos ------\n" << endl;

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			cout << cost[i][j] << " _ ";
		}
		cout << "\n";
	}
};
