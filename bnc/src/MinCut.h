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

typedef struct{

    int v = 0;
    double weight = -1;

} vertex;

typedef struct{
    
    int s;
    int t;
    double cotp; //cut of the phase
    
}st;

typedef struct{
    
    vector< int > s_;
    double cut_cost;

}cut;

extern vector< vector<int> > MinCut(double** x, int n);
void print_edges(double **x, int n);

#endif
