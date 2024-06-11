#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unistd.h>
#include "data.h"
#include <chrono>
#include <vector>
#include "Kruskal.h"
#include "subgradiente.h"

using namespace std;

double read_instance_cost(std::string instance_name){

	std::ifstream instance_table ("table.txt");

	std::string word;

	while(std::getline(instance_table, word, '\n')){
		if(word.find(instance_name) != string::npos){
			break;
		}
	}

	std::getline(instance_table, word, '\n');

	if(word == "\0"){
		std::cout << "Instance not in table.txt" << std::endl;
		std::cout << "./exeLaRP [Instance] [branching] (0 - dfs, 1 - bfs) [upper_bound]" << std::endl;
		exit(1);
	}
	return stod(word);
}

int main(int argc, char** argv) {

	//le a instacia
	Data * data = new Data(argc, argv[1]);
	data->readData();

	//inicializa matriz custo
	
	vvi cost;

	for (int i = 0; i < data->getDimension(); i++){
		vector<double> line_costs;
		for (int j = 0; j < data->getDimension(); j++){
			line_costs.push_back(data->getDistance(i,j));
		}
		cost.push_back(line_costs);
	}
	
	Kruskal *kruskal = new Kruskal(cost);

	vii solution;

	kruskal->MST(data->getDimension());

	solution = kruskal->getEdges();

	for(int i = 0; i < solution.size(); i++){
		cout << solution[i].first << " - " << solution[i].second << endl;
	}

	cout << "\n-------------------\n" << endl;
	double tsp_cost;

	// if(argv[3] == NULL){
	// 	//se o valor do custo da solucao heuristica do tsp nao for passado como argumento
	// 	//ele eh lido do arquivo "table.txt"
	// 	//caso nao exista em "table.txt", o erro eh retornado
	// 	tsp_cost = read_instance_cost(data->getInstanceName());
		
	// }else{
	// 	tsp_cost = stod(argv[3]);
	// }
	
	auto start = chrono::high_resolution_clock::now();

	auto stop = chrono::high_resolution_clock::now();
    
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	delete data;

	delete kruskal;

	return 0;
}
