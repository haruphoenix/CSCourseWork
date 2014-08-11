/***********************************************************************
* Program:
*    Assignment 41, Allocate a string  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will ask the user for the amount of space to allocate
*    for a string, will store the space, and then will ask for the string
*    and will display it.
*
*    Estimated:  4.0 hrs   
*    Actual:     2.0 hrs
*      The hardest part was trying to do this in several functions. I
*      finally gave up and did it in one function "allocate"
************************************************************************/

#include <iostream>
using namespace std;

int getNumItems();
void allocate(int numItems);

/**********************************************************************
* main calls functions to get the size of memory to allocate, allocate
* it, and store and display a string in it.
***********************************************************************/
int main()
{
   // Get the size
   int numItems = getNumItems();
   // Allocate space, store and display string
   allocate(numItems);
   return 0;
}

/**********************************************************************
* Get the size of memory to allocate
***********************************************************************/
int getNumItems()
{
   int numItems;
   // Get the size of the string
   cout << "Number of characters: ";
   cin >> numItems;
   // Ignore because cin.getline is used later.
   cin.ignore();
   return numItems;
}

/**********************************************************************
* Allocate memory, store and display a string
***********************************************************************/
void allocate(int numItems)
{
   // Try to allocate memory
   char *text = new(nothrow) char [numItems + 1];
   // Make sure there's enough room.
   if (!text)
   {
      cout << "Allocation failure!\n";
      return;
   }
   // Get the string
   cout << "Enter Text: ";
   cin.getline (text, numItems + 1);
   // Delete the string
   cout << "Text: " << text << endl;
   // Forget the address
   delete text;
   return;
}
