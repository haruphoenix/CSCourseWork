/***********************************************************************
* Program:
*    Assignment 25, Display Table 
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program asks for the number of days in a month and the offset
*    of where the first day starts, and then creates a calendar.
*
*    Estimated:  2.0 hrs   
*    Actual:     5.0 hrs
*      Figuring out how to put in the offset right was a challenge.
************************************************************************/

#include <iostream>
using namespace std;

int getNumDays();
int getOffset();
void displayTable(int numDays, int offset);

/**********************************************************************
* main calls functions to get number of days, get the offset
* and display the table
***********************************************************************/
int main()
{
   int numDays = getNumDays();
   int offset = getOffset();
   displayTable(numDays, offset);
   return 0;
}

/*********************************************************************
* gets number of days in month from user
**********************************************************************/
int getNumDays()
{
   int numDays = 0;
   while ((numDays < 28) || (numDays > 31))
   {
      cout << "Number of days: ";
      cin >> numDays;
      // Make sure input is valid
      if ((numDays < 28) || (numDays > 31))
      {
         cout << "Please enter a number between 28 & 31." << endl;
      }
   }
   return numDays;
}

/*********************************************************************
* gets offset from user
**********************************************************************/
int getOffset()
{
   int offset = 9;
   while ((offset < 0) || (offset > 6))
   {
      cout << "Offset: ";
      cin >> offset;
      // Make sure input is valid
      if ((offset < 0) || (offset > 6))
      {
         cout << "Please enter a number between 0 & 6." << endl;
      }
   }
   return offset;
}

/*********************************************************************
* calculates and displays calendar
**********************************************************************/
void displayTable(int numDays, int offset)
{
   int dayOfWeek = 0;
   int daysInMonth;
   cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";
   if (offset == 6) 
   {
      offset = -1; //So there are no spaces with offset = 6
   }
   for (int spaces = offset; spaces > -1; spaces--)
   {
      cout << "    ";
   }
   for (daysInMonth = 1; daysInMonth <= numDays; daysInMonth++)
   {
      int dayOfWeek = ((offset + daysInMonth) % 7);
      if (dayOfWeek == 0)
      {
         if (daysInMonth > 1)
         {
            cout << "\n";
         }
         if (daysInMonth < 10)
         {
            cout << " ";
         }
         cout << "  " << daysInMonth;
      }
      else
      {
         if (daysInMonth < 10)
         {
            cout << " "; //spacing correction for numbers less than ten.
         }
         cout << "  " << daysInMonth;
      }
   }
   cout << endl;
}
