/***********************************************************************
* Program:
*    Assignment 31, Prompt for 10 Grades  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will prompt the user for 10 grades as percentages
*    and display the average grade.
*
*    Estimated:  2.0 hrs   
*    Actual:     0.3 hrs
*      Although it says to use integers, bothers that average isn't accurate.
************************************************************************/

#include <iostream>
using namespace std;

void getGrades(int grades[10]);
int computeAverage(int grades[10]);
void displayAverage(int average);

/**********************************************************************
* Call functions to get grades, find average, and display the average.
***********************************************************************/
int main()
{
   int grades[10];
   int average;
   getGrades(grades);
   average = computeAverage(grades);
   displayAverage(average);
   return 0;
}

/**********************************************************************
* Get grades from user
***********************************************************************/
void getGrades(int grades[10])
{
   for (int i = 0; i < 10; i++)  // Ask for 10 grades
   {
      cout << "Grade " << i + 1 << ": "; // Increment grade number each time
      cin >> grades[i];
   }
   return;
}

/**********************************************************************
* Compute average grade
***********************************************************************/
int computeAverage(int grades[10])
{
   int sum = 0;
   int average;
   for (int i = 0; i < 10; i++)
   {
      sum += grades[i]; // Find sum of grades
   }
   average = (sum / 10.0); // Divide by number of grades to find average
   return average;
}

/**********************************************************************
* Display average grade
***********************************************************************/
void displayAverage(int average)
{
   cout << "Average Grade: " << average << "%\n";
   return;
}
