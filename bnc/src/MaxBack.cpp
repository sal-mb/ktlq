
#include "MaxBack.h"

void print_edges(double **x, int n){
    
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++){
            if(x[i][j] < EPSILON){
                x[i][j] = 0;
            }
            cout << x[i][j] << " - ";
        }
        cout << endl;
    }
}


double inline CalculateMaxBackValue(double **x, vector<int> s, int v){
    //b(v) = sum{x_uv}
    
    double b = 0;

    for(int i = 0; i < s.size(); i++){
        b +=  x[v][s[i]];
    }

    return b;
}

vector<int> InitCandidateList(int n){
    
    vector<int> cl;

    for(int i = 1; i < n; i++){
        cl.push_back(i);
    }

    return cl;
}

double inline ComputeCutMin(double **x, int v, int n){
    
    double cutmin = 0;
    
    for(int i = 0; i < n; i++){
        cutmin += x[v][i];
    }

    return cutmin;
}

vector< vector<int> > MaxBack(double **x,  int n){
    
    print_edges(x, n);
    
    vector< vector<int> > subtours;
    vector<int> s_0 = {0};
    //cl = nos nao pertecentes a s_0;
    vector<int> cl = InitCandidateList(n);
    
   return subtours;
}
