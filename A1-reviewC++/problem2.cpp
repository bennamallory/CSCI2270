// CSCI 2270 Fall 2020
// Author: Mallory Benna
// Recitation: 103 – Abhidip Bhattacharyya
// Assignment 1 - Problem #2 - addStudentData

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

//Student struct
struct studentData {
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};


/*
* This function adds data to student struct and places in student array
* Parameters: studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length
* Return: none
*/
void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length){
    //Instantiate student object
    studentData stud;

    //Store values
    stud.studentName = studentName;
    stud.homework = homework;
    stud.recitation = recitation;
    stud.quiz = quiz;
    stud.exam = exam;
    stud.average = (homework + recitation + quiz + exam)/4.0;

    //Add struct to students array
    students[length] = stud;
    length++;
}

/*
* This function calculates a letter grade character based off of an average value
* Parameters: double avg   
* Return: char letterGrade
*/
char calcLetter(double avg){
    //Variables
    char letterGrade;

    if(avg > 90.0){
        letterGrade = 'A';
    } else if (avg > 80.0 && avg < 89.9){
        letterGrade = 'B';
    } else if (avg > 70.0 && avg < 79.9){
        letterGrade = 'C';
    } else if (avg > 60.0 && avg < 69.9){
        letterGrade = 'D';
    } else if (avg < 60.0){
        letterGrade = 'F';
    }

    return letterGrade;
}

/*
* This function prints out the data for the students in the student struct array
* Parameters: const studentData students[], int length
* Return: none
*/
void printList(const studentData students[], int length){
    //Loop throught the students array
        //Print out each element of the student array
    for(int i=0; i < length; i++){
        cout << students[i].studentName << " earned " << students[i].average << " which is an " << calcLetter(students[i].average) << endl;
    }
}

int main(int argc, char* argv[]){
    //Variables
    int homeworkConverted, recitationConverted, quizConverted, examConverted;
    studentData studentsArr[100];
    int numStudentsTotal = 0;
    char grade;
    char lowerGradeChar;
    char upperGradeChar;

    //store the command line arguments
    string inputFile = argv[1]; //input file
    string outputFile = argv[2]; //output file
    string lowBoundGrade = argv[3]; //low bound letter grade
    string uppBoundGrade = argv[4]; //upper bound letter grade

    //Convert low bound letter grade to a char
    if(lowBoundGrade == "A"){
        lowerGradeChar = 'A';
    } else if(lowBoundGrade == "B"){
        lowerGradeChar = 'B';
    } else if(lowBoundGrade == "C"){
        lowerGradeChar = 'C';
    } else if(lowBoundGrade == "D"){
        lowerGradeChar = 'D';
    } else if(lowBoundGrade == "F"){
        lowerGradeChar = 'F';
    }

    //Convert upper bound letter grade to a char
     if(uppBoundGrade == "A"){
        upperGradeChar = 'A';
    } else if (uppBoundGrade == "B"){
        upperGradeChar = 'B';
    } else if (uppBoundGrade == "C"){
        upperGradeChar = 'C';
    } else if (uppBoundGrade == "D"){
        upperGradeChar = 'D';
    } else if (uppBoundGrade == "F"){
        upperGradeChar = 'F';
    }

    
    //open the file passed via the the command line
    ifstream fileStream;
    fileStream.open(inputFile);

    //read the file and print failed statement if file fails to open
    if(fileStream.fail()){
        cout << "Failed to open the file " << endl;
    } else {
        string line, name, homeworkVal, recitationVal, quizVal, examVal;

        //read the entire line
        while(getline(fileStream,line)){
            stringstream s(line); //converting the line into a stream to be read from
            getline(s,name,',');
            getline(s,homeworkVal,',');
            getline(s,recitationVal,',');
            getline(s,quizVal,',');
            getline(s,examVal,'\n');


            //Convert strings read from file into proper data types
            homeworkConverted = stoi(homeworkVal);
            recitationConverted = stoi(recitationVal);
            quizConverted = stoi(quizVal);
            examConverted = stoi(examVal);

            //Add students to array
            addStudentData(studentsArr, name, homeworkConverted, recitationConverted, quizConverted, examConverted, numStudentsTotal);
            numStudentsTotal++;
        }

        //Print the students array
        printList(studentsArr,numStudentsTotal);

    }
    fileStream.close();

    //Open outStream and pass the name of the output file
    ofstream outStream;
    outStream.open(outputFile);

    //Write to the file
    if(outStream.fail()){
        cout << "Out file failed to open" << endl;
        return -1;
    } else {
        //Iterate over all people in the array to calculate if they are within the bounds
        for(int j=0; j < numStudentsTotal; j++){
            grade = calcLetter(studentsArr[j].average);

            //Checking if grade is within the bounds given
            if( (grade <= lowerGradeChar) && (grade >= upperGradeChar)){
                outStream << studentsArr[j].studentName << "," << studentsArr[j].average << "," << grade << endl;
            }
        }
    }
    outStream.close();
    
    return 0;
}