/*
 * (C) 2014 Douglas Sievers
 *
 * AStarSearch.h
 */

#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include <boost/heap/binomial_heap.hpp>
#include "SearchBase.h"


using namespace std;

class AStarSearch : public SearchBase
{
public:

	// Constructor
	//

	AStarSearch(Graph&);
	
	// public utility functions
	//

	virtual void search(const int, const int);
	SearchStatus processNext();

private:
	boost::heap::binomial_heap<nodePtr, boost::heap::compare<NodeCompareHeuristic> > frontier;
};

#endif /* A_STAR_SEARCH_H */
