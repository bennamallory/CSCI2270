// CSCI 2270 Fall 2020
// Author: Mallory Benna
// Recitation: 103 – Abhidip Bhattacharyya
// Assignment 3 - Array Doubling

#include<string>
#include<iostream>
using namespace std;

/*
 * Purpose: Inserts an element to the array at the smallest index, doubles if necessary
 * @param str_arr is the dynamic array storing the string values
 * @param s is the new string inserted
 * @param numEntries is the number of entries in the array
 * @param arraySize is the size of the entire array
 * @return true for doubled, false for not doubled
 */
bool append(string* &str_arr, string s, int &numEntries, int &arraySize){
    //Variables
    bool doubled = false;

    //Check if needs to be doubled
    if(numEntries == arraySize){
        //Create new array double the size
        string* newArray = new string[2*arraySize];

        //Transfer all values over to new array
        for(int i=0; i < numEntries; i++){
            newArray[i] = str_arr[i];
        }

        //Deallocate previous array
        delete [] str_arr;

        //Set pointer to new array
        str_arr = newArray;

        //Update arraySize
        arraySize = 2*arraySize;

        //Indicate that the array was doubled
        doubled = true;
    }

    //Append value into the array at smallest index
    str_arr[numEntries] = s;
    numEntries++;

    return doubled;
}

int main(){
    string* stringArray = new string[2];
    string newString;
    int numElements = 0;
    int currArrSize = 2;
    int doubled;

    newString = "hello";
    string newString1 = "bye";
    string newString2 = "cool";


   
    if( append(stringArray,newString,numElements,currArrSize) == 1){
        doubled++;
    }

    if( append(stringArray,newString1,numElements,currArrSize) == 1){
        doubled++;
    }

    if( append(stringArray,newString2,numElements,currArrSize) == 1){
        doubled++;
    }

    cout << doubled << endl;
   


}