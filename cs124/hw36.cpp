/***********************************************************************
* Program:
*    Assignment 36, Letter Grade from Number Grade. 
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will use switch operators and conditional expressions
*    to determine the letter grade, and sign for a given number grade.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.7 hrs
*      Finding out how to use conditional expressions was tricky.
************************************************************************/

#include <iostream>
using namespace std;

char computeGradeLetter(int grade);
char computeGradeSign(int grade);

/**********************************************************************
* Main prompts the user for a number grade and displays the letter
* grade
***********************************************************************/
int main()
{
   int grade;
   char letterGrade;
   char sign = '\0';
   // Get the percentage
   cout << "Enter number grade: ";
   cin >> grade;
   // Compute the letter grade
   letterGrade = computeGradeLetter(grade);
   // Compute the letter sign
   sign = (grade >= 60) ? computeGradeSign(grade) : sign;
   sign = (grade > 92) ? '\0' : sign;
   // Display the letter grade and sign
   cout << grade << "% is " << letterGrade;
   if (sign != '\0')
   {
      cout << sign;
   }
   cout << endl;
   return 0;
}

/**********************************************************************
* Determines the letter grade based off of percentage
***********************************************************************/
char computeGradeLetter(int grade)
{
   char letterGrade;
   switch (grade / 10)
   {
      case 10:
      case 9:
         letterGrade = 'A';
         break;
      case 8:
         letterGrade = 'B';
         break;
      case 7:
         letterGrade = 'C';
         break;
      case 6:
         letterGrade = 'D';
         break;
      default:
         letterGrade = 'F';
   }
   return letterGrade;
}

/**********************************************************************
* Determines whether or not a grade has a + or - sign
***********************************************************************/
char computeGradeSign(int grade)
{
   char sign;
   switch (grade % 10)
   {
      case 0:
         sign = '-';
         break;
      case 1:
         sign = '-';
         break;
      case 2:
         sign = '-';
         break;
      case 7:
         sign = '+';
         break;
      case 8:
         sign = '+';
         break;
      case 9:
         sign = '+';
         break;
      default:
         sign = '\0';
   }
   return sign;
}
