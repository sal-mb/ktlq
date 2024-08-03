#include "MinCut.h"
#include "MaxBack.h"
#include <algorithm>
#include <cassert>

bool orderByWeight(vertex a, vertex b){ return a.weight < b.weight; }

vector< int > initV(int n){

    vector< int > V;

    for(int i = 0; i < n; i++){
        V.push_back(i);
    }

    return V;

}

void attX(double **x, int n, int s,int t){

    if(s > t){
        int aux = s;
        s = t;
        t = aux;
    }

    for(int i = 0; i < s; i++){

        x[i][s] += x[i][t];
    }

    for(int i = t; i < n; i++){

        x[s][i] += x[t][i];
    }

    for(int i = s; i <= t; i++){
        x[s][i] += x[i][t];
    }

    x[s][s] = 0;
    x[t][t] = 0;
    x[s][t] = 0;

}

void initWeights(vector< int > V, vector< vertex > &W, double **x, int in){

    for(int i = 1 ; i < V.size(); i++){

        vertex v;


        v.v = V[i];
        if(in > V[i]){
            v.weight = x[V[i]][in];
        }else{
            v.weight = x[in][V[i]];
        }

        // se o v no vertor for menor q o i, significa q temos um v merged
        // portanto temos que somar o peso no v merged correto

        if(V[i] == i){
            W.push_back(v);
        }
    }

    make_heap(W.begin(), W.end(), orderByWeight);
}

void updateWeights(vector< vertex > &W, double** x, int vi){

    for(vertex &w : W){

        if(w.v > vi){

            w.weight += x[vi][w.v];
        }else{

            w.weight += x[w.v][vi];
        }

    }

    make_heap(W.begin(), W.end(), orderByWeight);
}

void attV(vector< int > &V, int s, int t){

    if(s > t){
        int aux = s;
        s = t;
        t = aux;
    }
    int t_ = V[t];

    for(int i = s+1; i < V.size(); i++){
        if(V[i] == t_){
            V[i] = V[s];
        }
    }
}

st MinCutPhase(double **x, vector< int >V, int initial_node){

    vector< vertex > W;
    vector< int > V_;

    V_.push_back(initial_node);

    initWeights(V, W, x, initial_node);

    int Vcount = 1;

    st st;

    int n = W.size()+1;

    while(Vcount < n){

        vertex v_to_insert = W[0];

        if(Vcount == n-1){
            st.t = v_to_insert.v;
            st.cut_of_the_phase = v_to_insert.weight;
        }else{
            st.s = v_to_insert.v;
        }
        pop_heap(W.begin(), W.end(), orderByWeight);
        W.pop_back();

        V_.push_back(v_to_insert.v);
        updateWeights(W, x, v_to_insert.v);

        Vcount++;
    }

    return st;
}

cut getCut(vector< int > V, int t, int cut_cost){

    cut cut;
    cut.cut_cost = cut_cost;

    vector< int > v, v_;

    for(int i = 0; i < V.size(); i++){
        if(V[i] == t){
            v.push_back(i);
        }else{
            v_.push_back(i);
        }
    }
    cut.v = v;
    cut.v_ = v_;

    return cut;
}

extern vector< vector<int> > MinCut(double** x, int n){
    fiX(x,n);
    cout << " min cut " << endl;
    vector< vector<int> > subtours;
    vector< int > V = initV(n);
    vector< int > last_subtour;

    int initial_node = 0;

    int Vcount = n;
    st st;

    while(Vcount > 1){

        st = MinCutPhase(x,V,initial_node);

        if(st.cotp < 2 - EPSILON){

            cut s = getCut(V, st.t, st.cotp);

            subtours.push_back(s.v);
            last_subtour = std::move(s.v_);
        }

        attV(V, st.s, st.t);
        attX(x,n, st.s, st.t);

        Vcount--;
    }

    if(!subtours.empty()){
        subtours.push_back(last_subtour);
    }

    return subtours;
}
