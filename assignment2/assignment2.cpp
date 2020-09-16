// CSCI 2270 Fall 2020
// Author: Mallory Benna
// Recitation: 103 – Abhidip Bhattacharyya
// Assignment 2 - mobyDick, ignoreWords

#include<string>
#include<iostream>
#include<fstream>
#include <iomanip>
#include <stdlib.h>  //reference from http://www.cplusplus.com/reference/cstdlib/atoi/
using namespace std;


//struct to store the words and their counts
struct wordRecord{
    string word = "";
    int count = 0;
};

/*
* This function opens the ignoredWord text file and stores each word in an array
* Parameters: const char *ignoreWordFileName, string ignoreWords[]
* Return: nothing
*/
void getIgnoreWords (const char *ignoreWordFileName, string ignoreWords[]){
    //Open and read ignore word file
    ifstream fileStream;
    fileStream.open(ignoreWordFileName);

    //read the file and print failed statement if file fails to open
    if(fileStream.fail()){
        cout << "Failed to open " << ignoreWordFileName << endl;
    } else {
        //read file
        string word;
        int i = 0;
        while (fileStream >> word ){
            ignoreWords[i] = word;
            i++;
        }
    }
    fileStream.close();
}


/*
* This function checks to see if word is in the ignoreWords array
* Parameters: string word, string ignoreWords[]
* Return: true or false
*/
bool isIgnoreWord(string word, string ignoreWords[]){
    //Check if the word is in the ignoreWords array
    for(int i=0; i < 50; i++){
        if(word == ignoreWords[i]){
            return true;
        }
    }

    return false;
}

/*
* This function computes the total number of words in the entire document by summing up all the counts of the individual unique words
* Parameters: wordRecord distinctWords[], int length
* Return: int numUniqueWords
*/
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length) {
    //Variables
    int numUniqueWords = 0;

    //Read through all the stucts in the distinctWords array, add all the counts
    for(int j=0; j < length; j++){
        numUniqueWords += distinctWords[j].count;
    }
    return numUniqueWords;
}

/*
* This function sorts the distinctWords array (containing length number of elements) by word count such tat the most frequent words are sorted to the begining
* Parameters: wordRecord distinctWords[], int length
* Return: none
*/
void sortArray(wordRecord distinctWords[], int length) {
    //Variables
    wordRecord temp;

    //sort array so that the most frequent words are at the begining (most count value)
    //compare first value to all rest, swap if first number less than second
    for(int i=0; i < length; i++){
        for(int j=i+1; j < length; j++){
            if(distinctWords[i].count < distinctWords[j].count || (distinctWords[i].count==distinctWords[j].count && distinctWords[i].word >distinctWords[j].word)){
                //set smaller value to temp
                temp.word = distinctWords[i].word;
                temp.count = distinctWords[i].count;

                //set first values to the larger value
                distinctWords[i].word = distinctWords[j].word;
                distinctWords[i].count = distinctWords[j].count;

                //set swapped value to temp (old smaller values)
                distinctWords[j].word = temp.word;
                distinctWords[j].count = temp.count;
            }   
        }
    }
}


/*
* This function doubles an array dynamically, reference from exercise.cpp
* Parameters: wordRecord* arrayPtr, int &capacity
* Return: wordRecord* newArray
*/
wordRecord* resize(wordRecord* arrayPtr, int &capacity)
{
	// Increase the capacity by two times
	int newCapacity = 2*capacity;
    
	//cout<<"Resizing from "<< capacity <<" to "<< newCapacity <<endl;

	// Dynamically allocate an array of size newCapacity
	wordRecord *newArray;
    newArray = new wordRecord[newCapacity];

	//Copy all data from oldArray to newArray
	for(int i=0; i < capacity; i++){
		newArray[i].word = arrayPtr[i].word;
        newArray[i].count = arrayPtr[i].count;
	}

	// Free the memory associated with oldArray
	delete [] arrayPtr;

	//Set capacity to new value
	capacity = newCapacity;

	//return the newArray
	return newArray;
}

/*
* This function prints the next 10 words after th starting index N from sorted array of distinct words
* Parameters: wordRecord distinctWords[], int N, int totalNumWords
* Return: none
*/
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords) {
    //Variables
    float probability;

    for(int k=N; k < (N+10); k++){
        probability = (float)distinctWords[k].count/totalNumWords;
        cout << fixed << setprecision(5) << probability << " - " << distinctWords[k].word << endl;
    }

}

/*
* This function checks to see if word is in the dynamic array already
* Parameters: string word, wordRecord dynamicArray, int length
* Return: index of duplicate or -1
*/
int isDuplicate(string word, wordRecord distinctWords[], int length){
    //Check if the word is in the array already
    for(int i=0; i < length; i++){
        if(word == distinctWords[i].word){
            return i;
        }
    }
    return -1;
}


int main(int argc, char* argv[]){
    //Variables
    string ignoredWordsArr[50];
    int numberTimesDoubled = 0;
    int duplicateIndex;

    //Store the command line arguments for N, file name of text to be read, ignored words file
        //Check if there are a correct number of command line arguments
    if(argc != 4){
        cout << "Usage: Assignment2SOlution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt" << endl;
    } 

    //reference from http://www.cplusplus.com/reference/cstdlib/atoi/
    int numberN = atoi(argv[1]);

    //Get stop-words/common-words from ignoreWords.txt and store them in an array (call getIgnoreWords fucntion)
    getIgnoreWords(argv[3],ignoredWordsArr);

    //Set up the file stream
    ifstream inStream;
    inStream.open(argv[2]); 

    //create dynamic wordRecord array of size 100
    //int capacity = 100;
    int capacity = 100;
    wordRecord *dynamicWordRecArr;
    dynamicWordRecArr = new wordRecord[capacity];
    int numElement = 0;
    string word;
    int duplicateWordIndex;

    //open the file and print failed statement if file fails to open
    if(inStream.fail()){
        cout << "Failed to open " << argv[2] << endl;
    } else {
        //read words from mobydick.txt and store all unique words in an array of structs
        while(inStream >> word){
            //If it is not an ignored word then add it to the dynamic array
            duplicateWordIndex = isDuplicate(word, dynamicWordRecArr, numElement);
            
            if(!isIgnoreWord(word,ignoredWordsArr)){
                //resize array
                if((numElement == capacity) && (duplicateWordIndex == -1)){
                    dynamicWordRecArr = resize(dynamicWordRecArr,capacity);
                    numberTimesDoubled++;
                }
                
                //set array values
                if(duplicateWordIndex == -1) {
                    dynamicWordRecArr[numElement].word = word;
                    dynamicWordRecArr[numElement].count += 1;
                    numElement++;
                } else if(duplicateWordIndex != -1){
                    dynamicWordRecArr[duplicateWordIndex].count += 1;
                }
            }
                    
        }
        inStream.close();
    }


    //Sort alphabetically
    //sortArrayAlphabet(dynamicWordRecArr,numElement);
    //Sort the array
    sortArray(dynamicWordRecArr,numElement);


    //Output 
    cout << "Array doubled: " << numberTimesDoubled << endl;
    cout << "Distinct non-common words: " << numElement << endl;
    int total = getTotalNumberNonIgnoreWords(dynamicWordRecArr,numElement);
    cout << "Total non-common words: " << total << endl;
    cout << "Probability of next 10 words from rank " << numberN << endl;
    cout << "---------------------------------------" << endl;
    printTenFromN(dynamicWordRecArr,numberN,total);

    return 0;

}
