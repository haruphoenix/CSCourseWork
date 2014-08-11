/*******************************************************************
* Program:
*    Assignment 12, Fibonacci numbers
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Description:
*    This program reads from the command line an integer. It finds
*    that nth fibonacci number and prints it out
*******************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <math.h>
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

/********************************************************************
* This is a class of really big integers. It can add positive Big
* numbers. It uses a linked list full of ints to represent each
* of its segments.
********************************************************************/
class Big
{
   public:
      Big();
      Big(int number);
      Big(string number);
   
      int  segment(int seg);
      int  length();
   
      void setDigits(string number);
      void setDigits(int number);
   
      Big  operator +  (Big &number);
      void operator += (Big &number);
   
      Big& operator =  (int    number);
      Big& operator =  (string number);

      bool operator <  (Big &number);
      bool operator >  (Big &number);
      bool operator <= (Big &number);
      bool operator >= (Big &number);
      bool operator == (Big &number);
   
   private:
      LList<int> digits;
      int sToI(string number);
      void add(int number, int seg);
};

ostream& operator << (ostream& out, Big &number);

/******************************************************************
* Main calculates a fibonacci number given from the command line
******************************************************************/
int main(int argc, char** argv)
{
   try
   {
      if (argc < 2)
         throw argc;
      int num = atoi(argv[1]);
      Big fibonacci1(1);
      Big fibonacci2(1);
      for (int i = 2; i < num; i++)
      {
         if ((i % 2) == 1)
            fibonacci1 += fibonacci2;
         else
            fibonacci2 += fibonacci1;
      }
      if ((num % 2) == 0)
         cout << fibonacci1 << endl;
      else
         cout << fibonacci2 << endl;
   }
   catch (int e)
   {
      cout << e << " is too few arguments\n";
   }
   return 0;
}


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
* Inserts a new node into the linked list. First parameter is
* the item to insert, second parameter is the integer location
* of where to place the item. By default, if no second parameter
* is givin, it will insert it wherever the current location is at
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
* Removes a node at given location.
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
* Returns the address of the node at a given integer location.
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

/********************************************************************
* Displays a Big number.
********************************************************************/
ostream& operator << (ostream& out, Big &number)
{
   int size = number.length() - 1;
   for (int i = size; i >= 0; i--)
   {
      if (i != size)
         out << setfill('0') << setw(9);
      out << number.segment(i);
   }
   out << setfill(' ');
   if ((size == 0) && (number.segment(0) == 0))
      out << 0;
   return out;
}


/********************************BIG********************************/


/********************************************************************
* Initializes a big number with the value zero.
********************************************************************/
Big::Big()
{
   digits.insert(0);
}

/********************************************************************
* Initializes a big number with an integer input.
********************************************************************/
Big::Big(int number)
{
   digits.insert(number);
}

/********************************************************************
* Initializes a big number with a string input.
********************************************************************/
Big::Big(string number)
{
   setDigits(number);
}

/********************************************************************
* Returns the integer at a given segment. Input is the segment, 0
* for smallest segment, size - 1 for greatest segment.
********************************************************************/
int Big::segment(int seg)
{
   return digits[seg];
}

/********************************************************************
* Returns the number of segments (of nine) in number
********************************************************************/
int Big::length()
{
   return digits.size();
}

/********************************************************************
* Sets the number to input string number.
********************************************************************/
void Big::setDigits(string number)
{
   digits.clear();
   int size = number.size() - 1;
   string seg = "";
   for (int i = size; i >= 0; i--)
   {
      seg = number[i] + seg;
      if ((((size - i + 1) % 9) == 0) || (i == 0))
      {
         digits.insert(sToI(seg));
         seg = "";
      }
   }
   return;
}

/********************************************************************
* Sets the number to input integer.
********************************************************************/
void Big::setDigits(int number)
{
   digits.clear();
   digits.insert(number, 0);
   return;
}

/********************************************************************
* Adds left and right big numbers together and returns the result.
********************************************************************/
Big Big::operator + (Big &number)
{
   Big sum;
   sum.digits = digits;
   for (int i = 0; i < number.digits.size(); i++)
      sum.add(number.digits[i], i);
   return sum;
}

/********************************************************************
* Adds the right side big number parameter to the left side.
********************************************************************/
void Big::operator += (Big &number)
{
   for (int i = 0; i < number.digits.size(); i++)
      add(number.digits[i], i);
   return;
}

/********************************************************************
* Converts a string number into an integer. Returns the integer.
********************************************************************/
int Big::sToI(string number)
{
   int size = number.size() - 1;
   int num = 0;
   for (int i = size; i >= 0; i--)
      num += (((int)(number[i] - 48)) * pow(10, (size - i)));
   return num;
}

/********************************************************************
* Adds an integer to a segment of the big number. Carries the
* remainder to the next segment recursively. Input is the number
* to add, and the integer segment to begin adding to.
********************************************************************/
void Big::add(int number, int seg)
{
   if (seg >= digits.size())
      digits.insert(0, seg);
   int total = number + digits[seg];
   int remainder = total / 1000000000;
   digits[seg] = total % 1000000000;
   if (remainder != 0)
   {
      if (seg < digits.size() - 1)
         add(remainder, (seg + 1));
      else
         digits.insert(remainder, digits.size());
   }
   return; 
}

/********************************************************************
* Sets a big number equal to an integer.
********************************************************************/
Big& Big::operator = (int number)
{
   digits.clear();
   digits.insert(number);
   return *this;
}

/********************************************************************
* Sets a big number equal to a string number
********************************************************************/
Big& Big::operator = (string number)
{
   setDigits(number);
   return *this;
}

/********************************************************************
* Compares two big numbers. Returns true if left side operand
* is less than the right side operand, false otherwise.
********************************************************************/
bool Big::operator < (Big &number)
{
   bool isLess = false;
   if (digits.size() < number.digits.size())
      isLess = true;
   else if (digits.size() == number.digits.size())
   {
      for (int i = digits.size() - 1; i >= 0; i--)
      {
         if (digits[i] < number.digits[i])
         {
            isLess = true;
            break;
         }
         else if (digits[i] != number.digits[i])
            break;
      }
   }
      
   return isLess;
}

/********************************************************************
* Compares two big numbers. Returns true if left side operand
* is bigger than the right side operand, false otherwise.
********************************************************************/
bool Big::operator > (Big &number)
{
      bool isGreater = false;
   if (digits.size() > number.digits.size())
      isGreater = true;
   else if (digits.size() == number.digits.size())
   {
      for (int i = digits.size() - 1; i >= 0; i--)
      {
         if (digits[i] > number.digits[i])
         {
            isGreater = true;
            break;
         }
         else if (digits[i] != number.digits[i])
            break;
      }
   }
      
   return isGreater;
}

/********************************************************************
* Compares two big numbers. Returns true if left side operand
* is less than or equal to the right side operand, false otherwise.
********************************************************************/
bool Big::operator <= (Big &number)
{
   return !(*this > number);
}

/********************************************************************
* Compares two big numbers. Returns true if left side operand
* is bigger than or equal to the right side operand, false otherwise.
********************************************************************/
bool Big::operator >= (Big &number)
{
   return !(*this < number);
}

/********************************************************************
* Compares two big numbers. Returns true if left side operand
* is equal to the right side operand, false otherwise.
********************************************************************/
bool Big::operator == (Big &number)
{
   bool isEqual = false;
   if (digits.size() == number.digits.size())
   {
      isEqual = true;
      for (int i = 0; i < digits.size(); i++)
         if (digits[i] != number.digits[i])
            isEqual = false;
   }
   return isEqual;
}
