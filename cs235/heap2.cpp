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

class Heap
{
   public:
      Heap();
      void setArray(int* theArray, int theSize);
      void setArray(vector<int> theArray);
      void sort();
      void push(int data);
      int  pop();
      void print();
   private:
      vector<int> array;
      void heapify();
      void percolateDown(int r, int sortVal = -1);
      void percolateUp(int r);
};

/*****************************************************************************
* main description
******************************************************************************/
int main(int argc, char** argv)
{
   try
   {
      if (argc != 2)
         throw argc;
      ifstream read;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      vector<int> numbers;
      int number;
      while (read >> number)
         numbers.push_back(number);
      Heap myHeap;
      myHeap.setArray(numbers);
      myHeap.sort();
      myHeap.print();
   }
   catch (int e)
   {
      cout << "Error: Must take two arguments\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   
   return 0;
}

Heap::Heap()
{
}

void Heap::setArray(int* theArray, int theSize)
{
   int ignore;
   array.push_back(ignore);
   for (int i = 0; i < theSize; i++)
      array.push_back(theArray[i]);
   heapify();
   return;
}

void Heap::setArray(vector<int> theArray)
{
   int ignore;
   array.push_back(ignore);
   for (int i = 0; i < theArray.size(); i++)
      array.push_back(theArray[i]);
   heapify();
   return;
}

void Heap::push(int data)
{
   array.push_back(data);
   percolateUp(array.size() - 1);
   return;
}

int Heap::pop()
{
   if (array.size() < 2)
      return -1;
   int data = array[1];
   array[1] = array[array.size() - 1];
   array.pop_back();
   percolateDown(1);
   return data;
}

void Heap::sort()
{
   int swap;
   for (int i = array.size() - 1; i > 0; i--)
   {
      swap = array[i];
      array[i] = array[1];
      array[1] = swap;
      percolateDown(1, i);
   }
   return;
}

void Heap::print()
{
   for (int i = 1; i < array.size(); i++)
   {
      cout << array[i];
      if (i != array.size())
         cout << " ";
   }
   cout << endl;
}

void Heap::heapify()
{
   for (int r = (array.size() / 2); r > 0; r--)
      percolateDown(r);
   return;
}

void Heap::percolateDown(int r, int sortVal)
{
   if (sortVal == -1)
      sortVal = array.size();
   int  greater;
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
      int swapVal = array[r];
      array[r] = array[swapLoc];
      array[swapLoc] = swapVal;
      percolateDown(swapLoc, sortVal);
   }
   
   return;
}

void Heap::percolateUp(int r)
{
   if ((array[r] > array[r / 2]) && (r > 1))
   {
      int temp = array[r];
      array[r] = array[r / 2];
      array[r / 2] = temp;
      percolateUp(r / 2);
   }
   return;
}
