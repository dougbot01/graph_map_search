/*
 * (C) 2014 Douglas Sievers
 *
 * UniformCostSearch.cpp
 */

#include <iostream>
#include "UniformCostSearch.h"

UniformCostSearch::UniformCostSearch(Graph& g) : SearchBase(g)
{
	// empty constructor
}

void UniformCostSearch::search(const int init, const int goal)
{
	// put initial node in the frontier, with cost:0 and status:frontier
	initialNodePtr = graph.nodeAt(init);
	initialNodePtr->setStatus(Node::FRONTIER);
	initialNodePtr->setPathCost(0.0f);
	frontier.push(initialNodePtr);

	// set the goal node
	goalNodePtr = graph.nodeAt(goal);

	// output a message of what we're searching for
	cout << "Searching for route from " << initialNodePtr->getNodeID() << " to " << goalNodePtr->getNodeID();

	// this loop keeps searching until a solution is found
	int nodeCount = 0;
	SearchStatus status = processNext();

	while( status == SearchStatus::SEARCHING )
	{
		++nodeCount;
		cout << " .";
		status = processNext();
	}

	// If FAIL, output a message
	if( status == SearchStatus::FAILURE )
	{
		cout << "\n\nNo solution found.\n\n";
	}
	// If SUCCESS, output the solution
	else if( status == SearchStatus::SUCCESS )
	{
		cout << "\n\nSearch Efficiency\n-----------------\nExpanded " << nodeCount << " nodes\n";

		// print out the solution if found
		printSolution();
	}

	// once the search has completed we clear the graph state 
	// (each node cost, state, parent, action) so we can search again
	graph.clearSearchState();
}

SearchStatus UniformCostSearch::processNext()
{
	// if the frontier is empty and goal is not found, return failure
	if (frontier.empty())
		return SearchStatus::FAILURE;

	// take a node from frontier, and set to explored
	nodePtr currentNodePtr = frontier.top();
	currentNodePtr->setStatus(Node::EXPLORED);
	frontier.pop();
	
	// check if current node is the goal
	if (currentNodePtr.get() == goalNodePtr.get())
	{
		// there appears to be a bug in the heap's "clear" method that doesn't pop the top node
		// if the pop doesn't happen, then the shared_ptr is never released and memory gets leaked
		// to solve this, pop elements until the queue is empty before returning
		while(!frontier.empty())
		{
			frontier.pop();
		}
		return SearchStatus::SUCCESS;
	}

	// if the current node is not the goal, then find it's children and add them to the frontier
	// we only add nodes not already expanded or in the frontier (graph search), and update nodes
	// if shorter paths are found
	else
	{
		for( edgeWeakPtrConstIterator edge = currentNodePtr->cbegin(); edge != currentNodePtr->cend(); ++edge)
		{
			boost::shared_ptr<Edge> ptrSharedEdge(*edge);
			nodePtr childNodePtr = ptrSharedEdge->getHeadNode();
			float newNodeCost = currentNodePtr->getPathCost() + ptrSharedEdge->getEdgeCost();
			
			// if the generated child node is unexplored (not in the frontier, and not explored),
			// update the child node's state and put it in the frontier
			if (childNodePtr->getStatus() == Node::UNEXPLORED)
			{
				// set status to frontier, update cost, set parent node and action, then add to frontier
				childNodePtr->setSearchState(Node::FRONTIER, newNodeCost, currentNodePtr, *edge);
				frontier.push(childNodePtr);
			}

			// if the generated child node is in the frontier, and we found a SHORTER path, then we have a
			// small issue. If you update the priority through the node handle, the queue is corrupted by
			// the priority shift.
			// Instead we must find the node in the priority queue, using the iterator, and then ERASE it.
			// Then we can update the child node's state and put it BACK in the frontier
			else if (childNodePtr->getStatus() == Node::FRONTIER && newNodeCost < childNodePtr->getPathCost())
			{
				// This ugly section is to create an iterator for the frontier (boost heap), iterate through the heap,
				// find the correct child node, and erase it from the frontier
				boost::heap::binomial_heap<nodePtr, boost::heap::compare<NodeCompareCost> >::iterator it = frontier.begin();
				for(it = frontier.begin(); it != frontier.end(); ++it)
				{
					if ( (*it).get() == currentNodePtr.get() )
					{
						boost::heap::binomial_heap<nodePtr, boost::heap::compare<NodeCompareCost> >::handle_type t = frontier.s_handle_from_iterator(it);
						frontier.erase(t);
						break;
					}
				}
				// Then update the node and push it back, in the correct order.
				childNodePtr->setSearchState(Node::FRONTIER, newNodeCost, currentNodePtr, *edge);
				frontier.push(childNodePtr);
			}

		}

		// Return that we are still searching
		return SearchStatus::SEARCHING;
	}
}

