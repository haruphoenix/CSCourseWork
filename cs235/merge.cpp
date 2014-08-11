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
#include <list>
using namespace std;

void mergeSort(list<int> &theList);
void split(list<int> &theList, list<int> &part1, list<int> &part2);
void merge(list<int> &theList, list<int> &part1, list<int> &part2);

/*****************************************************************************
* Opens a file, stores numbers into a list, sorts the list, and prints out
* the sorted list.
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
      int number;
      list<int> numbers;
      while (read >> number)                                // Read  numbers
         numbers.push_back(number);
      mergeSort(numbers);                                   // Sort  numbers
      list<int>::iterator i;
      for (i = numbers.begin(); i != numbers.end(); i++)    // Print numbers
         cout << *i << " ";
      cout << endl;
   }
   catch (int e)
   {
      cout << "Error: Must take exactly 2 argments\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   return 0;
}

/*****************************************************************************
* Sorts a list.  Input is the list to sort. (Passed by reference) No return.
******************************************************************************/
void mergeSort(list<int> &theList)
{
   list<int> part1;
   list<int> part2;
   while (true)
   {
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
void split(list<int> &theList, list<int> &part1, list<int> &part2)
{
   list<int>::iterator place;
   bool first = true;
   int  last = *theList.begin();
   // Whenever the next value is smaller than the previous, switch lists to
   // add to.
   for (place = theList.begin(); place != theList.end(); place++)
   {
      if (*place < last)
         first = !first;
      if (first)
         part1.push_back(*place);
      else
         part2.push_back(*place);
      last = *place;
   }
   return;
}

/*****************************************************************************
* Merges two lists together- Closer to being sorted. Inputs are the two list
* segments, as well as the main list. All are passed by reference. No return.
******************************************************************************/
void merge(list<int> &theList, list<int> &part1, list<int> &part2)
{
   theList.clear();

   list<int>::iterator place1 = part1.begin();
   list<int>::iterator place2 = part2.begin();

   int last1 = *place1;
   int last2 = *place2;
   // Take smaller of two values in list segments, add to main list.
   while ((place1 != part1.end()) || (place2 != part2.end()))
   {
      if (place1 == part1.end())
      {
         theList.push_back(*place2);
         place2++;
      }
      else if (place2 == part2.end())
      {
         theList.push_back(*place1);
         place1++;
      }
      else
      {
         if (*place1 < *place2)
         {
            theList.push_back(*place1);
            last1 = *place1;
            place1++;
         }
         else
         {
            theList.push_back(*place2);
            last2 = *place2;
            place2++;
         }
      }
   }
   part1.clear();
   part2.clear();
   return;
}
