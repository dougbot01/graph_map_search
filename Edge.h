/*
 * (C) 2014 Douglas Sievers
 *
 * Edge.h
 */

#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


// Explicitly call out types we are using, instead of "using namespace"
// due to conflicts between boost and std smart pointer types
using std::string;
using std::vector;


// Forward declaration of class Node, as well as typedefs
// An Edge is like an arrow, and contains a pointer to the
// Node object at its head and tail both, as shared pointers.
class Node;
typedef boost::shared_ptr<Node> nodePtr;



// ---------------------------------------------------------------------------------/
// The Edge class defines a link between to Nodes in a graph data structure.		/
// The edges are best thought of as arrows in a directed graph structure, and		/
// contains a shared pointer to the head and tail.									/
// There is also a cost defined for each edge, which can be thought of as a			/
// distance in map type searches.													/
// ---------------------------------------------------------------------------------/

class Edge
{
public:

	// Constructor and destructor
	//

    Edge(nodePtr, nodePtr, const float, const string&);
	~Edge();

	// Setters and getters
	// Data members cannot be changed after initialization
	//

	string getEdgeID() const;
	float getEdgeCost() const;
	nodePtr getHeadNode() const;
	nodePtr getTailNode() const;

	//  public utility functions
	//

	string toString() const;
	
private:
    string edgeID;
	float edgeCost;
	nodePtr ptrTailNode;
	nodePtr ptrHeadNode;

	// private utility functions
	//

	void setEdgeCost(const float);
};


#endif /* EDGE_H */