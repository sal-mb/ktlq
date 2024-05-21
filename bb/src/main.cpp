#include "bnb.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

#include "data.h"
#include "hungarian.h"
#include "subtours.h"


int main(int argc, char** argv) {

	Data * data = new Data(argc, argv[1]);
	data->readData();

	double **cost = new double*[data->getDimension()];
	for (int i = 0; i < data->getDimension(); i++){
		cost[i] = new double[data->getDimension()];
		for (int j = 0; j < data->getDimension(); j++){
			cost[i][j] = data->getDistance(i,j);
			std::cout << cost[i][j] << " ";
		}
		printf("\n");
	}
	
	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema
	double obsolve = hungarian_solve(&p);

	// std::vector<std::vector<int>> subtours = detecta_subtours(&p);
	// print_subtours(&subtours);

	// std::cout << "\ncusto: " <<obsolve << std::endl;

	// p.cost[subtours[0][0]-1][subtours[0][1]-1] = 99999999;
	// obsolve = hungarian_solve(&p);

	// subtours = detecta_subtours(&p);
	// print_subtours(&subtours);
	// std::cout << "\ncusto: " <<obsolve << std::endl;

	//argv[2] = 1 - bfs, 0 - dfs;
	bnb(&p, atoi(argv[2]) , cost);
	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	delete data;

	return 0;
}
