/*
 * (C) 2014 Douglas Sievers
 *
 * Node.cpp
 */

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include "Node.h"
#include "Edge.h"

using namespace std;

Node::Node(const string& id, const float latitude, const float longitude) : nodeID(id)
{
	setStatus(UNEXPLORED);
	setPathCost(0.0f);
	setHeuristic(0.0f);
	setLatitude(latitude);
	setLongitude(longitude);
}

// Because pointers to other objects, namely edges and the parent node, are
// managed by weak pointers, there is no requirement to explicitly delete
// them in the destructor.
Node::~Node()
{
	// This is only for debug purposes
	//cout << "Destroy node " << getNodeID() << endl;
	//system("PAUSE");
}

string Node::getNodeID() const
{
	return nodeID;
}

void Node::setStatus(const Node::ExploredStatus s)
{
	status = s;
}

Node::ExploredStatus Node::getStatus() const
{
	return status;
}

void Node::setPathCost(const float c)
{
	if (c >= 0.0f)
		pathCost = c;
	else
		pathCost = 0.0f;
}

float Node::getPathCost() const
{
	return pathCost;
}

void Node::setHeuristic(const float h)
{
	if (h >= 0.0f)
		heuristic = h;
	else
		heuristic = 0.0f;
}

float Node::getHeuristic() const
{
	return heuristic;
}

void Node::setLatitude(const float lat)
{
	if ((lat < -90.0f) || (lat > 90.0f))
	{
		throw out_of_range("Latitude must be between -90 and 90\n");
	}
	else
	{
		latitude = lat;
	}
}

float Node::getLatitude() const
{
	return latitude;
}

void Node::setLongitude(const float lon)
{
	if ((lon < -180.0f) || (lon > 180.0f))
	{
		throw out_of_range("Longitude must be between -180 and 180\n");
	}
	else
	{
		longitude = lon;
	}
}

float Node::getLongitude() const
{
	return longitude;
}

void Node::setParentNode(boost::shared_ptr<Node> p)
{
	parentNode = p;
}

boost::weak_ptr<Node> Node::getParentNode() const
{
	return parentNode;
}

void Node::setParentAction(edgeWeakPtr e)
{
	parentAction = e;
}

edgeWeakPtr Node::getParentAction() const
{
	return parentAction;
}

void Node::setSearchState(const ExploredStatus status, const float cost, boost::shared_ptr<Node> parent, edgeWeakPtr action)
{
	// convenience method to set multiple values in a single call

	setStatus(status);
	setPathCost(cost);
	setParentNode(parent);
	setParentAction(action);
}

void Node::addEdge(edgePtr edge)
{
	leavingEdges.push_back(edge);
}

float Node::linearDistanceTo(nodePtr b) const
{
	// This calculates the distance in km between two latitude/longitude coordinates
	double toRad = 0.01745329251994329;
	double dLat = (getLatitude() - b->getLatitude())*toRad;
	double dLon = (getLongitude() - b->getLongitude())*toRad;
	double a = sin(dLat/2.0) * sin(dLat/2.0) +
        sin(dLon/2.0) * sin(dLon/2.0) * cos(toRad*b->getLatitude()) * cos(toRad*getLatitude()); 
	double c = 2.0 * atan2(sqrt(a), sqrt(1-a)); 
	return float(6371.0f * c);
}

void Node::printEdges() const
{
	// iterate over leaving edges, and call each one's toString() method

	for (edgeWeakPtrConstIterator it = leavingEdges.cbegin(); it != leavingEdges.cend(); ++it)
	{
		boost::shared_ptr<Edge> ptrSharedEdge(*it);
		cout << "   " << ptrSharedEdge->toString() << endl;
	}
}

void Node::clearSearchState()
{
	// set all values back to initial states
	setStatus(UNEXPLORED);
	setPathCost(0.0f);
	setHeuristic(0.0f);

	// clear object pointers to point to nothing
	parentNode.reset();
	parentAction.reset();
}