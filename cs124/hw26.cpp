/***********************************************************************
* Program:
*    Assignment 26, Read 10 Grades  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will open a file, read 10 grades, and then display
*    the average.
*
*    Estimated:  2.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void getFileName(char fileName[]);
float readFile(char fileName[]);
void display(float average);

/**********************************************************************
* main calls for the filename, calls the average, and sends it
* to be displayed.
***********************************************************************/
int main()
{
   char fileName[256];
   getFileName(fileName);
   float average = readFile(fileName);
   if (average != 0)
   {
   display(average);
   }
   return 0;
}

/**********************************************************************
* Gets the name of the file to read.
***********************************************************************/
void getFileName(char fileName[])
{
   cout << "Please enter the filename: "; 
   cin >> fileName;
   return;
}

/**********************************************************************
* Reads the file.
***********************************************************************/
float readFile(char fileName[])
{
   ifstream fin;
   float number;
   float sum = 0;
   int x;
   fin.open(fileName);
   if (fin.fail())
   {
      cout << "Error reading file \"" << fileName << "\"\n";
      return 0;
   }
   for (x = 1; x <= 10; x++)
   {
      fin >> number;
      if (fin.fail())
      {
         cout << "Error reading file \"" << fileName << "\"\n";
         return 0;
      }
      sum += number;
   }
   fin.close();
   return (sum / 10);
}

/**********************************************************************
* Displays the average value.
***********************************************************************/
void display(float average)
{
   cout.precision(0);
   cout.setf(ios::fixed);
   cout << "Average Grade: " << average << "%\n";
   return;
}


