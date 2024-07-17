#ifndef MY_BRANCH_CALLBACK_H
#define MY_BRANCH_CALLBACK_H

#include <ilcplex/ilocplex.h>

/** Branch callback that keeps track of node depth. * The callback creates exactly the same branches as CPLEX would do. * Additionally, it uses the NodeData mechanism to store at each node * its depth in the branch and bound tree. */ 
class MyBranchCallback : public IloCplex::BranchCallbackI 
{
	public: // Public methods

	MyBranchCallback(IloEnv env);

	IloCplex::CallbackI *duplicateCallback() const;

	void main();
};

#endif
