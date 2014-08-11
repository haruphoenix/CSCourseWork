/***********************************************************************
* Program:
*    Assignment 43, Feet to Meters  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will take in the command line as parameters, and will
*    convert feet to meters.
*
*    Estimated:  0.5 hrs   
*    Actual:     0.4 hrs
*      The most difficult part was finding what library to include to
*      change the string into a float.
************************************************************************/

#include <stdlib.h>
#include <iostream>
using namespace std;

/**********************************************************************
* Main will take in the parameters, and will use functions to convert
* and display the meters
***********************************************************************/
int main(int argc, char **argv)
{
   for (int i = 1; i < argc; i++)
   {
      // Convert feet and meters
      float feet = atof(argv[i]);
      float meters = (feet * 0.3048);
      // Number formatting
      cout.setf(ios::showpoint);
      cout.setf(ios::fixed);
      cout.precision(1);
      // Display feet and meters
      cout << feet << " feet is " << meters << " meters" << endl;
   }
   return 0;
}
