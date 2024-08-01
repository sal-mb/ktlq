#include "MaxBack.h"

bool ordena_por_maxback(item a, item b){ return a.backValue < b.backValue; }

void print_edges(double **x, int n){

    for(int i = 0; i < n;i++){
        int print = 0;

        while(print < i){
            cout << "_ - ";
            print++;
        }
        for(int j = i; j < n;j++){
            if(x[i][j] < EPSILON){
                x[i][j] = 0;
            }
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

    cout << "computing cutmin value...\n" << endl;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == true){
            cutmin += computeCutMinV(x, s, i);
        }
    }

    cout << "cutmin value: " << cutmin << endl;
    return cutmin;
}

double inline CalculateMaxBackValue(double **x, vector< bool > s, int v, int in){
    //b(v) = sum{x_uv}

    double b = 0;

        
    if(v < in){
        b += x[v][in];
    }else{
        b += x[in][v];
    }
    
    return b;
}

void computeBackValues(vector< bool > &s, vector< item > &backValues, int initial_node, double** x){
    cout << "computing maxBack values of s...\n" << endl;
    
    backValues.clear();

    for(int i = 0; i < s.size(); i++){
        if(s[i] == false){
            item v;
            v.v = i;
            v.backValue = CalculateMaxBackValue(x, s, i, initial_node);

            backValues.push_back(v);
        }
    }
    std::make_heap(backValues.begin(), backValues.end(), ordena_por_maxback);
}

void inline updateBackValues(vector< item > &backValues, int v, double** x){
    for(item &bv : backValues){
        if(bv.v > v){
            bv.backValue += x[v][bv.v];
        }else{
            bv.backValue += x[bv.v][v];
        }
    }
    std::make_heap(backValues.begin(), backValues.end(), ordena_por_maxback);
}

vector< int > boolToIntSolution(vector< bool > s){
    vector< int > s_int;

    for(int i = 0; i < s.size(); i++){
        if(s[i] == true){
            s_int.push_back(i);
        }
    }
    return s_int;
}

void inline setVerticesTrue(vector< bool > &s, vector< int > s_0){
    
    for(int v : s_0){
        s[v] = true;
    }
}

int inline getInitialNode(vector< bool > s){
    
    int i;
    for(i = 0; i < s.size(); i++){
        if(s[i] == false){
            return i;
        }
    }
    i = -1;
    return i;
}

vector< vector<int> > MaxBack(double **x,  int n){

    vector< vector<int> > subtours;
    vector< bool > s_in_subtours(n,false); // stores vertices from all subtours
    vector< bool > s_0(n);
    int initial_node = 0;

    //print_edges(x, n);

    while(initial_node != -1){
        
        vector< bool > s_0(n, false);
        s_0[initial_node] = true;

        vector< bool > s_min; 
        vector< item > backValues;
        double cutval, cutmin;
        int s_0_count = 1;

        cutmin = cutval = ComputeCutMin(x, s_0);
        cout << cutmin << endl; 

        computeBackValues(s_0, backValues, initial_node, x);
        
        while(s_0_count < n){
            item v = backValues[0];
            
            s_0[v.v] = true;
            s_0_count++;

            std::pop_heap(backValues.begin(), backValues.end(), ordena_por_maxback);
            backValues.pop_back();

            cutval = cutval + 2 - 2*v.backValue;

            updateBackValues(backValues, v.v, x);

            if(cutval < cutmin){
                cout << "entrou if: " << s_0_count << endl;
                cutmin = cutval;
                s_min = s_0;
            }
        }
        vector< int > s_min_int( boolToIntSolution(s_min) );
        
        if(s_min_int.size() == n){
            return {};
        }

        setVerticesTrue(s_in_subtours, s_min_int);
        subtours.push_back(s_min_int);

        for(int v : s_min_int){
            cout << " -> " << v;
        }

        // get new inital node for next iteration 
        initial_node = getInitialNode(s_in_subtours);
    }
    
    return subtours;
}
