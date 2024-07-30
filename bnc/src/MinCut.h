#ifndef MINCUT_H 
#define MINCUT_H 

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

#define EPSILON 0.00000001

using namespace std;

extern vector< vector<int> > MinCut(double** x, int n);
#endif
