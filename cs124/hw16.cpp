/***********************************************************************
* Program:
*    Assignment 16, Compute Tax   
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program asks for your income, calculates your tax based
*    on different tax brackets, and displays your calculated tax.
*    
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     3.0 hrs
*      It was so hard to figure out how to properly call a function.
************************************************************************/

#include <iostream>
using namespace std;

float computeTax(float income);

/**********************************************************************
*Main will ask for income, and display the tax.
***********************************************************************/
int main()
{
   cout.setf(ios::fixed);
   cout.precision(0);
   float income;
   float tax;
   cout << "Income: ";
   cin >> income;
   tax = computeTax(income);
   cout << tax << endl;
   return 0;
}

/**********************************************************************
* computeTax will determine the tax bracket and compute the tax for
* the given income declared in main.
***********************************************************************/
float computeTax(float income)
{
   float tax;
   if (income == 0.00)
   {
      tax = 0.00;
   }
   else if (income <= 15200.00)
   {
      tax = (income * 0.10);
   }
   else if (income <= 61300.00)
   {
      tax = (income * 0.15);
   }
   else if (income <= 123700.00)
   {
      tax = (income * 0.25);
   }
   else if (income <= 188450.00)
   {
      tax = (income * 0.28);
   }
   else if (income <= 336550.00)
   {
      tax = (income * 0.33);
   }
   else
   {
      tax = (income * 0.35);
   }
   return tax;
}
