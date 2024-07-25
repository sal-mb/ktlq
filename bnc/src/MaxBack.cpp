#include "MaxBack.h"

bool ordena_por_maxback(item a, item b){ return a.backValue > b.backValue; }

void print_edges(double **x, int n){

    for(int i = 0; i < n;i++){
        for(int j = 0; j < n;j++){
            cout << x[i][j] << " - ";
        }
        cout << endl;
    }
}


double inline CalculateMaxBackValue(double **x, vector< item > s, int v){
    //b(v) = sum{x_uv}

    double b = 0;

    int max_i, max_j;
    for(int i = 0; i < s.size(); i++){

        if(v < s[i].v){
            b += x[v][s[i].v];

        }else{
            b += x[s[i].v][v];
        }

    }

    return b;
}

vector< item > InitCandidateList(double** x, int n){

    vector< item > cl;
    item v;
    v.v = 0;

    cout << "initializing candidate list..;\n" << endl;
    for(int i = 1; i < n; i++){
        v.v = i;
        cl.push_back(v);
    }

    return cl;
}

double inline computeCutMinV(double** x, vector< bool > s, int v){

    double cutminv = 0;

    for(int i = 0; i < s.size(); i++){
        if(s[i] == false){
            if(v > i){
                cutminv += x[i][v];
            }else{
                cutminv += x[v][i];
            }
        }
    }

    return cutminv;
}

double inline ComputeCutMin(double** x, vector< bool > s){

    double cutmin = 0;

    cout << "computing mincut value...\n" << endl;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == true){
            cutmin += computeCutMinV(x, s, v);
        }
    }

    cout << "cutmin value: " << cutmin << endl;
    return cutmin;
}

void computeBackValues(vector< item > &s, vector< item > s_, double** x){
    cout << "computing maxBack values of s...\n" << endl;

    for(int i = 0; i < s.size(); i++){
        s[i].backValue = CalculateMaxBackValue(x, s_, s[i].v);
        cout << "node: " << s[i].v << ", maxback value: " << s[i].backValue << endl;
    }

    std::sort(s.begin(), s.end(), ordena_por_maxback);

}

void inline updateBackValues(vector< item > &s, int v, double** x){
    for(int i = 0; i < s.size(); i++){
        if(s[i].v > v){
            s[i].backValue += x[v][s[i].v];
        }else{

            s[i].backValue += x[s[i].v][v];
        }
    }
}

vector< vector<int> > MaxBack(double **x,  int n){
    

    vector< vector<int> > subtours;
    vector< bool > s_0(n,false);
    vector< item > backValues(n-1);
    double cutval, cutmin;

    s_0[0] = true;

    cutmin = cutval = ComputeCutMin(x, s_0);
    cout << cutmin << endl;   
        


    for(int i = 0; i < s_min.size(); i++){
        cout << s_min[i].v << " -> ";
    }

    

    return subtours;
}
