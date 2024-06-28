#include "prints.h"

void print_best_nodes_0(pair<int,int> best_nodes, vvi cost_matrix){

	cout << "primeiro no: " << best_nodes.first << " - " << cost_matrix[0][best_nodes.first]
	<< ", segundo no: " << best_nodes.second << " - " << cost_matrix[0][best_nodes.second] << endl;
}

void print_edges(vii edges){


	cout << "\n ------ arestas ------ \n " << endl;	
    for(int i = 0; i < edges.size(); i++){
        cout << edges[i].first << " -> " << edges[i].second << " / "; 
    }

    cout << "\n";
}

void print_penalizadores(vector<double> lmb){

	cout << "\n ------ penalizadores ------ \n " << endl;	

	for(int i = 0; i < lmb.size(); i++){
		cout << lmb[i] << " _ ";
	}
	cout << "\n";
    
}

void print_subgradiente(vector<int> graus){
	
	cout << "\n ------ subgradiente ------ \n " << endl;	
	for(int i = 0; i < graus.size(); i++){
		cout << 2 - graus[i] << " _ ";
	}
    
	cout << "\n";

}

void print_matriz_de_custo(vvi cost){

	int n = cost.size();

	cout << "\n------ matriz de custos ------\n" << endl;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cout << cost[i][j] << " _ ";
		}
		cout << "\n";
	}
}

void print_no(Node no){

	print_penalizadores(no.penalizadores);

	print_edges(no.arestas);

	cout << "custo: " << no.cost << endl;

}

void print_arcos_para_proibir(vector<pair<int,int>> arcos){

	cout << "\n------ arcos para proibir ------\n" << endl;

	for(int i = 0; i < arcos.size(); i++){

		cout << arcos[i].first << " -> " << arcos[i].second << " / ";

	}

}