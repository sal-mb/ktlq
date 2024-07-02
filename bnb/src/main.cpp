#include "bnb.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unistd.h>
#include "data.h"
#include "hungarian.h"
#include <sys/wait.h>
#include <chrono>

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
	double **cost = new double*[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++){
		cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++){
			cost[i][j] = data->getDistance(i,j);
		}
	}
	
	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema
	
	double obj = hungarian_solve(&p);
	//eh necessario carregar o problema para definir os valores de p->num_rows e p->num_cols utilizados na funcao bnb

	double tsp_cost;

	if(argv[3] == NULL){
		//se o valor do custo da solucao heuristica do tsp nao for passado como argumento
		//ele eh lido do arquivo "table.txt"
		//caso nao exista em "table.txt", o erro eh retornado
		tsp_cost = read_instance_cost(data->getInstanceName());
		
	}else{
		tsp_cost = stod(argv[3]);
	}
	
    int branching = atoi(argv[2]);

	auto start = chrono::high_resolution_clock::now();
    
    Node s;
    if(branching < 2){
	    s = bnb(&p, atoi(argv[2]) , cost, tsp_cost);
    }else{
        s = bnb_bestbound(&p, cost, tsp_cost);
    }


	auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << data->getInstanceName() << " - " << argv[2] << std::endl;
	print_node_solution(&s);
	printf("%.3lf - %.1lf\n\n", (double) duration.count()/1000, s.lower_bound);

	delete data;

	return 0;
}
