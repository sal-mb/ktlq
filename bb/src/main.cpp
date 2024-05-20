#include <climits>
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
		}
	}

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	double obj_value = hungarian_solve(&p);
	cout << "Obj. value: " << obj_value << endl;

	cout << "Assignment" << endl;
	hungarian_print_assignment(&p);


	// for(int i = 0; i < 5; i++){
	// 	for(int j = 0; j < 5; j++){
	// 		p.assignment[i][j] = 0;
	// 	}
	// }

	// p.assignment[0][3] = 1;
	// p.assignment[1][0] = 1;
	// p.assignment[2][4] = 1;
	// p.assignment[3][1] = 1;
	// p.assignment[4][2] = 1;

	// p.num_cols=p.num_rows=5;

	std::vector<std::vector<int>> subtours = detecta_subtours(&p);
	print_subtours(&subtours);

	int no_arc_prob1 = subtours[0][0] -1;
	int no_arc_prob2 = subtours[0][1] -1;

	std::cout << "\n\nno 1: " << no_arc_prob1 <<", no 2: " << no_arc_prob2 << std::endl;

	printf("\n------------- prob1 --------------\n");
	cost[no_arc_prob1][no_arc_prob2] = 9999999;
	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	obj_value = hungarian_solve(&p);
	subtours = detecta_subtours(&p);
	print_subtours(&subtours);

	cout << "\nObj. value: " << obj_value << endl;

	printf("\n------------- prob2 --------------\n");

	cost[no_arc_prob1][no_arc_prob2] = data->getDistance(no_arc_prob1, no_arc_prob2);
	cost[no_arc_prob2][no_arc_prob1] = 999999999;

	hungarian_init(&p, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	obj_value = hungarian_solve(&p);

	subtours = detecta_subtours(&p);
	print_subtours(&subtours);

	cout << "\nObj. value2: " << obj_value << endl;


	hungarian_free(&p);
	for (int i = 0; i < data->getDimension(); i++) delete [] cost[i];
	delete [] cost;
	delete data;

	// hungarian_problem_t p_;
	// hungarian_init(&p_, cost, data->getDimension(), data->getDimension(), mode); // Carregando o problema

	return 0;
}
