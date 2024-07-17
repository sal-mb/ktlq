#ifndef NODE_INFO_H_
#define NODE_INFO_H_

#include <ilcplex/ilocplex.h>

/** A subclass of IloCplex::MIPCallbackI::NodeData that stores data related to the node **/
class NodeInfo : public IloCplex::MIPCallbackI::NodeData 
{

   //Depth of node at which this data is stored. 
   unsigned int const depth;

  public: 

      //cplex does not store node data for the root node. It is then necessary to explicitily maintain the NodeInfo object for the root of the B&C tree.
      //This object is a static object of the class NodeInfo.
      static NodeInfo* rootData;
      //call the method below before the B&C start
      static void initRootData();
      
      NodeInfo(unsigned int idepth); 

      unsigned int getDepth() const;
};

#endif
