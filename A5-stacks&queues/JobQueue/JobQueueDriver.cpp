/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}


// Use getline for reading
int main(int argc, char const *argv[])
{	
	//instantiate object
	JobQueue job1;


	string inputString;
	string s1;
	string s2;
	int input = 0;
	int numJobs;
	int totalJobs;


	//run menu in a loop
	while(input != 3){

		//display the menu
		menu();

		//get the user input
		getline(cin,inputString);

		//store the input value
		input = stoi(inputString);

		//test the cases
		switch (input)
		{
			case 1:   //add jobs into the queue
				cout << "Enter the number of jobs to be created:" << endl;
				getline(cin,s1);
				numJobs = stoi(s1);
				for(int i=1; i < numJobs+1; i++){
					cout << "job" << i << ":" << endl;
					getline(cin,s1);
					job1.enqueue(s1);
				}
				
				break;

			case 2: //dispatch jobs from the queue
				cout << "Enter the number of jobs to be dispatched: " << endl;
				getline(cin,s2);
				numJobs = stoi(s2);

				//if the number of jobs dispatched is greater than total, dequeue all jobs
				totalJobs = job1.queueSize();
				if(numJobs > totalJobs){
					//dequeue all jobs
					for(int j=0; j < totalJobs; j++){
						cout << "Dispatched: " << job1.peek() << endl;
						job1.dequeue();
					}
					cout << "No more jobs to be dispatched from queue" << endl;

				//Dispatch the number of jobs requested
				} else {
					for(int j=0; j < numJobs; j++){
						cout << "Dispatched: " << job1.peek() << endl;
						job1.dequeue();
					}
				}

				break;

			case 3: //return the queue size and exit
				cout << "Number of jobs in the queue:" << job1.queueSize() << endl;
				break;

			default:
				cout << "Invalid Input" << endl;
				break;
		}
	}
	
}
