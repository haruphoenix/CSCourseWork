/***********************************************************************
* Program:
*    Assignment 34, Account Balances  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will determine which of two accounts has
*    more money in it, and will use a pointer to change the
*    value in the account that will pay. Kind of like a debit
*    card. It will display the amount in the accounts at the end.
*
*    Estimated:  1.0 hrs   
*    Actual:     0.8 hrs
*      Compiled on first try, only forgot to set the cost of the date
*      equal to the function dateCost. Had fun using pass by reference.
************************************************************************/

#include <iostream>
using namespace std;

void getBalance(float &accountSam, float &accountSue);
void setAccount(float &accountSam, float &accountSue, float * &pAccount);
float askCost();
void payDate(float dateCost, float * &pAccount);
void displayBalance(float accountSam, float accountSue);

/**********************************************************************
* Calls functions to get balances, determine which is greater, set
* a pointer to the greater account, ask for the cost of the date,
* subtract the cost from the account using a pointer, and display the
* ending balances of the account.
***********************************************************************/
int main()
{
   float accountSam;
   float accountSue;
   float *pAccount;
   float dateCost;
   // Get Sam and Sue's balances
   getBalance(accountSam, accountSue);
   // Determine who has more money and set pointer to account
   setAccount(accountSam, accountSue, pAccount);
   // Determine cost of the date
   dateCost = askCost();
   // Pay for the date
   payDate(dateCost, pAccount);
   // Display final balances
   displayBalance(accountSam, accountSue);
   return 0;
}

/**********************************************************************
* Prompt for Sam and Sue's account balances
***********************************************************************/
void getBalance(float &accountSam, float &accountSue)
{
   cout << "What is Sam's balance? ";
   cin >> accountSam;

   cout << "What is Sue's balance? ";
   cin >> accountSue;
   return;
}

/**********************************************************************
* Determine who has more money, and "use their card"
***********************************************************************/
void setAccount(float &accountSam, float &accountSue, float * &pAccount)
{
   if (accountSam > accountSue)
   {
      pAccount = &accountSam;
   }
   else
   {
      pAccount = &accountSue;
   }
   return;
}

/**********************************************************************
* Find cost of date
***********************************************************************/
float askCost()
{
   float dinner;
   float movie;
   float iceCream;
   cout << "Cost of the date:\n"
        << "\tDinner:    ";
   cin >> dinner;
   cout << "\tMovie:     ";
   cin >> movie;
   cout << "\tIce cream: ";
   cin >> iceCream;
   return (dinner + movie + iceCream);
}

/**********************************************************************
* Pay using debit card
***********************************************************************/
void payDate(float dateCost, float * &pAccount)
{
   *pAccount -= dateCost;
   return;
}

/**********************************************************************
* Display final account balances
***********************************************************************/
void displayBalance(float accountSam, float accountSue)
{
   cout << "Sam's balance: $" << accountSam << endl;
   cout << "Sue's balance: $" << accountSue << endl;
   return;
}
