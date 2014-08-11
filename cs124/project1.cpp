/***********************************************************************
* Program:
*    project 1, Monthly Budget
*    Brother Andreasen,  CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program asks for your monthly expenses, as well as your 
*    living budget. It calculates your predicted tax and tithing, and
*    displays your budget in a chart along with the difference between
*    what you expected and what you received.
*    
*
*    Estimated:  6.0 hrs   
*    Actual:     8.3 hrs
*      Using if statements to calculate tax was tricky.
************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

float getIncome();
float getBudgetLiving();
float getActualLiving();
float getActualTaxes();
float getActualTithe();
float getActualOther();
float calculateTithe(float income);
float calculateTax(float income);
float calculateOther(float income,
                     float budgetTaxes,
                     float budgetTithe,
                     float budgetLiving);
float calculateBudgetDifference(float income,
                                float budgetLiving,
                                float budgetTaxes,
                                float budgetTithe,
                                float budgetOther);
float calculateActualDifference(float income,
                                float actualLiving,
                                float actualTaxes,
                                float actualTithe,
                                float actualOther);

/************************************************************
* Main calls functions to get input from user, and calculate
* a budget. It displays results on the screen.
*************************************************************/
int main()
{
   
// get expenses from user.
   float income = getIncome();
   float budgetLiving = getBudgetLiving();
   float actualLiving = getActualLiving();
   float actualTaxes = getActualTaxes();
   float actualTithe = getActualTithe();
   float actualOther = getActualOther();

// calculate budget   
   float budgetTaxes = calculateTax(income);
   float budgetTithe = calculateTithe(income);
   float budgetOther = calculateOther(income,
                                      budgetTaxes,
                                      budgetTithe,
                                      budgetLiving);
   float budgetDifference = calculateBudgetDifference(income,
                                                      budgetLiving,
                                                      budgetTaxes,
                                                      budgetTithe,
                                                      budgetOther);
   float actualDifference = calculateActualDifference(income,
                                                      actualLiving,
                                                      actualTaxes,
                                                      actualTithe,
                                                      actualOther);
// Number Formatting
   cout.setf(ios::showpoint);
   cout.setf(ios::fixed);
   cout.precision(2);
         
// Display Data.
   cout << "\nThe following is a report on your monthly expenses\n";
   cout << "\tItem                  Budget          Actual\n";
   cout << "\t=============== =============== ===============\n";
   cout << "\tIncome          $" << setw(11) << income << setw(5)
        << "$" << setw(11) << income << endl;
   cout << "\tTaxes           $" << setw(11) << budgetTaxes << setw(5)
        << "$" << setw(11) << actualTaxes << endl;
   cout << "\tTithing         $" << setw(11) << budgetTithe << setw(5)
        << "$" << setw(11) << actualTithe << endl;
   cout << "\tLiving          $" << setw(11) << budgetLiving << setw(5)
        << "$" << setw(11) << actualLiving << endl;
   cout << "\tOther           $" << setw(11) << budgetOther << setw(5)
        << "$" << setw(11) << actualOther << endl;
   cout << "\t=============== =============== ===============\n";
   cout << "\tDifference      $" << setw(11) << budgetDifference << setw(5)
        << "$" << setw(11) << actualDifference << endl;
   return 0;
}

/******************************************************************
* Asks user for their income.
*******************************************************************/
float getIncome()
{
   float income;
   cout << "This program keeps track of your monthly budget\n"
        << "Please enter the following:\n"
        << "\tYour monthly income: ";
   cin >> income;
   return income;
}

/******************************************************************
* Asks user for their budgeted Living expenses.
*******************************************************************/
float getBudgetLiving()
{
   float budgetLiving;
   cout << "\tYour budgeted living expenses: ";
   cin >> budgetLiving;
   return budgetLiving;
}

/******************************************************************
* Asks user for their actual living expenses.
*******************************************************************/
float getActualLiving()
{
   float actualLiving;
   cout << "\tYour actual living expenses: ";
   cin >> actualLiving;
   return actualLiving;
}

/******************************************************************
* Asks user for their actual taxes withheld.
*******************************************************************/
float getActualTaxes()
{
   float actualTaxes;
   cout << "\tYour actual taxes withheld: ";
   cin >> actualTaxes;
   return actualTaxes;
}

/******************************************************************
* Asks user for income.
*******************************************************************/
float getActualTithe()
{
   float actualTithe;
   cout << "\tYour actual tithe offerings: ";
   cin >> actualTithe;
   return actualTithe;
}

/******************************************************************
* Calculates budgeted Tithing.
*******************************************************************/
float calculateTithe(float income)
{
   float budgetTithe;
   budgetTithe = (income / 10.00);
   return budgetTithe;
}

/******************************************************************
* Determine and calculate tax based off income.
*******************************************************************/
float calculateTax(float income)
{
   float yearlyIncome = (income * 12.00);
   float budgetTaxes;   
   if (yearlyIncome == 0.00)
   {
      budgetTaxes = 0;
   }
   else if (yearlyIncome <= 15100.00)  
   {
      budgetTaxes = (income * 0.10);
   }
   else if (yearlyIncome <= 61300.00)
   {
      budgetTaxes = (1510.00 + ((income - 15100.00) * 0.15));
   }
   else if (yearlyIncome <= 123700.00)
   {
      budgetTaxes = (8440.00 + ((income - 61300.00) * 0.25));
   }
   else if (yearlyIncome <= 188450.00)
   {
      budgetTaxes = (24040.00 + ((income - 123700.00) * 0.28));
   }
   else if (yearlyIncome <= 336550.00)
   {
      budgetTaxes = (42170.00 + ((income - 188450.00) * 0.33));
   }
   else
   {
      budgetTaxes = (91043.00 + ((income - 336550.00) * 0.35));
   }
   return budgetTaxes;
}

/******************************************************************
* Asks user for actual other expenses used.
*******************************************************************/
float getActualOther()
{
   float actualOther;
   cout << "\tYour actual other expenses: ";
   cin >> actualOther;
   return actualOther;
}

/******************************************************************
* Calculate budgeted other expenses.
*******************************************************************/
float calculateOther(float income,
                     float budgetTaxes,
                     float budgetTithe,
                     float budgetLiving)
{
   float budgetOther = (income - (budgetLiving + budgetTaxes + budgetTithe));
   return budgetOther;
}

/******************************************************************
* Calculate the difference between income and budgeted expenses.
*******************************************************************/
float calculateBudgetDifference(float income,
                                float budgetLiving,
                                float budgetTaxes,
                                float budgetTithe,
                                float budgetOther)
{
   float budgetDifference = (income - (budgetLiving + budgetTaxes
                                 + budgetTithe + budgetOther));
   return budgetDifference;
}

/******************************************************************
* Calculate the difference between income and actual expenses.
*******************************************************************/
float calculateActualDifference(float income,
                                float actualLiving,
                                float actualTaxes,
                                float actualTithe,
                                float actualOther)
{
   float actualDifference = (income - (actualLiving + actualTaxes
                                 + actualTithe + actualOther));
   return actualDifference;
}
