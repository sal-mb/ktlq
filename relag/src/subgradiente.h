#include <numeric>
#include <vector>
#include "Kruskal.h"
#include "data.h"

vector<double> subgradiente(double heuristic_ub, Data *data, vvi cost_matrix);

vector<int> calcula_graus(vii msp, int n);

inline double tamanho_do_passo(double upper_bound, double w, vector<int> graus);

inline void altera_penalizadores(vector<double> &lmb, double u, vector<int> graus);