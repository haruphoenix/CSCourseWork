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
      Node<T>* getNext();              
      T        getData();              
      void     setData(T item);        
      void     setNext(Node<T>* node); 

   private:
      T data;                         
      Node<T>* next;
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
   
      void insert(T item, Node<T>* loc = NULL); // Current default
      void insert(T item, int loc);     // inserts after index loc
      void headInsert(T item);
      void backInsert(T item);
   
      void setCurrent(int index);       // Set current loc to index
      void setCurrent(Node<T>* loc);    // Set current loc to ptr
      int  size();
      bool isEmpty();
   
      int      position(Node<T>* loc);  // Returns index of ptr
      Node<T>* position(int pos);       // Returns ptr from index
      T& operator []   (int index);     // Directly access elements

      LList<T>& operator =  (const LList<T>& rtSide);
      LList<T>& operator += (const LList<T>& rtSide);
      LList<T>  operator +  (const LList<T>& rtSide);
   
      void remove(Node<T>* loc = NULL);
      void empty();
   
   private:
      Node<T>* head;
      Node<T>* current;
      Node<T>* last;
      int theSize;
};

/*******************************NODE*******************************/



/******************************************************************
* Constructor for Node. Sets next pointer to NULL. Since template
* class, data is uninitialized.
******************************************************************/
template <class T>
Node<T>::Node()
{
   next = NULL;
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
* Sets the node pointer to input pointer. No return.
******************************************************************/
template <class T>
void Node<T>::setNext(Node<T>* node)
{
   next = node;
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
   for (int i = 0; i < original.theSize; i++)
   {
      insert(original[i]);
   }
}

/******************************************************************
* Destructor, removes and deletes each node in the list.
******************************************************************/
template <class T>
LList<T>::~LList()
{
   while (theSize != 0)
   {
      remove();
   }
}

/******************************************************************
* Inserts an item into the linked list, Inputs are the item to
* insert, and the index location of the list to add the item after.
******************************************************************/
template <class T>
void LList<T>::insert(T item, int loc)
{
   insert(item, position(loc));
   return;
}

/******************************************************************
* Inserts an item at the back of a linked list. Input is the item
* to insert.
******************************************************************/
template <class T>
void LList<T>::backInsert(T item)
{
   insert(item, last);
   return;
}

/******************************************************************
* Inserts an item at the front of a linked list. This function
* must be used to insert at the very front. Inserting at index
* 0 will insert one after the first in the list. Input is the item
* to insert.
******************************************************************/
template <class T>
void LList<T>::headInsert(T item)
{
   Node<T>* newNode = new Node<T>;
   newNode->setData(item);
   newNode->setNext(head);
   head = newNode;
   current = newNode;
   if (theSize == 0)
      last = newNode;
   theSize++;
   return;
}

/******************************************************************
* Inserts an item at a specific location in the list. Inputs are
* the item to insert, and the pointer location of where to insert
* after.  This pointer will by default insert at where the current
* location pointer is pointing to. If for some reason that pointer
* is null, it will insert at the end of the list. The current
* pointer will then point to the last created node.
******************************************************************/
template <class T>
void LList<T>::insert(T item, Node<T>* loc)
{
   if (theSize == 0) // Insert at front of list, if only element
   {
      headInsert(item);
      return;
   }
   
   if (loc == NULL)  // Order of default insertion priority
      loc = current;
   if (loc == NULL)
      loc = last;
   if (loc == NULL)
      loc = head;
   
   try
   {
      Node<T>* newNode = new (nothrow) Node<T>;
      if (newNode == NULL)
         throw 0;
      
      newNode->setData(item);       // Set and add node
      current = loc->getNext();
      loc->setNext(newNode);
      newNode->setNext(current);
      current = newNode;
      
      if (newNode->getNext() == NULL)
         last = newNode;

      theSize++;                    // Increment size of list
   }
   catch (int e)
   {
      cout << "Error in void LList<T>"
           << "::insert(T item, Node<T>* loc)\n";
   }
   return;
}

/******************************************************************
* Removes a node from the list. Input is the pointer location of
* the node to remove. By default the node to be removed will be
* the one the current pointer is pointing to. If that happens to
* be NULL, it will remove the last node in the list. Current will
* then point to the node before the one deleted.
******************************************************************/
template <class T>
void LList<T>::remove(Node<T>* loc)
{
   if (loc == NULL)    // Order of deletion priority
      loc = current;
   if (current == NULL)
      loc = last;
   if (last == NULL)
      return;

   if (loc != head)        // Remove node
   {
      current = position(position(loc) - 1);
      current->setNext(loc->getNext());
      if (last == loc)
         last = current;
      delete loc;
      if (theSize == 1)
         head = current;
   }
   else
   {
      if (theSize == 1)
      {
         delete loc;
         head = NULL;
         last = NULL;
         current = NULL;
      }
      else
      {
         head = loc->getNext();
         current = head;
         delete loc;
      }
   }
   theSize--;            // Decrement size
      
   return;
}

/******************************************************************
* Sets the current pointer to a given index. The input is the
* integer index to point to.
******************************************************************/
template <class T>
void LList<T>::setCurrent(int index)
{
   current = position(index);
   return;
}

/******************************************************************
* Sets the current pointer to a given location. The input is the
* pointer location to point to.
******************************************************************/
template <class T>
void LList<T>::setCurrent(Node<T>* loc)
{
   current = loc;
   return;
}

/******************************************************************
* Returns the size of the list. No inputs
******************************************************************/
template <class T>
int LList<T>::size()
{
   return theSize;
}

/******************************************************************
* Returns true if the list is empty, false if it is not
******************************************************************/
template <class T>
bool LList<T>::isEmpty()
{
   if (theSize < 1)
      return true;
   else
      return false;
}

/******************************************************************
* This function accepts a pointer, and searches through the list
* for that pointer. If found, it will return the index location
* of that pointer, if not found, it will return the index of the
* last element in the list.
******************************************************************/
template <class T>
int LList<T>::position(Node<T>* loc)
{
   int index = 0;
   current = head;
   for (int i = 0; i < theSize; i++)
   {
      if (current == loc)
      {
         index = i;
         break;
      }
      else
      {
         current = current->getNext();
      }
   }
   return index;
}

/******************************************************************
* This function requires and integer index as a parameter, and
* returns a pointer to that position in the list. If the position
* is out of range, it will return the pointer to the last element
* in the list.
******************************************************************/
template <class T>
Node<T>* LList<T>::position(int pos)
{
   if (pos >= theSize)
      pos = (theSize - 1);
   current = head;
   for (int i = 0; i < pos; i++)
      current = current->getNext();
   return current;
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
* Overloaded assignment operator replicates a list on the right
* side, and creates an identical list on the left side.
******************************************************************/
template <class T>
LList<T>& LList<T>::operator = (const LList<T>& rtSide)
{
   empty();
   for (int i = 0; i < rtSide.theSize; i++)
   {
      insert(rtSide[i]);
   }
   
   return *this;
}

/******************************************************************
* Appends the list with elements from the right side operand.
******************************************************************/
template <class T>
LList<T>& LList<T>::operator += (const LList<T>& rtSide)
{
   for (int i = 0; i < rtSide.theSize; i++)
   {
      backInsert(rtSide[i]);
   }
   return *this;
}

/******************************************************************
* Returns a list with the elements of the left side operand,
* appended with elements of the right side operand
******************************************************************/
template <class T>
LList<T> LList<T>::operator + (const LList<T>& rtSide)
{
   LList<T> newList;
   for (int i = 0; i < theSize; i++)
   {
      newList.insert(position(i)->getData());
   }
   for (int i = 0; i < rtSide.theSide; i++)
   {
      newList.insert(rtSide[i]);
   }
   return newList;
}

/******************************************************************
* Removes all nodes from the list.
******************************************************************/
template <class T>
void LList<T>::empty()
{
   while (theSize != 0)
      remove();
   return;
}
