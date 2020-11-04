#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::createEdge(string v1, string v2, int num){
    //search for the first vertex (v1)
    for(int i=0; i < vertices.size(); i++){
        //if you find the first vertex, search for second
        if(vertices[i]->name == v1){
            //searching for second vertex (v2)
            for(int j=0; j < vertices.size(); j++){
                //if you find the second vertex, can place edges
                if(vertices[j]->name == v2){
                    //create new edge and set value, put each vertex into other adj list
                    adjVertex e0;
                    e0.v = vertices[j];
                    e0.weight = num;
                    vertices[i]->adj.push_back(e0);

                    adjVertex e1;
                    e1.v = vertices[i];
                    e1.weight = num;
                    vertices[j]->adj.push_back(e1);

                }
            }
        }
    }
}

void Graph::insertVertex(string n){
    //CASE 1: vertex is already present
    bool found = false;


    //iterate through vertex list and search for key value
    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == n){
            found = true;
        }
    }

    //CASE 2: Dynamically allocate space for a new vertex and add to vector
    if(found == false){
        vertex* v = new vertex;
        v->name = n;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    // cout<<"here"<<vertices.size()<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name << " "<<vertices[i]->adj[j].weight<<endl;
        }
        cout<<endl;
    }
}

void Graph::traverseWithDijkstra(string start){
    //compute the single source shortest path in the graph from the start city to its component
    //find vertex pointer
    vertex* vStart = NULL;
    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == start){
            vStart = vertices[i];
        }
    }

    //If start not found
    if(vStart == NULL){
        cout << "Start not found" << endl;
    }

    //Start ALG
    vStart->visited = true;
    vStart->distance = 0;

    //Create a list to store solved vertices and append to vStart
    vector<vertex*> solvedList;
    solvedList.push_back(vStart);

    //Use boolean to leave the loop if all vertices solved
    bool allSolved = false;

    while(!allSolved){
        int minDist = 2147483647;

        //pointer to keep track of solved node
        vertex* solvedV = NULL;
        allSolved = true;

        //iterate across the list of solved vertices
        for(int i=0; i < solvedList.size(); i++){
            //start at first vertex in list
            vertex* s = solvedList[i];
            //cout << s->name << endl;

            //iterate over s's adj list
            for(int j=0; j < s->adj.size(); j++){
                //if it hasn't been visited, calculate distance from vStart
                if(!s->adj[j].v->visited){
                    //calculate distance from vStart
                    int dist = s->distance + s->adj[j].weight;

                    //check to see if distance is less than smallest dist so far
                    if(dist < minDist){
                        //store new vertex as solved V and update dist from start
                        solvedV = s->adj[j].v;
                        minDist = dist;
                        s->adj[j].v->pred = s;
                    }
                    allSolved = false;
                }
            }
        }
        
        //If not all are solved yet, store new vert with distance in solvedList
        if(!allSolved){
            solvedV->distance = minDist;
            solvedV->visited = true;
            solvedList.push_back(solvedV);
        }
    }
    
}


void depthFirstRecursive(vertex* root){ 
    //set this vertex to be visited
    root->visited = true;

    //loop across adj list of vertex
    for(int j=0; j < root->adj.size(); j++){
        //check to see if vertices in adj list have been visited
        if(!root->adj[j].v->visited){
            //if not visited, display that vertex key
            cout << root->adj[j].v->name << " -> ";

            //recursively call again to get next 
            depthFirstRecursive(root->adj[j].v);
        }
    }

}

void Graph::depthFirstTraversal(string sourceVertex)
{ 
    //SEARCH
    vertex* root; 
    //find the pointer to this vertex
    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            root = vertices[i];
        }
    }
    
    //display the vertex key
    cout << root->name << " -> ";

    //recursive call with root
    depthFirstRecursive(root);

    cout << "DONE";

}

void Graph::minDistPath(string source, string destination) {
    //print the shortest path found between city 1 and city two by invoking traverseWithDijkstra
    traverseWithDijkstra(source);

    // the "path" vector stores the vertices of the shortest path
    vector<vertex*> path;

    // A pointer for destination vertex and start vertex
    vertex *vDest;
    vertex *crawler;

    //Find destination vertex
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == destination){
            vDest = vertices[i];
        }
    }

    //Back track through the list until you hit the vStart key
    path.push_back(vDest);
    crawler = vDest;

    //crawl backward through pred nodes
    while(crawler->name != source){
        crawler = crawler->pred;
        path.push_back(crawler);
    }
    
    //cout << "The shortest path is: " << endl; 
    int totDist = 0;
    //print array in reverse to get correct order
    for(int k = path.size()-1; k >= 0; k--){
        cout << path[k]->name << " -> ";
    }

    //print out the first index distance (dijkstras distance)
    cout << "DONE " << "[" << path[0]->distance << "]" << endl;
}
