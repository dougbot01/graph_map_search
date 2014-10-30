/*
 * (C) 2014 Douglas Sievers
 *
 * BestFirstSearch.h
 */

#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include <boost/heap/binomial_heap.hpp>
#include "SearchBase.h"


using namespace std;

class BestFirstSearch : public SearchBase
{
public:

	// Constructor
	//

	BestFirstSearch(Graph&);
	
	// public utility functions
	//

	virtual void search(const int, const int);
	SearchStatus processNext();

private:
	boost::heap::binomial_heap<nodePtr, boost::heap::compare<NodeCompareHeuristic> > frontier;
};

#endif /* BEST_FIRST_SEARCH_H */