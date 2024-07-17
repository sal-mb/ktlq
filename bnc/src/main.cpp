#include "dataFunction.h"
#include "auxFunctions.h"
#include "separation.h"
#include "MyLazyCallback.h"
#include "MyCutCallback.h"
#include "MyBranchCallback.h"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>

void STSP_Solve(Data *data, string instanceName, double ub)
{   
    IloEnv env;
    IloModel model(env);

    env.setName("Branch and Cut");
    model.setName("Symmetrical Traveling Salesman Problem");

    int dimension = data->getDimension();

    /********** Creating variable x for each edge **********/
    IloArray <IloBoolVarArray> x(env, dimension);

    for (int i = 0; i < dimension; i++) {
		IloBoolVarArray array(env, dimension);
		x[i] = array;
	}
    /*******************************************************/

    /*********** Adding x variables to the model ***********/
    char var[100];
    for (int i = 0; i < dimension; i++){
        for (int j = i + 1; j < dimension; j++){
            sprintf(var, "X(%d,%d)", i, j);
			x[i][j].setName(var);
			model.add(x[i][j]);
        }
    }
    /******************************************************/
    
    /**************** Objective Function ******************/
    IloExpr obj(env);
    for (int i = 0; i < dimension; i++) {	
		for (int j = i + 1; j < dimension; j++) {
			obj += data->getDistance(i, j)*x[i][j];
		}
	}
    model.add(IloMinimize(env, obj));
    /******************************************************/
    
    /******************** Constraints *********************/
    IloRange r;
    char name[100];

    for (int i = 0; i < dimension; i++){
        IloExpr sumX(env);
        for (int j = 0; j < dimension; j++){
            if (j < i) {
				sumX += x[j][i];
			}
            if (i < j){
                sumX += x[i][j];
            }
        }
        r = (sumX == 2);
        sprintf(name, "c_%d", i);
		r.setName(name);
		model.add(r);
    }
    /******************************************************/

    /****************** Solve the model *******************/
    IloCplex STSP(model);
    STSP.setParam(IloCplex::TiLim, 2*60*60);
    STSP.setParam(IloCplex::Threads, 1);
    STSP.setParam(IloCplex::Param::MIP::Tolerances::MIPGap, 1e-08);
    STSP.setParam(IloCplex::CutUp, ub);
    //STSP.exportModel("stsp.lp");

    double timeBefore, timeAfter;

    const IloArray<IloBoolVarArray>& x_ref = x;

    /********** Creating Branch Callback Object ***********/
    MyBranchCallback* branchCbk = new (env) MyBranchCallback(env);
    STSP.use(branchCbk);
    /******************************************************/

    /************ Creating Cut Callback Object ************/
    MyCutCallback* cutCbk = new (env) MyCutCallback(env, x_ref, dimension); 
	STSP.use(cutCbk);
    /******************************************************/

    /************ Creating Lazy Callback Object ***********/
    MyLazyCallback* lazyCbk = new (env) MyLazyCallback(env, x_ref, dimension);
    STSP.use(lazyCbk);
    /******************************************************/

    try{ 
	    timeBefore = STSP.getTime();
	    STSP.solve();
	    timeAfter = STSP.getTime();
    }
    catch(IloException& e){
        std::cout << e;
    }

    printResults(STSP, instanceName, timeAfter-timeBefore);
	printSolution(STSP, x, dimension);
	//printResultsToFile(STSP, instanceName, timeAfter-timeBefore);
    /******************************************************/

    /**************** Cleaning the memory *****************/
    delete branchCbk;
    delete cutCbk;
    delete lazyCbk;
    env.end();
    /******************************************************/
}

int main(int argc, char** argv)
{
    double ub = numeric_limits<double>::max();

    if(argc < 2){
        printf("Correct command: ./bc data/instance\n");
        return 0;
    }
    else if(argc > 2){
        ub = stod(argv[2]);
    }

    Data * data = new Data(argc, argv[1]);
    data->readData();

    string instanceName = getInstanceName(argv);
    STSP_Solve(data, instanceName, ub);

    /*************** Cleaning the memory ***************/
    delete data;
    /***************************************************/

    return 0;
}