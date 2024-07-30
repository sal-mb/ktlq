#include "MinCut.h"
#include "MaxBack.h"

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

int inline insertNodeOnA(vector< bool > &A, double** x){
    
    double max_weight = 0;
    double max_v = -1;
    for(int i = 0; i < A.size(); i++){
        if(A[i] == false){
            double weight = computeWeight(A,x,i);

            if(weight >= max_weight){
                max_weight = weight;
                max_v = i;
                cout << "max: " << max_weight << endl;
                cout << "v: " << max_v << endl;
            }
        }
    }

    return max_v;
}

extern vector< vector<int> > MinCut(double** x, int n){
    
    vector< bool > A(n,false);
    int A_count = 1;
    A[0] = true;

    print_edges(x, n);
    insertNodeOnA(A, x);
    
    int s,t;

    while(A_count < n){
        int v_to_insert = insertNodeOnA(A, x);

        if(A_count == n-1){
            t = v_to_insert;
        }else{
            s = v_to_insert;
        }

        cout << "v insert: " << v_to_insert << endl;
        A[v_to_insert] = true;

        cout << "count: " << A_count << endl;
        A_count++;

    }
    cout << "s: " << s << ", t: " << t << endl;

    return {};
}
