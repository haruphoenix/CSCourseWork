/***********************************************************
* Program:
*    Test 1, Converting $ to E
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program is meant to convert U.S. dollars into
*    euros.
************************************************************/
#include <iostream>
using namespace std;

float getDollars();
float convertEuro(float dollars);
void displayEuro(float euros);

/***********************************************************
* main calls functions to receive dollars from user, convert
* dollars into euros, and then display the result back to
* the user.
************************************************************/
int main()
{
   float dollars = getDollars();
   float euros = convertEuro(dollars);
   displayEuro(euros);
   return 0;
}

/***********************************************************
* getDollars asks user for amount in U.S Dollars.
*************************************************************/
float getDollars()
{
   float dollars;
   cout << "Please enter the amount in US Dollars: $";
   cin >> dollars;
   return dollars;
}

/******************************************************************
* convertEuro will make the actual calculation from Dollars to Euros.
*******************************************************************/
float convertEuro(float dollars)
{
   float euros = (dollars / 1.41);
   return euros;
}

/******************************************************************
* displayEuro gives the computed amount in Euros back to the user.
*******************************************************************/
void displayEuro(float euros)
{
// set numerical formatting.
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
// decide whether or not amount is negative and should have parentheses.
   if (euros < 0)
   {
      cout << "\tEuros: (" << euros << ")\n";
   }
   else
   {
      cout << "\tEuros: " << euros << endl;
   }
   return;
}
