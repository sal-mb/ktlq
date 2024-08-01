#include "MinCut.h"
#include "MaxBack.h"

bool orderByWeight(vertex a, vertex b){ return a.weight < b.weight; }

vector< int > initV(int n, int s, int t){

    vector< int > V;
    
    for(int i = 0; i < n; i++){
        V.push_back(i);
    }

    V[t] = V[s];

    return V;
    
}

void attX(double **x, int n, int s, int t){
    
    if(s == t){
        return;
    }

    for(int i = 0; i < s-1; i++){

        x[i][s] += x[i][t];
    }

    for(int i = s+1; i < t; i++){

        x[s][i] += x[i][t];
    }

    for(int i = s+1; i < n; i++){

        x[s][i] += x[t][i];
    }

    for(int i = 0; i < s; i++){
        x[i][s] += x[i][t];
    }


    x[s][s] = 0;
    x[t][t] = 0;

}

/*
double computeWeight(vector< int > V, int v, double **x){

    double w = 0;

    for(int i = 1; i < V.size(); i++){

        if(V[i] > v){
            w += x[v][V[i]];
        }else{
            w += x[V[i]][v];
        }
    }
}*/

void initWeights(vector< int > V, vector< vertex > &W, double **x){
    
    for(int i = 1 ; i < V.size(); i++){

        vertex v;
        
        
        v.v = V[i];
        v.weight = x[0][V[i]];
        
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

st MinCutPhase(double **x, vector< int >V){
    
    vector< vertex > W;
    vector< int > V_ = {0};

    initWeights(V, W, x);
    
    int Vcount = 1;

    double cut_of_the_phase;
    int s = 0, t = 0;
    
    int n = W.size()+1;

    while(Vcount < n){
        
        vertex v_to_insert = W[0];

        if(Vcount == n-1){
            t = v_to_insert.v;
            cut_of_the_phase = v_to_insert.weight;
        }else{
            s = v_to_insert.v;
        }
        pop_heap(W.begin(), W.end(), orderByWeight);
        W.pop_back();
        
        //cout << "v: " << v_to_insert.v << ", w: " << v_to_insert.weight << endl;
        V_.push_back(v_to_insert.v);
        /*
        for(auto v : V_){
            cout << " -> " << v;
        }*/
        updateWeights(W, x, v_to_insert.v);
        
        Vcount++;
    }
    
    st st;

    if(s > t){
        st.t = s;
        st.s = t;
        st.cotp = cut_of_the_phase;
    }else{
        st.t = t;
        st.s = s;
        st.cotp = cut_of_the_phase;
    }

    return st;
}

extern vector< vector<int> > MinCut(double** x, int n){
    
    vector< int > V = initV(n, 0, 0);
    
    st st;
    st = MinCutPhase(x, V);

    cout << "s: " << st.s << ", t: " << st.t << ", cotp: " << st.cotp << endl;

    print_edges(x,n);
    getchar();
    attX(x,n,st.s, st.t);
    
    print_edges(x,n);
    
    getchar();
    V = initV(n, st.s, st.t);

    st = MinCutPhase(x, V);

    cout << "s: " << st.s << ", t: " << st.t << ", cotp: " << st.cotp << endl;
    getchar();
    return {};
}
