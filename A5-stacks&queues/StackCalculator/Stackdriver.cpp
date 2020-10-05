#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;

int main()
{
  // stack to hold the operands
  StackCalculator stack;
  bool result;

  int numElement = 0;
  string* inparr = new string[50];

  // enter a number
  string number;
  cout << "Enter the operators and operands ('+', '*') in a prefix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, number);

    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. store them in inparr
    */
    if(number != "="){
      inparr[numElement] = number;
      //cout << inparr[numElement] << endl;
      numElement++;
    } else {
      break;
    }

  }

  /* TODO - If the inparr is empty then print "No operands: Nothing to evaluate"
            else call the evaluate function
  */
  if(numElement == 0){
    cout << "No operands: Nothing to evaluate" << endl;
  } else {
    result = stack.evaluate(inparr,numElement);
  }


  /* TODO - Validate the expression
      1. If valid then print the result cout << "Result= "<<result << endl;
      2. Else, print "Invalid expression"*/
  if(result == true){
    cout << "Result= " << stack.peek()->number << endl;
  }

  return 0;
}
