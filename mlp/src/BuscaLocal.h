#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Subsequencia.h"
#include "Solucao.h"
#include "Data.h"
#include <vector>


void BuscaLocal(Solucao &s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

bool BISwap(Solucao &s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

bool BI2_Opt(Solucao &s, Data *data, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

bool BIOrOpt(Solucao &s, Data *data, int option, std::vector<std::vector<Subsequencia>> &subSeqMatrix);

#endif