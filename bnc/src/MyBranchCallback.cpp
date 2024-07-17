#include <ilcplex/ilocplex.h>	 
#include "NodeInfo.h" 
#include "MyBranchCallback.h"
#include <iostream>

//construtor da classe BrachCallBack
MyBranchCallback::MyBranchCallback(IloEnv env) : IloCplex::BranchCallbackI(env)  
{
}   

//retorna uma cópia do callback. Este método é uma exigência do cplex.
IloCplex::CallbackI* MyBranchCallback::duplicateCallback() const 
{ 
   return new (getEnv()) MyBranchCallback(getEnv()); 
}   

//codigo do callback que será executado pelo cplex. Esse BranchCallback não muda os branchings que o cplex iria fazer caso ele não existisse.
//O propósito deste callback é apenas colocar o NodeInfo em cada do nó da árvore. Isso é feito no momento do branching.
void MyBranchCallback::main() 
{
	// How many branches would CPLEX create? 
	IloInt const nbranch = getNbranches(); 

	if(nbranch > 0){ 
		// CPLEX would branch. Get the branches CPLEX would create 
		// and create exactly those branches. With each branch store 
		// its NodeInfo. 
		// Note that getNodeData() returns NULL for the root node. 
		NodeInfo *data = dynamic_cast<NodeInfo *>(getNodeData()); 
		unsigned int depth;
   
		if(!data){
		   	// se entrou aqui é porque o nó atual é a raiz. Cplex não guarda NodeInfo para a raiz, por isso o método acima retorna NULL.
			// O NodeInfo da raiz é um objeto estático da classe NodeInfo. Abaixo, verifica-se se objeto já foi construído e aponta-se o ponteiro data para ele.
			if(NodeInfo::rootData == NULL){
				NodeInfo::initRootData();
			}
			data = NodeInfo::rootData;
		}

		depth = data->getDepth();

		IloNumVarArray vars(getEnv());
		IloNumArray bounds(getEnv()); 
		IloCplex::BranchDirectionArray dirs(getEnv());   

		//cria as mesmas branches que o cplex criaria, mas coloca o NodeInfo.
		for(IloInt i = 0; i < nbranch; ++i){ 
			IloNum const est = getBranch(vars, bounds, dirs, i);
			makeBranch(vars, bounds, dirs, est, new NodeInfo(depth + 1U)); 
		} 

		dirs.end(); 
		bounds.end(); 
		vars.end(); 
   } 
   else{ 
		// CPLEX would not create any branch here. Prune the node. 
		prune(); 
   } 
}

