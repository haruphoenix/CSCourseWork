/***********************************************************************
* Program:
*    Assignment 12, Prompt for Income
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program is meant to first prompt for someone's income.
*    and then redisplay it.
*  
*   
*  
*
*    Estimated:  1.0 hrs   
*    Actual:     1.1 hrs
*      The hardest part was remembering to add decimal places.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
* Asks for monthly income,
* then displays it.
***********************************************************************/
int main()
{
   float income;
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   cout << "\tYour monthly income: ";
   cin >> income;
   cout << "Your income is: $" << setw(9) << income << "\n";
   return 0;
}
