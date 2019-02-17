#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

RPNCalculator ::  RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator :: ~RPNCalculator()
{
  // Destructor--pop everything off the stack and set stackHead to NULL.
  while(!isEmpty()) pop();
  stackHead = NULL;
}

bool RPNCalculator :: isEmpty()
{
  if(stackHead == NULL) return true;
  return false;
}

void RPNCalculator :: push(float num)
{
  // Insert a new node with number onto the top of the stack (beginning of linked list)
  Operand *newOperand = new Operand;
  newOperand -> number = num;
  newOperand -> next = stackHead;
  stackHead = newOperand;
}

void RPNCalculator :: pop()
{
  // If the stack is empty, print "Stack empty, cannot pop an item." and return.
  if(isEmpty()) cout << "Stack empty, cannot pop an item." << endl;
  //Otherwise delete the top most item from the stack
  else{
    Operand *temp;
    temp = stackHead;
    stackHead = temp -> next;
    delete temp;
    temp = nullptr;
  }
}

Operand* RPNCalculator :: peek()
{
  //If the stack is empty, print "Stack empty, cannot peek." and return NULL.
  if(isEmpty()) {
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
  //Otherwise, return a pointer to the top of the stack
  else return stackHead;
}

bool RPNCalculator :: compute(std::string symbol)
{
//   ➔ Perform the arithmetic operation symbol, which will be either “+” or “*”, on the top 2
// numbers in the stack. The return value indicates whether the operation was carried out
// successfully
// ➔ If symbol is not “+” or “*”, print "err: invalid operation" and return false
  if(symbol != "+" && symbol != "*")
  {
    cout << "err: invalid operation" << endl;
    return false;
  }
// ➔ Store the floats from the top two elements in the stack in local variables and pop them.
// ◆ Before getting each element, make sure that the stack is not empty. If it is empty,
// print “err: not enough operands” and return false
// ◆ If you pop the first element, and notice that the list is empty prior to getting the
// next element, print the error message, push the first element back to the stack,
// and return false
  if(isEmpty())
  {
    cout << "err: not enough operands" << endl;
    return false;
  }
  float num1 = getStackHead() -> number;
  pop();
  if(isEmpty()){
    cout << "err: not enough operands" << endl;
    push(num1);
    return false;
  }
  float num2 = getStackHead() -> number;
  pop();
// ➔ Perform the arithmetic operation symbol on those two elements and push the result to
// the stack
  float result;
  if(symbol == "+") result = num1 + num2;
  else result = num1 * num2;
  push(result);
  return true;
}
