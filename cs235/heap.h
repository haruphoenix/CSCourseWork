/*****************************************************************************
* Program:
*    Assignment 17, Heap Sort
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program reads in a file from the command line, it reads in numbers,
*    and prints them out in ascending order, sorted using a heap sort.
******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*****************************************************************************
* Heap class works like a priority queue, with the option of sorting and
* printing the heap.
******************************************************************************/
template <class T>
class Heap
{
   public:
      Heap();
      void setArray(T* theArray, int theSize);
      void setArray(vector<T> theArray);
      void sort();
      void push(T data);
      T    pop();
      void print();
      bool empty();
   private:
      vector<T> array;
      void heapify();
      void percolateDown(int r, int sortVal = -1);
      void percolateUp(int r);
};


/*****************************************************************************
* Constructor for Heap. Doesn't do anything
******************************************************************************/
template <class T>
Heap<T>::Heap()
{
   T ignore; // Value to be the zeroeth element. Not really used.
   array.push_back(ignore);
}

/*****************************************************************************
* Sets the heap equal to an array. Input is the array, and the size of the
* array.
******************************************************************************/
template <class T>
void Heap<T>::setArray(T* theArray, int theSize)
{
   array.clear();
   T ignore;
   array.push_back(ignore);
   for (int i = 0; i < theSize; i++)
      array.push_back(theArray[i]);
   heapify();
   return;
}

/*****************************************************************************
* Sets the heap equal to a vector. Input is the vector.
******************************************************************************/
template <class T>
void Heap<T>::setArray(vector<T> theArray)
{
   array.clear();
   T ignore;
   array.push_back(ignore);
   for (int i = 0; i < theArray.size(); i++)
      array.push_back(theArray[i]);
   heapify();
   return;
}

/*****************************************************************************
* Adds a value onto the heap. Value will percolate up to where it belongs.
******************************************************************************/
template <class T>
void Heap<T>::push(T data)
{
   array.push_back(data);
   percolateUp(array.size() - 1);
   return;
}

/*****************************************************************************
* Removes and returns the highest value on the heap.
******************************************************************************/
template <class T>
T Heap<T>::pop()
{
   T data;
   if (array.size() < 2)
      return data;
   data = array[1];
   array[1] = array[array.size() - 1];
   array.pop_back();
   percolateDown(1);
   return data;
}

/*****************************************************************************
* Sorts the heap from smallest to largest.
******************************************************************************/
template <class T>
void Heap<T>::sort()
{
   T swap;
   for (int i = array.size() - 1; i > 0; i--)
   {
      swap = array[i];
      array[i] = array[1];
      array[1] = swap;
      percolateDown(1, i);
   }
   return;
}

/*****************************************************************************
* Prints out the elements in the heap from the first to the last.
******************************************************************************/
template <class T>
void Heap<T>::print()
{
   for (int i = 1; i < array.size(); i++)
      cout << array[i] << " ";
   cout << endl;
}

/*****************************************************************************
* Turns an ordinary array or vector into a heap structure.
******************************************************************************/
template <class T>
void Heap<T>::heapify()
{
   for (int r = (array.size() / 2); r > 0; r--)
      percolateDown(r);
   return;
}

/*****************************************************************************
* Recursively causes a value to continue swapping down the "tree" or heap until
* it finds the place where it belongs. Inputs are the array index of the value
* to "settle", and the second value is only needed if sorting. It will be the
* index of the start of the "pruned" section of the tree/heap.
******************************************************************************/
template <class T>
void Heap<T>::percolateDown(int r, int sortVal)
{
   if (sortVal == -1)
      sortVal = array.size();
   int  swapLoc = r;
   bool swapped = false;
   
   if (r * 2 < sortVal)
      if (array[r * 2] > array[swapLoc])
      {
         swapLoc = r * 2;
         swapped = true;
      }
   if ((r * 2) + 1 < sortVal)
      if (array[(r * 2) + 1] > array[swapLoc])
      {
         swapLoc = (r * 2) + 1;
         swapped = true;
      }

   if (swapped)
   {
      T swapVal = array[r];
      array[r] = array[swapLoc];
      array[swapLoc] = swapVal;
      percolateDown(swapLoc, sortVal);
   }
   
   return;
}

/*****************************************************************************
* Swaps a value up the heap until it finds the place where it belongs. Input
* is the index to start percolating. Recursive.
******************************************************************************/
template <class T>
void Heap<T>::percolateUp(int r)
{
   if ((array[r] > array[r / 2]) && (r > 1))
   {
      T temp = array[r];
      array[r] = array[r / 2];
      array[r / 2] = temp;
      percolateUp(r / 2);
   }
   return;
}


/*****************************************************************************
* Returns true if the heap is empty. False if it is not empty
******************************************************************************/
template <class T>
bool Heap<T>::empty()
{
   if (array.size() < 2)
      return true;
   else
      return false;
}
