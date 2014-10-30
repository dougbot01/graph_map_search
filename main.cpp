/*
 * (C) 2014 Douglas Sievers
 *
 * main.cpph
 */

#include <iostream>
#include <exception>
#include <fstream>
#include <cstdlib>
#include <string>

#include "Graph.h"
#include "BestFirstSearch.h"
#include "UniformCostSearch.h"
#include "AStarSearch.h"

using namespace std;

string getFilename()
{
	// READ A FILE NAME
	string filename;
	cout << "Enter a file name: ";
	cin >> filename;
	return filename;
}

int main()
{
	// Prompt user for a file
	string filename = getFilename();

	try
	{
		// Create a graph instance, and read the file into it
		Graph g;
		g.readFile(filename.c_str());
		g.print();					//print the graph, for fun
	
		// Print the list of nodes available for user to choose
		// start and end points
		int numNodes = g.printNodeList();
		int startNode, goalNode;

		// Prompt user
		cout << "\nEnter start Node (0-" << numNodes << ") : ";
		cin >> startNode;
		cout << "Enter goal Node (0-" << numNodes << ") : ";
		cin >> goalNode;
		cout << endl;

		cout << "\nBEST FIRST SEARCH   \n--------------------\n";
		BestFirstSearch a = BestFirstSearch(g);
		a.search(startNode, goalNode);
		
		#ifdef _WIN32
			system("PAUSE");
		#endif
	
		cout << "\nUNIFORM COST SEARCH \n--------------------\n";
		UniformCostSearch b = UniformCostSearch(g);
		b.search(startNode, goalNode);
		
		#ifdef _WIN32
			system("PAUSE");
		#endif
	
		cout << "\nA STAR SEARCH       \n--------------------\n";
		AStarSearch c = AStarSearch(g);
		c.search(startNode, goalNode);
		
		#ifdef _WIN32
			system("PAUSE");
		#endif
	}

	// catch any errors and quit
	catch (std::exception& e)
	{
		cout << e.what() << endl;
		
		#ifdef _WIN32
			system("PAUSE");
		#endif
	}

	return 0;
}

