#ifndef SUBTOURS_H
#define SUBTOURS_H

#include <vector>
#include <iostream>
#include "hungarian.h"
#include <list>

std::vector<int> detecta_subtours(hungarian_problem_t *p);
void print_subtours(std::vector<std::vector<int>> *subtours);
bool ordena_por_tamanho(std::vector<int> a, std::vector<int> b);
void print_subtour(std::vector<int> *subtour);

#endif