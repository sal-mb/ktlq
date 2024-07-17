#include "NodeInfo.h"

//metodos da classe DepthData.
//Um objeto desta classe é associado a cada nó do B&C duranto o branching. Esse objeto é recuperado no cut callback.
NodeInfo::NodeInfo(unsigned  int depth) : depth(depth)
{

} 

void NodeInfo::initRootData()
{
   rootData = new NodeInfo(0);
}

unsigned int NodeInfo::getDepth() const 
{ 
   return this->depth; 
}

//ponteiro estático para o objeto NodeInfo que contém os dados da raiz
NodeInfo* NodeInfo::rootData = NULL;
