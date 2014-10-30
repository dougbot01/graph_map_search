graph_map_search
================

A C++ implementation of a graph structure, used to find shortest routes.
Includes Best First Search, Uniform Cost Search, and A* Search

Installing
==========

This was developed on Windows, so the code is portable. However, the instructions below are for installing on Ubuntu Linux.

1) Download the code
2) To compile using the included script, you'll need to download Boost 1.51.0 (http://sourceforge.net/projects/boost/files/boost/1.51.0/boost_1_51_0.tar.gz/download) and untar it in the source directory. If your system includes a newer version of Boost, I assume it will work, but you will have to change the include directory in build.sh.
3) From the command line: ./build.sh

Running the program
===================

1) From the command line: ./search
2) When prompted for a file, enter “major_cities_state.txt” or “major_cities.txt”
3) When prompted again, enter whatever values you want to execute the searches

Recommended Input
=================

There are a couple input choices that illustrate the differences in the search methods.

Choice 1 : Start = 1/San Diego, Goal = 5/Salt Lake City
	In this case, all 3 search methods give the same result, with shortest route of 1306 km. However, you will see that Uniform Cost Search takes 6 nodes to find the result, but the other two methods require only 3 nodes.

Choice 2 : Start = 0/Los Angeles, Goal = 9/Oklahoma City
	In this case, the differences are more clear.
Best First Search : Takes 2 nodes, going through Denver with distance2728km.
Uniform Cost Search : Takes 9 nodes, but finds the shortest path through Albuquerque of 2142km.
A* Search : Also finds the shortest path, but requires only 4 nodes to do so.

Best First Search tries to get as close to the goal in a single step, so it terminates quickly. However, it may not always find the shortest route, because it is based on a heuristic but the path cost may be larger.

Uniform Cost Search will always find the shortest path, however it must generate many nodes because it has no knowledge about which nodes are closes to the goal.

A* Search is a best of breed. It always finds the shortest path, and uses a heuristic that searches nodes first that have the shortest total estimated distance, which is the sum of the path cost so far, and the estimated remaining distance. This allows the search to proceed efficiently toward its goal.

Input Files
===========

For those who want to try this on Windows, use the files in the "win_input" folder instead. The line endings have only been changed.

License & Copyright
===================

No specific license. Just give credit where it is due!

(C) 2014 Douglas Sievers
