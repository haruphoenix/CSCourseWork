/************************************************************
* Program:
*    Assignment 02, Stack Class
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This is the implementation file for a stack class. A
*    stack is a container that allows for first in, last out
*    or last in, first out.  It uses the primary functions
*    push, pop, and top.
************************************************************/
#include "stack.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef STACK_I
#define STACK_I

/************************************************************
* Constructor - Requires the size of the stack as a parameter
************************************************************/
Stack::Stack(int size)
{
   stackItems = new int[size];
   maxSize = size;
   myTop = 0;
}

/************************************************************
* Copy constructor. Creates an exact replica of a stack
************************************************************/
Stack::Stack(const Stack &aStack)
{
   maxSize = aStack.maxSize;
   stackItems = new int[maxSize];
   myTop = 0;
   for (int i = 0; i < aStack.myTop; i++)
   {
      push(aStack.stackItems[i]);
   }
}

/************************************************************
* Returns the last integer pushed onto the stack.
* If the stack is empty, returns 0. No parameters.
************************************************************/
int Stack::top(void)
{
   if (myTop > 0)
      return (stackItems[myTop - 1]);
   else
      return 0;
}

/************************************************************
* Pushes an integer onto the stack. The integer to push onto
* the stack is the parameter. If the stack is full. It will
* display an error, and end the program.
************************************************************/
void Stack::push(int item)
{
   if (!full())
   {
      stackItems[myTop] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(EXIT_FAILURE);
   }
}

/************************************************************
* Removes an integer from the top of the stack. Has no
* parameters or return. If the stack is empty, it will
* display an error, and end the program.
************************************************************/
void Stack::pop(void)
{
   if (!empty())
   {
      myTop--;
   }
   else
   {
      cout << "ERROR: Stack Underflow\n";
      exit(EXIT_FAILURE);
   }
}

/************************************************************
* This function tells if the stack is empty or not. Returns
* true for empty, false for not empty.
************************************************************/
bool Stack::empty(void)
{
   bool isEmpty = false;
   if (myTop <= 0)
      isEmpty = true;
   return isEmpty;
}

/************************************************************
* This function tells if the stack is full or not. Returns
* true for full, false for not.
************************************************************/
bool Stack::full(void)
{
   bool isFull = false;
   if (myTop > (maxSize - 1))
      isFull = true;
   return isFull;
}

/************************************************************
* Destructor - Deletes the dynamically allocated array.
************************************************************/
Stack::~Stack()
{
   delete [] stackItems;
}

/************************************************************
* Assignment operator - Creates an exact replica of right
* operand
************************************************************/
Stack& Stack::operator = (const Stack &rtSide)
{
   delete [] stackItems;
   maxSize = rtSide.maxSize;
   stackItems = new int[maxSize];
   myTop = 0;
   for (int i = 0; i < rtSide.myTop; i++)
   {
      push(rtSide.stackItems[i]);
   }
   myTop = rtSide.myTop;
   return *this;
}

#endif
