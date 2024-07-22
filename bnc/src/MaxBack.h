#ifndef MAXBACK_H
#define MAXBACK_H

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
    vector<int> nodes;
    int id;
    bool is_vertexA;
} vertex_type;

extern vector <vector<int> > MaxBack(double** x, int n);
void print_edges(double **x, int n);
double inline ComputeCutMin(double **x, int v);
double inline CalculateMaxBackValue(double **x, vector<int> s, int v);
vector<int> initCandidateList(int n);

#endif

