/***********************************************************************
* Program:
*    Assignment 11, Display Budget  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program is meant to display a budget on the screen.
*
*    Estimated:  1.0 hrs   
*    Actual:     4.0 hrs
*      Hard finding out how to line up $ signs, and how to fix style.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

/***********************************************************************
* This program will display the budge
************************************************************************/
int main()
{
   cout.precision(2);
   cout.setf(ios::showpoint);
   cout.setf(ios::fixed);
   cout << "\tItem" << setw(21) << "Projected\n";
   cout << "\t=============" << setw(13) << "==========\n";
   cout << "\tIncome" << setw(10) << "$" << setw(9) << 1000.00 << endl;
   cout << "\tTaxes" << setw(11) << "$" << setw(9) << 100.00 << endl;
   cout << "\tTithing" << setw(9) << "$" << setw(9) << 100.00 << endl;
   cout << "\tLiving" << setw(10) << "$" << setw(9) << 650.00 << endl;
   cout << "\tOther" << setw(11) << "$" << setw(9) << 90.00 << endl;
   cout << "\t=============" << setw(13) << "==========\n";
   cout << "\tDelta" << setw(11) << "$" << setw(9) << 60.00 << endl;
   return 0;
}
