/*****************************************************************************
* Program:
*    Assignment 18, Merge Sort
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    Reads in a file of numbers, and sorts them using a merge sort.
******************************************************************************/
#include <iostream>
#include <fstream>
#include "dllist.cpp"
using namespace std;

template <class T>
void mergeSort(LList<T> &theList);
template <class T>
void split(LList<T> &theList, LList<T> &part1, LList<T> &part2);
template <class T>
void merge(LList<T> &theList, LList<T> &part1, LList<T> &part2);


/*****************************************************************************
* Sorts a list.  Input is the list to sort. (Passed by reference) No return.
******************************************************************************/
template <class T>
void mergeSort(LList<T> &theList)
{
   LList<T> part1;
   LList<T> part2;
   while (true)
   {
      cout << "part1: " << part1.size() << endl;
      cout << "part2: " << part2.size() << endl;
      
      split(theList, part1, part2);
      if (part1.empty() || part2.empty()) // Break as soon as one of the
         break;                           // segments is empty meaning it's
      merge(theList, part1, part2);       // sorted
   }
   return;
}

/*****************************************************************************
* Splits a list in two. Input is the list to split, as well as the two lists
* to split the list into. All are passed by reference. No return.
******************************************************************************/
template <class T>
void split(LList<T> &theList, LList<T> &part1, LList<T> &part2)
{
   bool first = true;
   T  last = theList[0];
   // Whenever the next value is smaller than the previous, switch lists to
   // add to.
   for (int i = 0; i < theList.size(); i++)
   {
      if (theList() < last)
         first = !first;
      if (first)
         part1.insert(theList());
      else
         part2.insert(theList());
      last = theList();
      theList++;
   }
   return;
}

/*****************************************************************************
* Merges two lists together- Closer to being sorted. Inputs are the two list
* segments, as well as the main list. All are passed by reference. No return.
******************************************************************************/
template <class T>
void merge(LList<T> &theList, LList<T> &part1, LList<T> &part2)
{
   theList.clear();

   int i = 0;
   int j = 0;

   T last1 = part1[0];
   T last2 = part2[0];
   // Take smaller of two values in list segments, add to main list.
   while ((i < part1.size()) || (j < part2.size()))
   {
      if (i >= part1.size())
      {
         theList.insert(part2());
         part2++;
         j++;
      }
      else if (j >= part2.size())
      {
         theList.insert(part1());
         part1++;
         i++;
      }
      else
      {
         if (part1() < part2())
         {
            theList.insert(part1());
            last1 = part1();
            part1++;
            i++;
         }
         else
         {
            theList.insert(part2());
            last2 = part2();
            part2++;
            j++;
         }
      }
   }
   part1.clear();
   part2.clear();
   return;
}
