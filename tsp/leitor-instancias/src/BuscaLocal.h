#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Solucao.h"
#include "Data.h"


void BuscaLocal(Solucao *s, Data *data);

bool BISwap(Solucao *s, Data *data);

bool BI2_Opt(Solucao *s, Data *data);

bool BIOrOpt(Solucao *s, Data *data, int option);

#endif