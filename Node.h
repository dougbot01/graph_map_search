/*
 * (C) 2014 Douglas Sievers
 *
 * Node.h
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


// Explicitly call out types we are using, instead of "using namespace"
// due to conflicts between boost and std smart pointer types
using std::string;
using std::vector;


// Forward declaration of class Edge, as well as typedefs
// A Node object has a vector of "weak pointers" to edges,
// that keeps track of all edges LEAVING the node.
class Edge;
typedef boost::shared_ptr<Edge> edgePtr;									//pointer to an Edge
typedef boost::weak_ptr<Edge> edgeWeakPtr;									//weak pointer to an Edge
typedef vector<edgeWeakPtr>::const_iterator edgeWeakPtrConstIterator;		//iterator for vector of weak pointers to edges



// ---------------------------------------------------------------------------------/
// The Node class defines a node within a graph data structure. It has links to		/
// its edges (to other nodes) as well as its parent and path cost, that are used	/
// in graph search algorithms.														/
// There are also latitude and longitude members for heuristic map type searches,	/
// with helper function "linearDistanceTo".											/
// ---------------------------------------------------------------------------------/

class Node
{
public:

	// Enum for node's status
	//
	enum ExploredStatus { UNEXPLORED, FRONTIER, EXPLORED };

	// Constructor and destructor
	//

	Node(const string&, const float, const float);
	~Node();

	// Setters and getters
	// Node ID cannot be changed
	//

	string getNodeID() const;
	
	void setStatus(const ExploredStatus);
	ExploredStatus getStatus() const;
	
	void setPathCost(const float);
	float getPathCost() const;
	
	void setHeuristic(const float);
	float getHeuristic() const;
	
	void setLatitude(const float);
	float getLatitude() const;
	
	void setLongitude(const float);
	float getLongitude() const;

	void setParentNode(boost::shared_ptr<Node>);
	boost::weak_ptr<Node> getParentNode() const;
	
	void setParentAction(edgeWeakPtr);
	edgeWeakPtr getParentAction() const;

	void setSearchState(const ExploredStatus, const float, boost::shared_ptr<Node>, edgeWeakPtr);
	
	// Additional public utility functions
	//

	void addEdge(edgePtr);
	float linearDistanceTo(boost::shared_ptr<Node>) const;
	void printEdges() const;
	void clearSearchState();


	// Iterators for the vector of edges are exposed
	// as part of Node's public interface using inlines.
	
	edgeWeakPtrConstIterator cbegin() { return leavingEdges.cbegin(); }
	edgeWeakPtrConstIterator cend() { return leavingEdges.cend(); }


private:
    string nodeID;
	ExploredStatus status;
	float pathCost;
	float heuristic;
	float latitude;
	float longitude;
	boost::weak_ptr<Node> parentNode;
	edgeWeakPtr parentAction;
	vector<edgeWeakPtr> leavingEdges;
};



// Typedefs for the Node class that are used in other classes (like Edge and Graph)
//

typedef boost::shared_ptr<Node> nodePtr;
typedef vector<nodePtr>::const_iterator nodeVecConstIterator;



// ---------------------------------------------------------------------------------/
// The NodeCompare___ classes define function objects that are passed				/
// to a priority queue or similar data structure for correct ordering				/
// of Node objects. This implementation sets the shortest path to					/
// be the Node popped first.														/
// ---------------------------------------------------------------------------------/

class NodeCompareCost {
public:
    bool operator()(const nodePtr& n1, const nodePtr& n2) const
    {
       if (n1->getPathCost() > n2->getPathCost())
		   return true;
       return false;
    }
};

class NodeCompareHeuristic {
public:
    bool operator()(const nodePtr& n1, const nodePtr& n2) const
    {
       if (n1->getHeuristic() > n2->getHeuristic())
		   return true;
       return false;
    }
};

#endif /* NODE_H */
