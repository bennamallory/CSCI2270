b
#include <iostream>
#include <fstream>
#include "JobQueue.hpp"


using namespace std;


/*
 * Purpose: constructor
 * @param none
 * @return none
 */
JobQueue::JobQueue()
{
  //set initial conditions
  queueFront = 0;
  queueEnd = 0;
  counter = 0;
}



/*
 * Purpose: return true if the queue is empty, false otherwise
 * @param none
 * @return true or false
 */
bool JobQueue::isEmpty()
{
	//check if counter is zero (no elements)
    if(counter == 0){
        return true;
    } else {
        return false;
    }
}

/*
 * Purpose: return true if the queue is full, false otherwise
 * @param none
 * @return true or false
 */
bool JobQueue::isFull()
{
	//check if counter is same as size
    if(counter == SIZE){
        return true;
    } else {
        return false;
    }
}

/*
 * Purpose: add an element to the end of the queue
 * @param string job
 * @return none
 */
void JobQueue::enqueue(string job)
{
 //check if the queue is full
 if(!isFull()){
     //add job to the end of the queue and modify front and end

     //increase the number of elements in the array
     counter++;

     //set the end index of the array to the new value
     queue[queueEnd] = job;

     //set the queueEnd to the next value
     queueEnd = (queueEnd+1)%SIZE;

 //Otherwise queue is full
 } else {
     cout << "Queue full, cannot add new job" << endl;
 }

}


/*
 * Purpose: remove the first element in the queue
 * @param string job
 * @return none
 */
void JobQueue::dequeue()
{
 //check if the queue is empty
 if(!isEmpty()){
     //"remove" first element

     //reduce the number of elements in the array
     counter--;
     
     //move the head over to next value
     queueFront = (queueFront+1)%SIZE;

 //the queue is empty
 } else {
     cout << "Queue empty, cannot dequeue a job" << endl;
 }

}

/*
 * Purpose: see the first job
 * @param none
 * @return string job
 */
string JobQueue::peek()
{
    //check if queue is empty
    if(!isEmpty()){
        return queue[queueFront];
    } else {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
}


/*
 * Purpose: return the size of the queue
 * @param none
 * @return int counter
 */
int JobQueue:: queueSize()
{
  return counter;
}
