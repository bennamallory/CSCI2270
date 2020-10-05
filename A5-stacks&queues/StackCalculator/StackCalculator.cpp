#include <iostream>
#include <iomanip>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //Set the stackHead pointer to NULL
  stackHead = NULL;
}

StackCalculator::~StackCalculator()
{
  //Destroy the stack, remove all nodes
  Operand *current;

  //While the stack still has values, delete nodess
  while(!isEmpty()){
    //set current value (crawler to top of stack)
    current = stackHead;

    //set stackHead to the next down
    stackHead = stackHead->next;

    //delete the top of the stack
    delete current;
  }


}

bool StackCalculator::isEmpty()
{
	//If the top of the stack is NULL, return true (stack empty)
  if(stackHead == nullptr){
    return true;

  //If it is not NULL, then it is not empty (return false)
  } else {
    return false;
  }
}

void StackCalculator::push(float number)
{
  //Allocate memory for a new node
  Operand* temp = new Operand;

  //Set the key of the node
  temp->number = number;

  //Check if stack is empty
  if(isEmpty()){
    //If it is empty, new node is the head
    stackHead = temp;
    stackHead->next = NULL;

  //If it is not empty, new node goes after the head and set it to the head
  } else {
    //set it to point down to current head
    temp->next = stackHead;

    //set new head to this node
    stackHead = temp;
  }

}

void StackCalculator::pop()
{
  //Pop top element off the stack
  Operand* temp;

  //Check if empty, not empty, set temp to top and move top down and delete top
  if(!isEmpty()){
    //set to top node
    temp = stackHead;

    //set head to next down in stack
    stackHead = stackHead->next;

    //pop the top node off
    delete temp;
  } else {
    cout << "Stack empty, cannot pop an item." << endl;
  }

}

Operand* StackCalculator::peek()
{
	//return the top pointer
  if(isEmpty()){
    cout << "Stack empty, cannot peek." << endl;
    return nullptr;
  } else {
    return stackHead;
  }

}

bool StackCalculator:: evaluate(string* s, int size)
{
  /*TODO: 1.scan the array from the end
          2.Use isNumber function to check if the input is an operand
          3.push all operands to the stack
          4.If operator take two element of from the stack,
            compute and put the result back in stack
          5.Handle the boundery cases as required.
          6.Read the writeup for more details
  */

  //scan the array from the end
  for(int i=size-1; i > -1; i--){
    //if it is a number push it onto the stack
    if(isNumber(s[i])){
      //push it onto the stack
      float insertNum = stof(s[i]);
      push(insertNum);

    //it is not a number, evaluate the operator
    } else if(!isNumber(s[i])) {
      //evaluate if it is a valid operator (+ or *)
      if(s[i] != "+" && s[i] != "*"){
        cout << "err: invalid operation" << endl;
        return false;
      } else {
        //the operand is true, evaluate and push onto stack
        
        //if stack is empty or there is only one number on the stack (not enough operands)
        if(isEmpty()){
          cout << "err: not enough operands" << endl;
          return false;
        //Otherwise, add as usual
        } else {
          float val1;
          float val2;
          float result;

          //get two values from stack
          val1 = stackHead->number;
          pop();
          val2 = stackHead->number;
          pop();

          //perform the operation
          if(s[i] == "+"){
            result = val1 + val2;
          } else if (s[i] == "*"){
            result = val1*val2;
          }

          //push the result onto the stack
          push(result);
        }
      }
    }
  }
  return true;
}
