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
            cutmin += computeCutMinV(x, s, i);
        }
    }

    cout << "cutmin value: " << cutmin << endl;
    return cutmin;
}

double inline CalculateMaxBackValue(double **x, vector< bool > s, int v){
    //b(v) = sum{x_uv}

    double b = 0;

    int max_i, max_j;
    for(int i = 0; i < s.size(); i++){
        
        if(s[i] == true){
            if(v < i){
                b += x[v][i];

            }else{
                b += x[i][v];
            }

        }
        
    }
    
    return b;
}
void computeBackValues(vector< bool > &s, vector< item > &backValues, double** x){
    cout << "computing maxBack values of s...\n" << endl;
    
    backValues.clear();

    for(int i = 0; i < s.size(); i++){
        if(s[i] == false){
            item v;
            v.v = i;
            v.backValue = CalculateMaxBackValue(x, s, i);

            backValues.push_back(v);
        }
    }
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
    vector< item > backValues;
    double cutval, cutmin;

    s_0[0] = true;  

    cutmin = cutval = ComputeCutMin(x, s_0);
    cout << cutmin << endl; 

    computeBackValues(s_0, backValues, x);

    for(int i = 0; i < backValues.size(); i++){
       cout << "backValue: " << backValues[i].backValue << endl;
       cout << "v: " << backValues[i].v << endl;
    }

    return subtours;
}
