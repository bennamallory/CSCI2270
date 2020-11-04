// CSCI 2270 Fall 2020
// Author: Mallory Benna
// Recitation: 103 – Abhidip Bhattacharyya
// Assignment 2 - mobyDick, ignoreWords

#include<string>
#include<iostream>
#include<fstream>
using namespace std;


//struct to store the words and their counts
struct wordRecord{
    string word;
    int count;
};

/*
* This function 
* Parameters: 
* Return: 
*/
void getIgnoreWords (const char *ignoreWordFileName, string ignoreWords[]){
    //Variables

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
            cout << word << endl;
            i++;
        }
    }
    fileStream.close();
}

int main(int argc, char* argv[]){
    //Variables
    string ignoredWordsArr[50];

    //Store the command line arguments for N, file name of text to be read, ignored words file

    //Check if there are a correct number of command line arguments
    if(argc != 4){
        cout << "Usage: Assignment2SOlution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt" << endl;
    } else {
        string numberN = argv[1];
        int numberNInt = stoi(numberN);
        string fileRead = argv[2];
        string ignoredWordFile = argv[3];
    }

    //Get stop-words/common-words from ignoreWords.txt and store them in an array (call getIgnoreWords fucntion)
        //Ignore the top 50 most common words in mobyDick that are read from the ignoredWordFile
    getIgnoreWords(ignoredWordFile,ignoredWordsArr);

    //Implement Array Doubling Algorithm

    //Read words from mobydick.txt and store all unique words not in ignore-words in an array of structs
        //create dynamic wordRecord array of size 100
        //add non-ignore words to the array (double the array size if array is full)
        //keep track of the number of times the wordRecord array is doubled and the number of unique non-ignore words

    
    //Output next 10 most frequent words, starting at index numberNInt
        //cout << "Array doubled: " << number of times the array was doubled << endl;
        // cout << "Distinct non-common words: " << number of distinct non-commonn words << endl; (unique non ignore words)
        // cout << "Total non-common words: " << number of words from file that are not common words << endl;
        // cout << "-----------------------------" << endl;
        //probability of the 10 words starting from index N
        // cout << probability << " - " << word << endl;

    return 0;

}