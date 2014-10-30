/*
 * (C) 2014 Douglas Sievers
 *
 * UniformCostSearch.h
 */

#ifndef UNIFORM_COST_SEARCH_H
#define UNIFORM_COST_SEARCH_H

#include <boost/heap/binomial_heap.hpp>
#include "SearchBase.h"


using namespace std;

class UniformCostSearch : public SearchBase
{
public:

	// Constructor
	//

	UniformCostSearch(Graph&);
	
	// public utility functions
	//

	virtual void search(const int, const int);
	SearchStatus processNext();

private:
	boost::heap::binomial_heap<nodePtr, boost::heap::compare<NodeCompareCost> > frontier;
};

#endif /* UNIFORM_COST_SEARCH_H */