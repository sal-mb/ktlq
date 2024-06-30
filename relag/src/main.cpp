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
#include "prints.h"

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

vvi cost_matrix_from_file(){

	ifstream file("matriz_de_custos.txt");

	vvi cost_matrix;

	for(int i = 0; i < 5; i++){
		vector<double> line_costs;

		for(int j = 0; j < 5; j++){
			double d;
			file >> d;
			line_costs.push_back(d);

		}

		cost_matrix.push_back(line_costs);
	}

	return cost_matrix;
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
	
	double tsp_cost;

	if(argv[3] == NULL){
		//se o valor do custo da solucao heuristica do tsp nao for passado como argumento
		//ele eh lido do arquivo "table.txt"
		//caso nao exista em "table.txt", o erro eh retornado
		tsp_cost = read_instance_cost(data->getInstanceName());
		
	}else{
		tsp_cost = stod(argv[3]);
	}
	
	auto start = chrono::high_resolution_clock::now();

	Node s_ = bnb(atoi(argv[2]), cost, tsp_cost+1, data->getDimension());

	auto stop = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	print_no(s_);

	delete data;

	return 0;
}
