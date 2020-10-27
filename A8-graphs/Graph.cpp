#include<vector>
#include<iostream>
#include "Graph.hpp"
using namespace std;


/*
Purpose: function to add an edge between two vertices
@param: string v1, string v2 -- for both vertices to connect
@return: none
*/
void Graph::addEdge(string v1, string v2){
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
                    vertices[i]->adj.push_back(e0);

                    adjVertex e1;
                    e1.v = vertices[i];
                    vertices[j]->adj.push_back(e1);

                }
            }
        }
    }
}


/*
Purpose: function to add a vertex to graph
@param: string name -- key value of vertex
@return: none
*/
void Graph::addVertex(string name){
    //CASE 1: vertex is already present
    bool found = false;


    //iterate through vertex list and search for key value
    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }

    //CASE 2: Dynamically allocate space for a new vertex and add to vector
    if(found == false){
        vertex* v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }

}


/*
Purpose: function to display all the edges in the graph
@param: none
@return: none
*/
void Graph::displayEdges(){
    //get size of the vertices matrix
    int size = vertices.size();

    //loop through each of the vertices
    for(int i=0; i < size; i++){
        cout << vertices[i]->name << " --> ";

        //get the size of the adjVert
        int adjVertSize = vertices[i]->adj.size();

        //loop through each of the adjVert and print
        for(int j=0; j < adjVertSize; j++){
            //index to vertex (is a pointer) -- get adj value (->), in adjValue -- get pointer to adjVert (.), vert is pointer (get key ->)
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
    
}

//Queue struct to use for BFT
struct Queue {
    int queueFront; //the index in queue[] that will be dequeued next
    int queueEnd; //the index in queue[] that keeps track of the next available empty space
    int counter; // number of elements in the queue currently
    vertex* queue[20];
};

//Constructs the queue
void constructQueue(Queue* q){
  //set initial conditions
  q->queueFront = 0;
  q->queueEnd = 0;
  q->counter = 0;
}

//checks to see if the queue is empty
bool isEmpty(Queue* q)
{
	//check if counter is zero (no elements)
    if(q->counter == 0){
        return true;
    } else {
        return false;
    }
}

//checks to see if queue is full
bool isFull(Queue* q)
{
	//check if counter is same as size
    if(q->counter == 20){
        return true;
    } else {
        return false;
    }
}

//enqueues a vertex pointer
void enqueue(vertex* vertex, Queue* q)
{
    //check if the queue is full
    if(!isFull(q)){
        //add job to the end of the queue and modify front and end

        //increase the number of elements in the array
        q->counter++;

        //set the end index of the array to the new value
        q->queue[q->queueEnd] = vertex;

        //set the queueEnd to the next value
        q->queueEnd = (q->queueEnd+1)%20;

 //Otherwise queue is full
    } else {
        cout << "Queue full, cannot add new job" << endl;
    }
}

//dequeues
void dequeue(Queue* q)
{
 //check if the queue is empty
    if(!isEmpty(q)){
        //"remove" first element

        //reduce the number of elements in the array
        q->counter--;
        
        //move the head over to next value
        q->queueFront = (q->queueFront+1)%20;

    //the queue is empty
    } else {
        cout << "Queue empty, cannot dequeue a job" << endl;
    }

}

//peeks at the first element in the array
vertex* peek(Queue* q)
{
    //check if queue is empty
    vertex* emptyVert = NULL;
    if(!isEmpty(q)){
        return q->queue[q->queueFront];
    } else {
        cout << "Queue empty, cannot peek" << endl;
        return emptyVert;
    }
}

/*
Purpose: function to display vertices breadth first
@param: string sourceVertex -- name of "root" vertex 
@return: none
*/
void Graph::breadthFirstTraverse(string sourceVertex){
    //find key of starting vertex (sourceVertex)
    vertex* vStart = NULL;
    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            // cout << "FOUND vStart" << endl;
            vStart = vertices[i];
        }
    }


    //set vStart as "visited"
    vStart->visited = true;
    
    cout << "Starting vertex (root): " << vStart->name << "-> ";

    //create a queue
    Queue* q = new Queue;
    constructQueue(q);

    //enqueue vstart
    enqueue(vStart,q);


    //loop until queue is empty 
    while(!isEmpty(q)){
        //store the first element in the queue
        vertex* n = peek(q);

        //dequeue that element
        dequeue(q);

        //loop across n's adjList
        for(int x=0; x < n->adj.size(); x++){
            //if the adj vertex has not been visited, change that
            if(!(n->adj[x].v->visited)){
                //set that vertex to be visited
                n->adj[x].v->visited = true;
                //add that vertex to the queue
                enqueue(n->adj[x].v,q);
                //set that vertex's distance from n
                n->adj[x].v->distance = n->distance+1;

                //print that vertex and distance
                cout << n->adj[x].v->name << "(" << n->adj[x].v->distance << ")" << " ";
            }
        }
    }
}


/*
Purpose: helper function 
@param: string sourceVertex -- name of "root" vertex 
@return: none
*/
int getConnectedComponents(string sourceVertex,vector<vertex*> vertices){
    //find key of starting vertex (sourceVertex)
    vertex* vStart = NULL;
    int numVisited = 0;

    //reset all vertex to not visited
    // for(int i=0; i < vertices.size(); i++){
    //     vertices[i]->visited = false;
    // }

    for(int i=0; i < vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            // cout << "FOUND vStart" << endl;
            vStart = vertices[i];
        }
    }

    //set vStart as "visited"
    vStart->visited = true;

    //create a queue
    Queue* q = new Queue;
    constructQueue(q);

    //enqueue vstart
    enqueue(vStart,q);

    //loop until queue is empty 
    while(!isEmpty(q)){
        //store the first element in the queue
        vertex* n = peek(q);

        //dequeue that element
        dequeue(q);

        //loop across n's adjList
        for(int x=0; x < n->adj.size(); x++){
            //if the adj vertex has not been visited, change that
            if(!(n->adj[x].v->visited)){
                //set that vertex to be visited
                n->adj[x].v->visited = true;
                numVisited++;
                //add that vertex to the queue
                enqueue(n->adj[x].v,q);
                //set that vertex's distance from n
                n->adj[x].v->distance = n->distance+1;
            }
        }
    }

    //if there are some new visited nodes from the start node, return 1
    if(numVisited != 0){
        //cout << "Vertices visited" << endl;
        return 1;

    //if there are no new visited nodes, but the subgraph is one vertex
    } else if (numVisited == 0 && vStart->adj.size() == 0) {
        //cout << "No vertices visited" << endl;
        return 1;
    } else {
        return 0;
    }

}


int Graph::getConnectedBuildings(){
    int numSubGraphs = 0;

    //loop through the graph, find if all the nodes have been visited
    for(int i=0; i < vertices.size(); i++){
        numSubGraphs += getConnectedComponents(vertices[i]->name,vertices);
    }

    //return the number of graphs that are separate
    return numSubGraphs;
}
