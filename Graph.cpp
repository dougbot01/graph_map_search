/*
 * (C) 2014 Douglas Sievers
 *
 * Graph.cpp
 */

#include <exception>
#include <fstream>
#include <iomanip>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "Graph.h"

nodePtr Graph::findNode(const string& nodeName) const
{
	// this function simply iterates through the list of nodes
	// and returns a pointer to it if it exists, or an empty 
	// shared_ptr if not found

	nodeVecConstIterator it = nodeList.cbegin();

	while(it!=nodeList.cend())
	{
		if ( (*it)->getNodeID() == nodeName )
		{
			return (*it);
		}
		++it;
	}

	return boost::shared_ptr<Node>();
}

nodePtr Graph::nodeAt(const int index) const
{
	// returns a pointer to the node at a given index in the list
	// best used when selecting nodes along with the printNodeList() function

	return nodeList.at(index);
}

void Graph::readFile(const string& fileName)
{
	// this function takes a string for the file name as input, and attempts to parse
	// the file to create a graph structure
	// 
	// The file structure is text format. First is a list of nodes, a blank line, 
	//		a list of edges, then another blank line.
	//
	//		Node format : nodeName,latitude,longitude (string, float, float)
	//		Edge format : tailNodeName,headNodeName,edge distance/cost,edge name (string, string, float, string)
	//
	// Node names can include commas if the whole string is enclosed in quotation marks.
	// Many file format checks are made, and errors thrown if found, which will cause program termination

	ifstream inputFile;
	string fileString;

	// Attempt to open the file, and throw an exception if cannot open
	inputFile.open(fileName, ios::in);
	if(!inputFile)
	{
		throw runtime_error("Could not open the file.");
	}
	
	// In the first section, read an initial node, and loop until a blank line (length 0) is found
	
	getline(inputFile, fileString);
	while (fileString.length() > 0)
	{
		addNode(fileString);
		getline(inputFile, fileString);
	}

	// In the second section, read an initial edge, and loop until a blank line (length 0) is found
	
	getline(inputFile, fileString);
	while (fileString.length() > 0)
	{
		addEdge(fileString);
		getline(inputFile, fileString);
	}

	// close the file
	inputFile.close();
}

void Graph::print() const
{
	// prints out the whole graph
	// it will iterator over all nodes, and print each one's edges

	cout << "\n\nGraph\n-----\n";

	for(nodeVecConstIterator it=nodeList.cbegin(); it!=nodeList.cend(); ++it)
	{
		cout << "Node : " << (*it)->getNodeID() << endl;
		(*it)->printEdges();
		cout << endl;
	}

	cout << endl;
}

int Graph::printNodeList() const
{
	// prints out the node list, along with its position in the vector that
	// stores the nodes. Used to present the user with a numerated list of
	// nodes to choose as start and goal

	// returns the highest index of the vector

	int count = 0;
	cout << "Nodes : \n";
	for(nodeVecConstIterator it=nodeList.cbegin(); it!=nodeList.cend(); ++it, ++count)
	{
		cout << setw(2) << count << " : " << (*it)->getNodeID() << endl;
	}
	return --count;
}

void Graph::clearSearchState()
{
	// iterates over all nodes and clears their search states (parent node, cost, etc.)
	// so the graph can be re-used for a new search

	for(nodeVecConstIterator it=nodeList.cbegin(); it!=nodeList.cend(); ++it)
	{
		(*it)->clearSearchState();
	}
}

void Graph::addNode(const string& nodeString)
{
	// takes a string from the file, and parses it in CSV format
	// using boost tokenizer.
	// if the correct fields do not exist an exception is thrown

	string nodeID;
	float data1, data2;

	// convert the string to a token list, separated by commas
	tokenizer<escaped_list_separator<char> > tok(nodeString);
	tokenizer<escaped_list_separator<char> >::iterator it=tok.begin();
	
	// go through the tokens, and try converting them to the expected type
	// throw errors if incorrect fields are found by the lexical_cast
	int count = 0;
	while ( (count < 3) && (it!=tok.end()) )
	{
		try {
			switch (count)
			{
			case 0:
				nodeID = (*it);
				break;
			case 1:
				data1 = lexical_cast<float, string>(*it);
				break;
			case 2:
				data2 = lexical_cast<float, string>(*it);
				break;
			}
		}
		catch (bad_lexical_cast& e)
		{
			string errorString = "File format error : Did not recognize '" + nodeString + "' as a node";
			throw runtime_error(errorString.c_str());
		}
		++it;
		++count;
	}

	// if the correct number of fields was found, add the node
	// otherwise throw an error
	if ((count == 3) && (it == tok.end()))
	{
		addNode(nodeID, data1, data2);
	}
	else
	{
		string errorString = "File format error : Did not recognize '" + nodeString + "' as a node";
		throw runtime_error(errorString.c_str());
	}
}

void Graph::addNode(const string& name, const float data1, const float data2)
{
	// before adding the node, try to find it
	nodePtr nodeExists = findNode(name);

	// if the node already exists, throw an error message
	// if the node does not exist, add it to the list of nodes
	if ( nodeList.size() > 0 && nodeExists )
	{
		string errorString = "File format error : Duplicate node '" + nodeExists->getNodeID() + "'";
		throw runtime_error(errorString.c_str());
	}
	else
	{
		nodeList.push_back( nodePtr(new Node(name, data1, data2) ) );
	}
}

void Graph::addEdge(const string& edgeString)
{
	// takes a string from the file, and parses it in CSV format
	// using boost tokenizer.
	// if the correct fields do not exist an exception is thrown

	string tail, head, name;
	float data1;

	// convert the string to a token list, separated by commas
	tokenizer<escaped_list_separator<char> > tok(edgeString);
	tokenizer<escaped_list_separator<char> >::iterator it=tok.begin();
	int count = 0;

	// go through the tokens, and try converting them to the expected type
	// throw errors if incorrect fields are found by the lexical_cast
	while ( (count < 4) && (it!=tok.end()) )
	{
		try {
			switch (count)
			{
			case 0:
				tail = (*it);
				break;
			case 1:
				head = (*it);
				break;
			case 2:
				data1 = lexical_cast<float, string>(*it);
				break;
			case 3:
				name = (*it);
				break;
			}
		}
		catch (bad_lexical_cast& e)
		{
			string errorString = "File format error : Did not recognize '" + edgeString + "' as an edge";
			throw runtime_error(errorString.c_str());
		}
		++it;
		++count;
	}

	// if the correct number of fields was found, add the edge
	// otherwise throw an error
	if ((count == 4) && (it == tok.end()))
	{
		addEdge(tail, head, data1, name);
	}
	else
	{
		string errorString = "File format error : Did not recognize '" + edgeString + "' as an edge";
		throw runtime_error(errorString.c_str());
	}
}

void Graph::addEdge(const string& tail, const string& head, const float cost, const string& name)
{
	// find the pointers to nodes at head and tail, based on the strings
	// throw errors if either is not found

	nodePtr nodeTail = findNode(tail);
	if (!nodeTail)
	{
		string errorString = "File error : Node " + tail + " does not exist.";
		throw runtime_error(errorString.c_str());
	}
	nodePtr nodeHead = findNode(head);
	if (!nodeHead)
	{
		string errorString = "File error : Node " + head + " does not exist.";
		throw runtime_error(errorString.c_str());
	}
	
	// after eliminating potential errors, create the edge, add it to the list
	// and add it to the tail node's list of leaving edges
	edgePtr newEdge = edgePtr(new Edge( nodeTail, nodeHead, cost, name) );
	edgeList.push_back( newEdge );
	nodeTail->addEdge( newEdge );	
}
