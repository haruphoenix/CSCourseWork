/*****************************************************************
* Program:
*    Exploration 2
*    Brother Neff, CS237
* Author:
*    Haru McClellan
* Description:
*    Proves up to so many digits that if a number is a
*    positive integer it may be expressed as the result
*    of the floor of either m*root(2) or m*(2 + root(2))
*    but never both.
******************************************************************/
#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <math.h>
using namespace std;

NTL_CLIENT

ZZ floorOfMTimesRoot2(ZZ m);
ZZ floorOfMTimes2PlusRoot2(ZZ m);

/*****************************************************************
*
*
******************************************************************/
int main()
{
   for (int i = 1; i < 1000; i++)
   {
      cout << floorOfMTimesRoot2(to_ZZ(i)) << " ";
   }
   /*else
   {
      int num = (int)argv[1][0];
      ZZ numTry = to_ZZ(input);
   
      if (cin.fail())
      {
         cin.clear();
         cin.ignore();
         cout << "Error: Invalid value\nProgram will now terminate\n";
      }
   
      else
      {
         for (ZZ i = to_ZZ(1); i < numTry; i++)
         {
            holds = false;
            if (i == floorOfMTimesRoot2(i))
               holds = true;
            if (i == floorOfMTimes2PlusRoot2(i))
               holds = -holds;
            if (-holds)
               break;
         }
      }
   
      if (holds)
         cout << "The conjecture holds\n";
      else
         cout << "The conjecture fails\n";
   }*/
   
   return 0;
}

/*****************************************************************
*
*
******************************************************************/
ZZ floorOfMTimesRoot2(ZZ m)
{
   RR temp = to_RR(m) * to_RR(sqrt(2));
   ZZ result = FloorToZZ(temp);                           
   return result;
}

/*****************************************************************
*
*
******************************************************************/
ZZ floorOfMTimes2PlusRoot2(ZZ m)
{
   RR temp = to_RR(m) * to_RR(2.0 + sqrt(2));
   ZZ result = FloorToZZ(temp);
   return result;
}
