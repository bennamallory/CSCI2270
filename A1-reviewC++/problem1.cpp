// CSCI 2270 Fall 2020
// Author: Mallory Benna
// Recitation: 103 – Abhidip Bhattacharyya
// Assignment 1 - Problem #1 - addToArrayAsc

#include<string>
#include<iostream>
#include<fstream>
using namespace std;

/*
* This function adds a new element into an array and sorts it from smallest to largest
* Parameters: float sortedArray[], int numElements, float newValue
* Return: int numElements
*/
int addToArrayAsc(float sortedArray[], int numElements, float newValue){
    //Variables
    int indexForNew;

    //Iterate through array and place smallest element at the front
    if(numElements == 0){
        sortedArray[0] = newValue;
        numElements++;
    } else {
        //check the values iterated and arrange
        for(int i=0; i < numElements; i++){
            //If new value less than any value in the array, shift and place
            if(newValue < sortedArray[i]){
                //find index for insertion
                indexForNew = i;

                //shift all data right one
                for(int k=numElements; k > indexForNew; k--){
                    //shift...
                    sortedArray[k] = sortedArray[k-1];
                }

                sortedArray[indexForNew] = newValue;
                break;

            //Otherwise, place at the end
            } else {
                sortedArray[numElements] = newValue;
            }
        }

        numElements++;
    }

    //return a count of the elements inserted so far (current size of the array)
    return numElements;

}

int main(int argc, char* argv[]){
    //variables
    float arrayThatsSorted[100];
    int numElementsInserted = 0;
    float valueToInsert;


    //create an array of floats to store at most 100 floats
    float floatArr[100];

    //store the command line argument for the text file as "fileName"
    string fileName = argv[1];
    
    //open the file passed via the the command line
    ifstream fileStream;
    fileStream.open(fileName);

    //read the file and print failed statement if file fails to open
    if(fileStream.fail()){
        cout << "Failed to open the file " << endl;
    } else {
        string line;
        while(getline(fileStream,line)){
            //grab each new value to insert
            valueToInsert = stof(line);
            //cout << valueInserted << endl;

            //store these integers in a sorted array by passing them to the addToArrayAsc
            numElementsInserted = addToArrayAsc(arrayThatsSorted, numElementsInserted, valueToInsert);

            //print entire array after each insertion
            for(int j=0; j < numElementsInserted; j++){
                //Make sure comma only gets printed in between numbers and not at the end
                if(j != numElementsInserted-1){
                    cout << arrayThatsSorted[j] << ",";
                } else {
                    cout << arrayThatsSorted[j];
                }
                
            }
            cout << endl;
        }
    }
    
    return 0;
}

//ISSUES -- getting duplicates? losing numbers?
