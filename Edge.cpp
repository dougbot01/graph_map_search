/*
 * (C) 2014 Douglas Sievers
 *
 * Edge.cpp
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "Edge.h"
#include "Node.h"

using namespace std;

Edge::Edge(nodePtr tail, nodePtr head, const float cost, const string& id) : ptrTailNode(tail), ptrHeadNode(head), edgeID(id)
{
	setEdgeCost(cost);
}

Edge::~Edge()
{
	// This is only for debug purposes
	//cout << "Destroy edge from " << ptrTailNode->getNodeID() << " to " << ptrHeadNode->getNodeID() << endl;
	//system("PAUSE");
}

string Edge::getEdgeID() const
{
	return edgeID;
}
	
float Edge::getEdgeCost() const
{
	return edgeCost;
}

nodePtr Edge::getHeadNode() const
{
	return ptrHeadNode;
}

nodePtr Edge::getTailNode() const
{
	return ptrTailNode;
}

string Edge::toString() const
{
	stringstream a;
	a << "Edge : " << ptrTailNode->getNodeID() << " -> " << ptrHeadNode->getNodeID();
	a << " : " << getEdgeCost() << "km via " << getEdgeID();
	return a.str();
}

void Edge::setEdgeCost(const float c)
{
	if (c > 0.0f)
	{
		edgeCost = c;
	}
	else
	{
		edgeCost = 1.0f;
	}
}
