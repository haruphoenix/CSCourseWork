/***********************************************************************
* Program:
*    Assignment 23, Sum the Multiples  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program asks for a number and then adds up all the multiples
*    of that number up to 100.
*    
*    
*    
*
*    Estimated:  1.5 hrs   
*    Actual:     1.0 hrs
*      Was hard finding out how to stop a loop midway once a value changed
************************************************************************/

#include <iostream>
using namespace std;

int getMultiple();
int calculateSum(int multiple);
void displaySum(int multiple, int sum);

/**********************************************************************
* main calls functions to get number to find the sum of
* the multiples, and display the sum.
***********************************************************************/
int main()
{
   int multiple = getMultiple();
   int sum = calculateSum(multiple);
   displaySum(multiple, sum);
   return 0;
}

/**********************************************************************
* Prompt user for multiple
***********************************************************************/
int getMultiple()
{
   int multiple;
   cout << "What multiples are we adding? ";
   cin >> multiple;
   return multiple;
}

/**********************************************************************
* Calculate the sum of the multiples
***********************************************************************/
int calculateSum(int multiple)
{
   int count = 0;
   int x = 0;
   int sum = 0;
   while (count < 100)
   {
      count = (multiple * x);
      // So we don't include the last multiple that puts it over 100.
      if (count < 100)
      {
         sum = (sum + count);
      }
      // Increment the number multiple is multiplied by.
      x++;
   }
   return sum;
}

/**********************************************************************
* Display sum of the multiples under 100
***********************************************************************/
void displaySum(int multiple, int sum)
{
   cout << "The sum of multiples of " << multiple << " less than 100 are: "
        << sum << endl;
   return;
}
