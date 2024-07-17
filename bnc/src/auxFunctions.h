//---------------------------------------------------------------------------

/*******************************************************/
/* Auxiliary Function's Set by Prof. Anand Subramanian */
/*******************************************************/

#ifndef auxFunctions_H
#define auxFunctions_H

#include <ilcplex/ilocplex.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <pthread.h>

using namespace std;

string getInstanceName(char **argv);
void printResults(IloCplex cplex, string instanceName, double time);
void printSolution(IloCplex cplex, IloArray <IloBoolVarArray> x, int n);
void printResultsToFile(IloCplex cplex, string instanceName, double time);

#endif
//---------------------------------------------------------------------------