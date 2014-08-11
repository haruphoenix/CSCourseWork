/*******************************************************************
* Program:
*    Assignment 09, Node Class
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Description:
*    This program reads in a list of integers from a file, and puts
*    them into a linked list in ascending order.
*******************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#ifndef LIST_H

#define LIST_H

template <class T>
class LList;

/******************************************************************
* Node class contains a pointer, and data, along with getters
* and setters for each. Basic unit for a linked list
******************************************************************/
template <class T>
class Node
{
   public:
      friend class LList<T>; // For direct access in overloading []
      Node();
      Node(T theData);
      Node<T>* getNext();
      Node<T>* getPrev();
      T        getData();              
      void     setData(T item);        
      void     setNext(Node<T>* node);
      void     setPrev(Node<T>* node);

   private:
      T data;                         
      Node<T>* next;
      Node<T>* prev;
};

/******************************************************************
* Linked List class, contains all the functions for a fluid list,
* plus indexing for ease of use.
******************************************************************/
template <class T>
class LList
{
   public:
      LList();
      LList(const LList& original);
      ~LList();

      void insert(T item, int loc = -1);
      void remove(int loc = -1);

      Node<T>* position(int loc = 0);

      int  size();
      bool empty();
      void clear();
   
      T& operator [] (int index); // Directly access elements
      T& operator () ();          // Directly access current

      void setCurrent(int loc);   // set current to loc
      void operator ++ (int);     // increment current
      void operator -- (int);     // decrement current
   
      LList<T>& operator =  (const LList<T>& rtSide);
   
   private:
      Node<T>* head;
      Node<T>* current;
      Node<T>* last;
      int theSize;
};



/*******************************NODE*******************************/



/******************************************************************
* Constructor for Node. Sets next and previous pointers to NULL.
* Since template class, data is uninitialized.
******************************************************************/
template <class T>
Node<T>::Node()
{
   next = NULL;
   prev = NULL;
}

/******************************************************************
* Constructor for Node. Sets next and previous pointers to NULL.
* Sets parameter as data.
******************************************************************/
template <class T>
Node<T>::Node(T theData)
{
   data = theData;
   next = NULL;
   prev = NULL;
}

/******************************************************************
* Returns the node's pointer to the next. No input.
******************************************************************/
template <class T>
Node<T>* Node<T>::getNext()
{
   return next;
}

/******************************************************************
* Returns the node's pointer to the previous. No input.
******************************************************************/
template <class T>
Node<T>* Node<T>::getPrev()
{
   return prev;
}

/******************************************************************
* Returns the node's data. No input.
******************************************************************/
template <class T>
T Node<T>::getData()
{
   return data;
}

/******************************************************************
* Sets the node data to input value. No return.
******************************************************************/
template <class T>
void Node<T>::setData(T item)
{
   data = item;
   return;
}

/******************************************************************
* Sets the next node pointer to input pointer. No return.
******************************************************************/
template <class T>
void Node<T>::setNext(Node<T>* node)
{
   next = node;
   return;
}

/******************************************************************
* Sets the previous node pointer to input pointer. No return.
******************************************************************/
template <class T>
void Node<T>::setPrev(Node<T>* node)
{
   prev = node;
   return;
}


/*******************************LIST*******************************/



/******************************************************************
* Constructor for Linked List, initializes all pointers to NULL.
******************************************************************/
template <class T>
LList<T>::LList()
{
   theSize = 0;
   head = NULL;
   last = NULL;
   current = NULL;
}

/******************************************************************
* Copy constructor, makes a duplicate of linked list.
******************************************************************/
template <class T>
LList<T>::LList(const LList& original)
{
   theSize = 0;
   head = NULL;
   last = NULL;
   current = NULL;
   Node<T>* temp = original.head;
   for (int i = 0; i < original.theSize; i++)
   {
      insert(temp->getData());
      temp = temp->getNext();
   }
}

/******************************************************************
* Destructor, removes and deletes each node in the list.
******************************************************************/
template <class T>
LList<T>::~LList()
{
   clear();
}

/******************************************************************
* 
******************************************************************/
template <class T>
void LList<T>::insert(T item, int loc)
{
   Node<T>* newNode = new Node<T>;
   newNode->setData(item);
   
   if (loc != -1)
      current = position(loc);

   if (current == NULL)            // Empty or end of list
   {
      newNode->setPrev(last);
      if (last != NULL)
         last->setNext(newNode);
      else
         head = newNode;
      last = newNode;
   }
   else                            // Beginning or middle of list
   {
      newNode->setNext(current);
      newNode->setPrev(current->getPrev());
      if (newNode->getPrev() != NULL)
         newNode->getPrev()->setNext(newNode);
      else
         head = newNode;
      current->setPrev(newNode);
   }
   
   current = newNode->getNext();
   theSize++;
   
   return;
}

/******************************************************************
* 
******************************************************************/
template <class T>
void LList<T>::remove(int loc)
{
   if (theSize == 0)
      return;
      
   if ((loc < 0) || (loc >= theSize))
      loc = theSize - 1;

   Node<T>* node2Remove = position(loc);

   if (node2Remove->getPrev() != NULL)
      node2Remove->getPrev()->setNext(node2Remove->getNext());
   else
      head = node2Remove->getNext();
   
   if (node2Remove->getNext() != NULL)
      node2Remove->getNext()->setPrev(node2Remove->getPrev());
   else
      last = node2Remove->getPrev();

   delete node2Remove;
   theSize--;
   
   return;
}

/******************************************************************
* 
******************************************************************/
template <class T>
Node<T>* LList<T>::position(int loc)
{
   if (loc > theSize)
      loc = theSize;
   
   Node<T>* temp = head;
   
   for (int i = 0; i < loc; i++)
      temp = temp->getNext();
   
   return temp;
}

/******************************************************************
* Returns the size of the list.
******************************************************************/
template <class T>
int LList<T>::size()
{
   return theSize;
}

/******************************************************************
* Returns true if the list is empty. false otherwise
******************************************************************/
template <class T>
bool LList<T>::empty()
{
   if (theSize == 0)
      return true;
   else
      return false;
}

/******************************************************************
* Clears the list of all its nodes
******************************************************************/
template <class T>
void LList<T>::clear()
{
   while (theSize != 0)
      remove();
   head = NULL;
   last = NULL;
   current = NULL;
   return;
}

/******************************************************************
* Overloaded square brackets allow direct access to elements of
* the list. Input is the index, returns the address of the item
* contained by the node at that location.
******************************************************************/
template <class T>
T& LList<T>::operator [] (int index)
{
   return position(index)->data;
}

/******************************************************************
* Accesses the data of the current node pointer. Allows more
* efficient traversing through list when used with ++ and --
* operators.
******************************************************************/
template <class T>
T& LList<T>::operator () ()
{
   if (current != NULL)
      return current->data;
   else
      return position(theSize - 1)->data;
}

/******************************************************************
* Sets the current pointer location to given index location.
******************************************************************/
template <class T>
void LList<T>::setCurrent(int loc)
{
   current = position(loc);
   return;
}

/******************************************************************
* Increments current pointer forwards through the list. Loops
* back to the beginning when it basses the end.
******************************************************************/
template <class T>
void LList<T>::operator ++ (int)
{
   if (current != NULL)
      current = current->getNext();
   else
      current = head;
   return;
}

/******************************************************************
* Increments current pointer backwards through the list. Loops
* back to end when it passes the beginning.
******************************************************************/
template <class T>
void LList<T>::operator -- (int)
{
   if (current != NULL)
      current = current->getPrev();
   else
      current = last;
   return;
}


/******************************************************************
* Overloaded assignment operator replicates a list on the right
* side, and creates an identical list on the left side.
******************************************************************/
template <class T>
LList<T>& LList<T>::operator = (const LList<T>& rtSide)
{
   clear();
   Node<T>* temp = rtSide.head;
   for (int i = 0; i < rtSide.theSize; i++)
   {
      insert(temp->getData());
      temp = temp->getNext();
   }
   
   return *this;
}

#endif
