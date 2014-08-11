/***********************************************************************
* Program:
*    Project 2, Calendar  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will ask for a month and a year, and display an
*    accurate calendar for the given date.
*
*    Estimated:  6.0 hrs   
*    Actual:     4.0 hrs
*      Displaying the calendar with the correct offset was tricky.
************************************************************************/

#include <iostream>
#include <iomanip>   //Used to set width for calendar.
using namespace std;

/***********************************************************************
* Functions get data from user.
************************************************************************/
int getMonth();
int getYear();

/***********************************************************************
* Functions compute data.
************************************************************************/
bool isLeap(int year);
int computeNumDays(int month, int year);
int computeOffset(int month, int year);

/***********************************************************************
* Functions display calendar.
************************************************************************/
void displayHeader(int month, int year);
void displayCalendar(int numDays, int offset);

/**********************************************************************
* main calls functions to get the month and year, compute the number
* of days in a month, and what day of the week the month starts on,
* and display the actual calendar.
***********************************************************************/
int main()
{
   // Ask for the month.
   int month = getMonth();
   // Ask for the year.
   int year = getYear();
   // Compute number of days in month
   int numDays = computeNumDays(month, year);
   // Compute offset, or day of the week month starts on.
   int offset = computeOffset(month, year);
   // Display the header.
   displayHeader(month, year);
   // Display the rest of the Calendar
   displayCalendar(numDays, offset);
   return 0;
}

/***********************************************************************
* Ask user for the month.
************************************************************************/
int getMonth()
{
   int month = 0;
   while (month < 1 || month > 12) // Keep asking until given a valid month
   {
      cout << "Enter a month number: "; // Prompt for month
      cin >> month;
      if (month < 1 || month > 12) // Inform user if month is invalid
      {
         cout << "Month must be between 1 and 12.\n";
      }
   }
   return month;
}

/***********************************************************************
* Ask user for the year.
************************************************************************/
int getYear()
{
   int year = 0;
   while (year < 1753) // Keep asking until valid year is given
   {
      cout << "Enter year: "; // Prompt for year
      cin >> year;
      if (year < 1753) // Inform if year is invalid.
      {
         cout << "Year must be 1753 or later.\n";
      }
   }
   return year;
}

/***********************************************************************
* Compute whether or not it's a leap year.
************************************************************************/
bool isLeap(int year)
{
   bool isLeap = false;
   if (((year % 4) == 0)        // year must be evenly divisible by 4
       && ((year % 100) != 0)   // but not by 100
       || ((year % 400) == 0))  // unless also evenly divisible by 400
   {
      isLeap = true;
   }
   return isLeap;
}

/***********************************************************************
* Compute the number of days in the given month.
************************************************************************/
int computeNumDays(int month, int year)
{
   int numDays = 0;
   if ((month == 1) || (month == 3) || (month == 5) || (month == 7)
       || (month == 8) || (month == 10) || (month == 12))
   {
      numDays = 31; // Months listed above always have 31 days in them
   }
   else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
   {
      numDays = 30; // These months always have 30 days in them
   }
   else if (month == 2)
   {
      if (isLeap(year) == true) // Determine if it's a leap year
      {
         numDays = 29;  
      }
      else  // February has 29 days if it's a leap year, otherwise 28
      {
         numDays = 28;
      }
   }
   return numDays;
}

/***********************************************************************
* Compute the day of the week month starts on.
************************************************************************/
int computeOffset(int month, int year)
{
   int offset = 0;
   int numDays = 0;
   int sumDays = 0;
   int years = (year - 1753);
   // Keep adding days in year, until sum of days since 1753 has been reached
   for (int yearNum = 0; yearNum < (year - 1753); yearNum++) 
   {
      // Determine whether each year is a leap year
      if (isLeap((1753 + yearNum)) == true)
      {
         numDays = 366;  // Leap years have an extra day
      }
      else
      {
         numDays = 365;
      }
      sumDays += numDays;
   }
   // Keep adding days in month, until sum of days since January is reached.
   for (int monthNum = 1; monthNum < month; monthNum++)
   {
      // Compute days in each month
      numDays = computeNumDays(monthNum, year);
      sumDays += numDays;
   }
   offset = (sumDays % 7); // Find day of the week or "offset"
   return offset;
}

/***********************************************************************
* Display the header.
************************************************************************/
void displayHeader(int month, int year)
{
   cout << endl;
   // Display month name, according to month number
   if (month == 1)
   {
      cout << "January";
   }
   if (month == 2)
   {
      cout << "February";
   }
   if (month == 3)
   {
      cout << "March";
   }
   if (month == 4)
   {
      cout << "April";
   }
   if (month == 5)
   {
      cout << "May";
   }
   if (month == 6)
   {
      cout << "June";
   }
   if (month == 7)
   {
      cout << "July";
   }
   if (month == 8)
   {
      cout << "August";
   }
   if (month == 9)
   {
      cout << "September";
   }
   if (month == 10)
   {
      cout << "October";
   }
   if (month == 11)
   {
      cout << "November";
   }
   if (month == 12)
   {
      cout << "December";
   }
   // Display year
   cout << ", " << year << endl;
   return;
}

/***********************************************************************
* Display the calendar.
************************************************************************/
void displayCalendar(int numDays, int offset)
{
   int dayNum = 1;
   cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";  // Show name of days
   if (offset == 6)
   {
      offset = -1; // So there isn't a blank line at the beginning
   }
   for (int spaces = offset; spaces >= 0; spaces--)
   {
      cout << "    "; // Create empty space before first day of month
   }
   for (int day = 1; day <= numDays; day++)
   {
      if (((offset + day) % 7) == 0)
      {
         if (offset != -1)
         {
            cout << endl; // Create a new line at the end of the week
         }
         else if (day != 1) // Don't do a new line at the beginning
         {
            cout << endl;
         }
      }
      cout << setw(4) << dayNum; // Display days
      dayNum++;
   }
   cout << endl; // Create a new line at end of calendar.
   return;
}
