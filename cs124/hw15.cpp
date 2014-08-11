/***********************************************************************
* Program:
*    Assignment 15, Full Tithe Payer  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program calculates your tithing, and determines whether or
*    not you have paid in full. If you have paid in full, it will
*    inform you, otherwise will kindly admonish you with scripture.
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     0.4 hrs
*      It's hard to remember when to use = and ==.
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Main will ask user for income and tithing paid, calculate tithing
* owed, and display feedback regarding a full tithe.
***********************************************************************/
int main()
{
   float income;
   float tithingPaid;
   float tithingOwed;
   bool tithingMet;
   cout.precision(0);
   cout.setf(ios::fixed);
   cout << "Income: ";
   cin >> income;
   cout << "Tithe: ";
   cin >> tithingPaid;
   tithingOwed = (income * 0.1);
   tithingMet = (tithingOwed <= tithingPaid);
   if (tithingMet == true)
      cout << "You are a full tithe payer.\n";
   else
      cout << "Will a man rob God?  Yet ye have robbed me.\n"
           << "But ye say, Wherein have we robbed thee?\n"
           << "In tithes and offerings.  Malachi 3:8\n";  
   
   return 0;
}
