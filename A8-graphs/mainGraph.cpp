#include <iostream>
#include <fstream>
#include <sstream>

#include "Graph.hpp"

using namespace std;


int main(int argc, char *argv[])
{
    //Create an instance of the graph
	Graph g1;

    //Add vertices
    g1.addVertex("ATLS");
    g1.addVertex("EC");
    g1.addVertex("AERO");

    //Add edges
    g1.addEdge("ATLS","EC");
    g1.addEdge("AERO","EC");

    g1.displayEdges();

    //g1.breadthFirstTraverse("ATLS");

    cout << endl;
    cout << g1.getConnectedBuildings() << endl;

}
