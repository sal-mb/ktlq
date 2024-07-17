//---------------------------------------------------------------------------

/*******************************************************/
/* Auxiliary Function's Set by Prof. Anand Subramanian */
/*******************************************************/

#include "auxFunctions.h"

string getInstanceName(char **argv)
{
	string temp(argv[1]);
	string::size_type loc = temp.find_last_of(".", temp.size() );
	string::size_type loc2 = temp.find_last_of("/", temp.size() );
	string nomeDaInstancia;
	
	if (loc != string::npos) {
		nomeDaInstancia.append(temp, loc2+1, loc-loc2-1 );
		//cout << "\n1-" << nomeDaInstancia << endl;
	}
	else {
		nomeDaInstancia.append(temp, loc2+1, temp.size() );
		//cout << "\n2-" << nomeDaInstancia << endl;
	}
	
	return nomeDaInstancia;
}

void printResults(IloCplex cplex, string instanceName, double time)
{

	cout << "\n\nBranch-and-cut_Results: \n" << endl;

	cout << "Instance: " << instanceName << endl;
	cout << "Tree_Size: " << cplex.getNnodes() + cplex.getNnodesLeft() + 1 << endl;
	cout << "Total_Time: " << time << endl;
	cout << "LB: " << cplex.getBestObjValue() << endl;
	cout << "UB: " << cplex.getObjValue() << endl; 
	cout << "Status: " << cplex.getStatus() << endl;
}

void printResultsToFile(IloCplex cplex, string instanceName, double time)
{
	ofstream results1("Results1.txt", ios::app);
	results1 << "Instance: " << instanceName;
	results1 << " Tree_Size: " <<  cplex.getNnodes() + cplex.getNnodesLeft() + 1;
	results1 << " Total_Time: " << time;
	results1 << " LB: " << cplex.getBestObjValue();
	results1 << " UB: " << cplex.getObjValue() ; 
	results1 << " Status: " << cplex.getStatus();
	results1 << endl;
	results1.close();
}

void printSolution(IloCplex cplex, IloArray <IloBoolVarArray> x, int n)
{
	bool **sol = new bool*[n];
	vector<int> solution;

	for (int i = 0; i < n; i++) {
		sol[i] = new bool[n];
	}

	/************** Getting the solution **************/
	//cout << "\nSolution:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(j > i){
				sol[i][j] = 0;
				if (cplex.getValue(x[i][j]) > 0.5) {
					//cout << "X(" << i << "," << j << ") = " << cplex.getValue(x[i][j]) << " ";
					sol[i][j] = 1;
					sol[j][i] = 1;
				}
			}
			else{
				sol[i][j] = 0;
			}
		}
		//cout << endl;
	}
	/**************************************************/
	
	/*************** Building the route ***************/
	solution.push_back(0);
	int p;
	vector<bool> in_solution(n, false);
	in_solution[0] = true;
	bool find = true;
	int last_index = 0, current_index = 0;

	while (solution.size() < n){
		p = solution[last_index];

		for(int j = 0; j < n; j++){
			if (sol[p][j] == 1 || sol[j][p] == 1) {
				if(in_solution[j] == false){
					solution.insert(solution.begin() + current_index + 1, j);
					in_solution[j] = true;
					current_index++;
				}
			}
		}
		last_index++;
		current_index = last_index;
	}
	solution.push_back(0);
	/**************************************************/

	cout << "\nRoute: ";
	for (int i = 0; i < solution.size(); i++) {
		cout << solution[i] + 1 << " ";
	}
	cout << endl;

	/************** Cleaning the memory ***************/
	for (int i = 0; i < n; i++) {
		delete[] sol[i];
	}
	delete[] sol;
	/**************************************************/
}
//---------------------------------------------------------------------------