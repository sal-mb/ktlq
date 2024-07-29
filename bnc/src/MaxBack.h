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
 /*   
typedef struct{
    vector<int> nodes;
    int id;
    bool is_vertexA;
} vertex_type;
*/

typedef struct{
    double backValue = 0;
    int v;
    
} item;

extern vector <vector<int> > MaxBack(double** x, int n);
void print_edges(double **x, int n);

#endif
