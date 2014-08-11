
/***********************************************************************
* Program:
*    Sandbox
* Author:
*    Haru 
* Summary: 
*    This is my sandbox. It's purpose is to let me experiment and
*    practice writing code freely. 
************************************************************************/

#include <iostream>
#include <math.h>
using namespace std;

bool isRange();
long int getNum();
void getRange();
bool isPrime(long int number, bool factors);

/**********************************************************************
* Call functions to get number and determine if it's prime.
***********************************************************************/
int main()
{
   bool wantsRange = isRange();
   if (!wantsRange)
   {
      long int number = getNum();
      isPrime(number, wantsRange);
   }
   else
   {
      getRange();
   }
   return 0;
}

/********************************************************************
* ask user for number
*********************************************************************/
bool isRange()
{
   char response;
   char range = 'r';
   char value = 'v';
   cout << "Would you like to determine a value or a range? (v/r): ";
   do
   {
      cin >> response;
      if (response == range)
         return true;  
   }
   while ((response != value) && (response != range));
   return false;
}

/********************************************************************
* ask user for number
*********************************************************************/
long int getNum()
{
   long int number;
   cout << "Please enter a number: ";
   cin >> number;
   return number;
}

/********************************************************************
* determine the range of numbers to check
*********************************************************************/
void getRange()
{
   long int start;
   long int end;
   long int value;
   cout << "Where would you like to start?: ";
   cin >> start;
   cout << "Where would you like to end?: ";
   cin >> end;
   value = start;
   for (int i = 0; i < (end - start); i++)
   {
      bool x = isPrime(value, true);
      if (x)
         cout << value << " ";
      value++;
   }
   cout << endl;
   return;
}

/********************************************************************
* determine if number is prime, and it's factors
*********************************************************************/
bool isPrime(long int number, bool factors)
{
   long int bound = ((sqrt(number)) + 1);
   for (long int i = 2; i <= bound; i++)
   {
      if ((number % i) == 0)
      {
         if (factors == false)
         {
            cout << "The integer is divisible by " << i << ".\n";  
         }
         return false;
      }
   }
   if (factors == false)
   {
      cout << "The integer is prime.\n";
   }
   return true;
}
