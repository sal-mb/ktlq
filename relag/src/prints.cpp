#include "prints.h"

void print_best_nodes_0(pair<int,int> best_nodes, vvi cost_matrix){

	cout << "primeiro no: " << best_nodes.first << " - " << cost_matrix[0][best_nodes.first]
	<< ", segundo no: " << best_nodes.second << " - " << cost_matrix[0][best_nodes.second] << endl;
};

void print_edges(vii edges){


	cout << "\n ------ arestas ------ \n " << endl;	
    for(int i = 0; i < edges.size(); i++){
        cout << edges[i].first << " -> " << edges[i].second << " / "; 
    }

    cout << "\n";
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

void print_solution(solucao_t s){

	print_penalizadores(s.penalizadores);

	print_edges(s.arestas);

	cout << "custo: " << s.cost << endl;

};