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


double inline CalculateMaxBackValue(double **x, vector<int> s, int v){
    //b(v) = sum{x_uv}
    
    double b = 0;

    for(int i = 0; i < s.size(); i++){
        b +=  x[v][s[i]];
    }

    return b;
}

vector<int> initCandidateList(int n){
    
    vector<int> cl;

    for(int i = 1; i < n; i++){
        cl.push_back(i);
    }

    return cl;
}

vector< vector<int> > MaxBack(double **x,  int n){
    
    print_edges(x, n);
    
    vector< vector<int> > subtours;
    vector<int> s_0 = {0};
    //cl = nos nao pertecentes a s_0;
    vector<int> cl = initCandidateList(n);
    
    
    
    
    
    
    return subtours;
}

vector< vector<int> > MinCut(double **x,  int n){
    
    return {};
}


