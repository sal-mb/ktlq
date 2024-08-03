#include "MinCut.h"
#include "MaxBack.h"

bool orderByWeight(vertex a, vertex b){ return a.weight < b.weight; }

vector< int > initV(int n){

    vector< int > V;
    
    for(int i = 0; i < n; i++){
        V.push_back(i);
    }

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

cut getCut(vector< int > V, int s, int cut_cost){

    cut cut;
    cut.cut_cost = cut_cost;
    
    vector< int > v, v_;

    for(int i = 0; i < V.size(); i++){
        if(V[i] == s){
            v.push_back(i);
        }else{
            v_.push_back(i);
        }
    }
    cut.v = v;
    cut.v_ = v_;

    return cut;
}

st MinCutPhase(double **x, vector< int >V, int initial_node){
    
    vector< vertex > W;
    vector< int > V_;
    
    V_.push_back(initial_node);

    initWeights(V, W, x, initial_node);
    
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

double** cloneX(double** x, int n){

	double **x_edge = new double*[n];
 
	for (int i = 0; i < n; i++) {
		x_edge[i] = new double[n];
	}

	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			x_edge[i][j] = x[i][j];
		}
	}

    return x_edge;
}

void deleteX(double **x, int n){

    for(int i = 0; i < n; i++){
        delete x[i];
    }
    delete x;
}
void inline setVerticesTrue(vector< bool > &s, vector< int > v, vector< int > v_){
    
    for(int i : v){
        s[i] = true;
    }
    for(int i : v_){
        s[i] = true;
    }
}
/*
vector< vector<int> > getVertices(vector< int > V){
    
    vector< vector<int> > s_;
    vector< int > sub;
    
    int pos_s_ = 0;

    for(int i = 0; i < V.size(); i++){
        
        if(V[i] == i){
            sub.push_back(i);
        }else{
            vector< int > dummy;
            dummy.push_back(V[i]);

            for(int j = V[i]+1; j < V.size(); j++){
                if(V[i] == V[j]){
                    dummy.push_back(j);
                    V.erase(V.begin()+j);
                }
            }
            s_.push_back(dummy);
            for(auto o : dummy){
                cout << " -> " << o;
            }
        }
    }
    
    return std::move(s_);
}*/

extern vector< vector<int> > MinCut(double** x, int n){
    
    vector< vector<int> > subtours;

    vector< int > V = initV(n);
    int initial_node = 0;

    cut min_cut;
    cut current_cut;
    
    min_cut.cut_cost = 9999999;

    int Vcount = n;
    st st;
    
    print_edges(x,n);
 //   double** x_ = cloneX(x,n);

    while(Vcount > 1){
        
        st = MinCutPhase(x,V,initial_node);

        if(st.cotp < 2){
            cut s = getCut(V, st.s, st.cotp);
            for(auto x : s.v){
                cout << " -> " << x;
            }
            cout << endl;
            for(auto x : s.v_){

                cout << " -> " << x;
            }
            cout << endl;
        }

        V[st.t] = V[st.s];

        attX(x,n, st.s, st.t);
        
        Vcount--;
    }
    

    //deleteX(x_, n);

    for(auto s : subtours){
        for(auto v : s){
            cout << " -> " << v;
        }
        cout << endl;
    }

    print_edges(x,n);
    getchar();

    return subtours;

}
