/*
 * (C) 2014 Douglas Sievers
 *
 * SearchBase.cpp
 */

#include <iostream>
#include <stack>
#include "SearchBase.h"

SearchBase::SearchBase(Graph& g) : graph(g)
{
	// empty constructor
}

void SearchBase::printSolution() const
{
	//build out the solution...
	// maybe this is a do...while
	//

	stack<nodePtr> solnNodePtrStack;
	nodePtr currentNodePtr = goalNodePtr;
	solnNodePtrStack.push(goalNodePtr);

	while (! (currentNodePtr->getParentNode().expired()) )
	{
		nodePtr nextNode = currentNodePtr->getParentNode().lock();
		solnNodePtrStack.push(nextNode);
		currentNodePtr = nextNode;
	};

	cout << "\nResult\n------\n";

	while (solnNodePtrStack.top().get() != goalNodePtr.get())
	{
		currentNodePtr = solnNodePtrStack.top();
		cout << "From " << currentNodePtr->getNodeID();
		solnNodePtrStack.pop();
		
		currentNodePtr = solnNodePtrStack.top();
		edgePtr solnEdge = currentNodePtr->getParentAction().lock();
		cout << ", take route " << solnEdge->getEdgeID()
			<< " for " << solnEdge->getEdgeCost() << "km to "
			<< currentNodePtr->getNodeID() << endl;	
	} 
	
	cout << "\nTotal distance is " << goalNodePtr->getPathCost() << "km\n\n";
}
