#include "MaxBack.h"

bool ordena_por_maxback(item a, item b){ return a.backValue > b.backValue; }

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

double inline ComputeCutMin(double **x, vector< item > s, vector < item > s_){
    
    double cutmin = 0;
    
    cout << "computing mincut value...\n" << endl;
    for(int i = 0; i < s.size(); i++){
        cutmin += CalculateMaxBackValue(x, s_, s[i].v);
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

vector< vector<int> > MaxBack(double **x,  int n){
    
    print_edges(x, n);
    
    vector< vector<int> > subtours;
    vector< pair<int,int> > arestas_s_0;
    vector< item > s_0;

    item v;
    v.v = 0;
    s_0.push_back(v);

    //cl = nos nao pertecentes a s_0;
    vector< item > cl = InitCandidateList(x,n);

    computeBackValues(cl, s_0, x);

    double cutmin, cutval;
    
    cutmin = cutval = ComputeCutMin(x, s_0, cl);

   while(s_0.size() < n){
        
        item v = cl.front();
        cl.erase(cl.begin());
        cout << v.backValue;
        s_0.push_back(v);
        //s_0 = vector<item>(cl.begin, cl.begin+n);
    }
    
   return subtours;
}
