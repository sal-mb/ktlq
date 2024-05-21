#include "bnb.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;

#include "data.h"
#include "hungarian.h"
#include "subtours.h"
#include <pthread.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	//fork para executar o tsp heuristico
	int pid = fork();

	if(pid == 0){
		execl("./tsp", "./tsp", argv[1], (char *)NULL);
		exit(EXIT_SUCCESS);

	}
	waitpid(pid, NULL, 0);

	//leitura do resultado do tsp heuristico
	std::ifstream fd("tsp_output.txt");

	std::string tsp;

	std::getline(fd, tsp);
	double tsp_cost = std::stod(tsp);

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
	
	//eh necessario carregar o problema para definir os valores de p->num_rows e p->num_cols utilizados na funcao bnb

	bnb(&p, atoi(argv[2]) , cost, tsp_cost);

	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	delete data;

	return 0;
}
