#include "MinCut.h"
#include "MaxBack.h"

bool orderByWeight(vertex a, vertex b){ return a.weight < b.weight; }

bool in_vector(vector< int > v, int i){ return std::find(v.begin(), v.end(), i); }

double inline computeWeight(vector< bool > &A, double** x, int v){

    double weight = 0;

    for(int i = 0; i < A.size(); i++){

        if(A[i] == true){
            if(v > i){
                weight += x[i][v];
            }else{
                weight += x[v][i];
            }        
        }
    }

    return weight;
}

/*
int inline insertNodeOnA(vector< bool > &A, double** x){

    double max_weight = 0;
    double max_v = -1;
    for(int i = 0; i < A.size(); i++){
        if(A[i] == false){
            double weight = computeWeight(A,x,i);
            if(weight >= max_weight){
                max_weight = weight;
                max_v = i;
            }
        }
    }

    cout << "max_weight: " << max_weight << endl;
    return max_v;
}
*/

void inline initWeights(vector< bool > &A, vector< vertex > &V_, vector< int > merged_vertices, double** x){

    double max_weight = 0;
    double max_v = -1;

    for(int i = 1; i < A.size(); i++){
        
        vertex v;
        
        if(find(merged_vertices.begin(), merged_vertices.end()))
        v.v = i;
        v.weight = computeWeight(A,x,i);

        V_.push_back(v);

    }

    make_heap(V_.begin(), V_.end(), orderByWeight);
}

void inline updateWeights(vector< vertex > &V_, double**x, int v){

    for(vertex &w : V_){
        if(w.v > v){

            w.weight += x[v][w.v];
        }else{

            w.weight += x[w.v][v];
        }
    }
    make_heap(V_.begin(), V_.end(), orderByWeight);
}

void print_A(vector< bool > A){

    for(int i = 0; i < A.size(); i++){

        if(A[i] == true){
            cout << i << " -> ";
        }
    }
    cout << endl;
}

pair<int,int> MinCutPhase(double** x, int n){

    vector< bool > A(n,false);
    vector< vertex > V_;

    int A_count = 1;
    A[0] = true;

    print_edges(x, n);
    initWeights(A, V_, x);


    int s = 0, t = 0;
    double cut_of_the_pase = 0;

    while(A_count < n){

        vertex v_to_insert = V_[0];

        if(A_count == n-1){
            t = v_to_insert.v;
            cut_of_the_pase = v_to_insert.weight;
        }else{
            s = v_to_insert.v;
        }
        pop_heap(V_.begin(), V_.end(), orderByWeight);
        V_.pop_back();

        //        cout << "v insert: " << v_to_insert.v << ", w: " << v_to_insert.weight << endl;
        A[v_to_insert.v] = true;

        updateWeights(V_, x, v_to_insert.v);


        A_count++;

    }

    return make_pair(s,t);
}


extern vector< vector<int> > MinCut(double** x, int n){

    pair<int,int> st = MinCutPhase(x,n);
    
    vector< int > merged_vertices;
    cout << "s: " << st.first << ", t: " << st.second << endl;

    return {};
}
