#include "separation.h"

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

vector< vector<int> > MaxBack(double **x,  int n){
    
    print_edges(x, n);
    
    vector< vector<int> > subtours;
    vector<int> s = {0};

    
    
    
    return subtours;
}

vector< vector<int> > MinCut(double **x,  int n){
    
    return {};
}

double inline CalculateMaxBackValue(double **x, vector<int> s, int v){
    //b(v) = sum{x_uv}
    
    double b = 0;

    for(int i = 0; i < s.size(); i++){
        b +=  x[v][s[i]];
    }

    return b;
}


