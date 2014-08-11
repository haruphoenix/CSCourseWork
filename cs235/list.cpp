/*******************************************************************
* Program:
*    Assignment 10, List Class
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    Implementation file for a linked list. Includes the functions
*    required to add or remove nodes, find the size of the list,
*    access elements of the list, etc.
*******************************************************************/
#include <iostream>
#include "list.h"
using namespace std;

/*******************************Node********************************/

/*******************************************************************
* Creates empty node
*******************************************************************/
Node::Node()                   
{
   data = 0;
   next = NULL;
}

/*******************************************************************
* Returns next pointer of a node
*******************************************************************/
Node* Node::getNext()
{
   return next;
}

/*******************************************************************
* Returns data of a node
*******************************************************************/
int Node::getData()
{
   return data;
}

/*******************************************************************
* Stores item in data member of current node
*******************************************************************/
void Node::setData(int item)
{
   data = item;
   return;
}

/*******************************************************************
* Sets next to point to node
*******************************************************************/
void Node::setNext(Node* node)
{
   next = node;
   return;
}

/*******************************LIST********************************/

/*******************************************************************
* Constructor. Sets size to zero, and the first node pointer to NULL
*******************************************************************/
List::List()
{
   numItems = 0;
   firstNode = NULL;
}

/*******************************************************************
* Destructor. Deletes all nodes in list
*******************************************************************/
List::~List()
{
   empty();
}

/*******************************************************************
* Copy constructor. Creates a copy of the list.
*******************************************************************/
List::List(const List &listToCopy)
{
   numItems = 0;
   firstNode = NULL;
   for (int i = 0; i < listToCopy.numItems; i++)
   {
      insert(listToCopy.getData(i), i);
   }
}

/*******************************************************************
* Assignment operator. Makes a copy of right side list, and assigns
* it to the left side. 
*******************************************************************/
List& List::operator = (const List &rightSide)
{
   empty();
   numItems = 0;
   firstNode = NULL;
   for (int i = 0; i < rightSide.numItems; i++)
   {
      insert(rightSide.getData(i), i);
   }
   return *this;
}

/*******************************************************************
* Inserts a node into the list. Parameters are the integer data,
* and the integer position of where in the list to insert.
*******************************************************************/
void List::insert(int item, int pos)
{

   if (pos > numItems)  // Insert at end
      pos = numItems;
   else if (pos < 0)    // Insert at beginning
      pos = 0;
   
   Node* newNode = new Node;
   newNode->setData(item);
   
   if (numItems == 0)
   {
      firstNode = newNode;
   }
   else if (pos == 0)
   {
      Node* temp = firstNode;
      firstNode = newNode;
      newNode->setNext(temp);
   }
   else
   {
      Node* tempA = firstNode;
      for (int i = 1; i < pos; i++)
      {
         tempA = tempA->getNext();
      }
      Node* tempB = tempA->getNext();
      tempA->setNext(newNode);
      newNode->setNext(tempB);
   }
   numItems++;
   return;
}

/*******************************************************************
* Removes a node from the list. Input is the position of the node
* to remove.
*******************************************************************/
void List::remove(int pos)
{
   if (numItems == 0)
      return;
   else if (pos >= numItems)
      pos = numItems - 1;
   else if (pos < 0)
      pos = 0;

   if (pos == 0)
   {
      Node* temp = firstNode;
      firstNode = temp->getNext();
      delete temp;
   }
   else
   {
      Node* temp = firstNode;
      for (int i = 1; i < pos; i++)
      {
         temp = temp->getNext();
      }
      Node* temp2 = temp->getNext();
      temp->setNext(temp2->getNext());
      delete temp2;
   }
   numItems--;
   
   return;
}

/*******************************************************************
* Looks through the list for a particular integer. Input is the
* integer to find. If found, it will return the position of the
* integer. If not found, it will return -1.
*******************************************************************/
int List::lookup(int item) const
{
   int index = 0;
   Node* search = firstNode;
   for (int i = 0; i < numItems; i++)
   {
      if (search->getData() == item)
         return i;
      else
         search = search->getNext();
   }
   return -1;
}

/*******************************************************************
* Returns the data at a given position. Input is the position to
* get data from.
*******************************************************************/
int List::getData(int pos) const
{
   if (numItems == 0)
      return 0;
   else if (pos >= numItems)
      pos = numItems - 1;
   else if (pos < 0)
      pos = 0;

   Node* temp = firstNode;
   for (int i = 0; i < pos; i++)
   {
      temp = temp->getNext();
   }
   return temp->getData();
}

/*******************************************************************
* This function returns 1 if the set is empty, and 0 if it is not 
*******************************************************************/
int List::empty(void) const
{
   if (numItems > 0)
      return 0;
   else
      return 1;
}

/*******************************************************************
* Returns the number of items in the list
*******************************************************************/
int List::getNumItems(void) const
{
   return numItems;
}

