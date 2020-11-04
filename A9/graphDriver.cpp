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
    g1.insertVertex("Aurora");
    g1.insertVertex("Bloomington");
    g1.insertVertex("Cheyenne");
    g1.insertVertex("Denver");
    g1.insertVertex("Fruita");
    

    //Add edges
    g1.createEdge("Aurora","Bloomington",5);
    g1.createEdge("Aurora","Cheyenne",10);
    g1.createEdge("Aurora","Fruita",30);

    g1.createEdge("Bloomington","Denver",40);
    g1.createEdge("Bloomington","Fruita",15);

    g1.createEdge("Cheyenne","Denver",10);

    g1.displayEdges();

    //g1.traverseWithDijkstra("Aurora");

    g1.minDistPath("Denver", "Bloomington");


}
