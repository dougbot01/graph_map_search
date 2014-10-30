/*
 * (C) 2014 Douglas Sievers
 *
 * SearchBase.h
 */

#ifndef SEARCH_BASE_H
#define SEARCH_BASE_H

#include "Node.h"
#include "Graph.h"

using namespace std;

// Enum for search status
//

enum SearchStatus { FAILURE, SEARCHING, SUCCESS };
	
class SearchBase
{
public:

	// Constructor
	//

	SearchBase(Graph&);
	
	// public utility functions
	//

	virtual void search(const int, const int) = 0;
	void printSolution() const;

protected:
	nodePtr initialNodePtr;
	nodePtr goalNodePtr;
	Graph& graph;
};

#endif /* SEARCH_BASE_H */