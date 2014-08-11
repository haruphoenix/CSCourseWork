/***********************************************************************
* Program:
*    Assignment 13, Temperature Conversion 
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program is supposed to convert Fahrenheit to Celsius.
*    It shouldn't have a decimal, but should be rounded
*    as close as possible to the next integer.
*    
*    
*
*    Estimated:  1.0 hrs   
*    Actual:     1.3 hrs
*      It was hard remembering how to divide integers so I wouldn't get 0
************************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Main will calculate the conversion
* from fahrenheit to celsius
***********************************************************************/
int main()
{
   cout.setf(ios::fixed);
   cout.precision(0);
   int tempFahrenheit;
   cout << "Please enter Fahrenheit degrees: ";
   cin >> tempFahrenheit;
   float tempCelsius = (tempFahrenheit - 32) * (5.0 / 9.0);
   cout << "Celsius: " << tempCelsius << "\n";
   return 0;
}
