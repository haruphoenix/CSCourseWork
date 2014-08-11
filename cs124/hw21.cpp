/***********************************************************************
* Program:
*    Assignment 21, Stub Functions  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will display "success" on the screen. (It doesn't
*    really do anything, but the code is meant to be an outline
*    of functions for a program that can tell you how much you're
*    spending on your car.)
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
using namespace std;

/***********************************************************************
* Base functions to be used in main.
************************************************************************/
float getPeriodicCost();
float getUsageCost();
void displayCost(float periodicCost, float usageCost);

/***********************************************************************
* Sub-functions to be called under function getPeriodicCost.
************************************************************************/
float promptDevalue();
float promptInsurance();
float promptParking();

/***********************************************************************
* Sub-functions to be called under function getUsageCost.
************************************************************************/
float promptMilage();
float promptGas();
float promptRepairs();
float promptTires();

/**********************************************************************
* Main will call functions to get the periodic cost, and the 
* usage cost for the user's car and then call a function to display it.
***********************************************************************/
int main()
{
   float periodicCost;
   float usageCost;
   getPeriodicCost();
   getUsageCost();
   displayCost(periodicCost, usageCost);
   return 0;
}

/**********************************************************************
* getPeriodicCost will ask the user for the devalue of their 
* vehicle, the cost of insurance, and parking.
***********************************************************************/
float getPeriodicCost();
{
   promptDevalue();
   promptInsurance();
   promptParking();
   return 0;
}


float promptDevalue();
{
   return 0;
}
 

float promptInsurance();
{
   return 0;
}


float promptParking();
{
   return 0;
}

/**********************************************************************
* getUsageCost will ask the user for their milage, gas, repair,
* and tire costs.
***********************************************************************/
float getUsageCost();
{
   promptMilage();
   promptGas();
   promptRepairs();
   promptTires();
   return 0;
}


float promptMilage();
{
   return 0;
}


float promptGas();
{
   return 0;
}


float promptRepairs();
{
   return 0;
}


float promptTires();
{
   return 0;
}

/**********************************************************************
* Display all the periodic and usage costs.
***********************************************************************/
void displayCost(float periodicCost, float usageCost);
{
   cout << "Success\n";
   return 0;
}
