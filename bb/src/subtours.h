#include <vector>
#include "hungarian.h"
#include "data.h"


std::vector<std::vector<int>> detecta_subtours(hungarian_problem_t *p);
void print_subtours(std::vector<std::vector<int>> *subtours);