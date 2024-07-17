#include "MyLazyCallback.h"

/********************************************** Class' Constructor **********************************************/
MyLazyCallback::MyLazyCallback(IloEnv env, const IloArray<IloBoolVarArray>& x_ref, int nodes) : IloCplex::LazyConstraintCallbackI(env), x(x_ref), x_vars(env), n(nodes)
{
	/********** Filling x_vars **********/
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++){
			x_vars.add(x[i][j]);
		}
	}
	/************************************/
} 
/*****************************************************************************************************************/

/************************** Return a callback copy. This method is a CPLEX requirement ***************************/
IloCplex::CallbackI* MyLazyCallback::duplicateCallback() const 
{ 
   return new (getEnv()) MyLazyCallback(getEnv(), x, n); 
}
/*****************************************************************************************************************/

/************************************ Callback's code that is runned by CPLEX ************************************/
void MyLazyCallback::main() 
{	
	/********** Getting the relaxed variables values **********/
	IloNumArray x_vals(getEnv(), (0.5*(n)*(n-1)));
	getValues(x_vals, x_vars);
	/**********************************************************/
   
	vector <vector<int> > cutSetPool;
	vector<IloConstraint> cons; 

	double **x_edge = new double*[n];
 
	for (int i = 0; i < n; i++) {
		x_edge[i] = new double[n];
	}

	int l = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			x_edge[i][j] = x_vals[l++];
		}
	}
	
	cutSetPool = MaxBack(x_edge, n);

	/***************** Creating the constraints ***************/
	for (int c = 0; c < cutSetPool.size(); c++) {
		IloExpr p(getEnv());
		for(int i = 0; i < cutSetPool[c].size(); i++){
			for(int j = 0; j < cutSetPool[c].size(); j++){
				if(cutSetPool[c][i] < cutSetPool[c][j]){
					p += x[cutSetPool[c][i]][cutSetPool[c][j]];
				}
			}
		}
		int RHS = cutSetPool[c].size();
		cons.push_back(p <= RHS - 1);
	}
	/**********************************************************/

	/*********** Adding the constraints to the model **********/
	for(int i = 0; i < cons.size(); i++){
		add(cons.at(i)).end();
	}
	/**********************************************************/

	/******************* Cleaning the memory ******************/
	for (int i = 0; i < n; i++) {
		delete[] x_edge[i];
	}
	delete[] x_edge;
	/**********************************************************/
}
/*****************************************************************************************************************/