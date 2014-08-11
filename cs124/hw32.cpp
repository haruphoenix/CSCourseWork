/***********************************************************************
* Program:
*    Assignment 32, Prompt for 10 Grades revisited  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will prompt the user for 10 grades as percentages
*    and display the average grade. If the grade is a negative 1,
*    it won't be considered in the average.
*
*    Estimated:  2.0 hrs   
*    Actual:     0.1 hrs
*      Took a minute to remember I couldn't divide by zero.
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
   int count = 0;
   for (int i = 0; i < 10; i++)
   {
      if (grades[i] != -1)
      {
         sum += grades[i]; // Find sum of grades
      }
      else
      {
         count++;
      }
   }
   if (count == 10)
   {
      return -1; // Can't divide by 0, so needs to return before division
   }
   else
   {
   // Find average of non-(-1) grades
      average = (sum / (10.0 - count));
   }
   return average;
}

/**********************************************************************
* Display average grade
***********************************************************************/
void displayAverage(int average)
{
   if (average == -1)
   {
      cout << "Average Grade: " << "---" << "%\n";
   }
   else
   {
      cout << "Average Grade: " << average << "%\n";
   }
   return;
}
