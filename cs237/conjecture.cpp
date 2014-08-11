/*******************************************************************************
 * Tests the conjecture
 * NTL library hates me
 ******************************************************************************/
#include <iostream>
#include <math.h>
using namespace std;

const string RED  = "\E[0;31m";
const string BLUE = "\E[0;34m";
const string GRAY = "\E[0;37m";
const string CLR  = "\E[0;0m";

/*******************************************************************************
 *
 *
 ******************************************************************************/
int main()
{
   long long max = 500;
   long long i = 0;

   long long* setA = new long long[max];
   long long* setB = new long long[max];

   long double sqrt2 = sqrt(2);
   long double sqrt2p2 = 2 + sqrt2;

   /*                       Data Sample                       */
   cout << "Different sets\n" << "Set A: ->  a = |_M * 2^(1/2)_|\n" << RED;
   // Set A (floor of m * root2)
   for (i = 1; i < max; i++)
   {
      setA[i-1] = (long long)(i * sqrt2);
      cout << setA[i-1] << " ";
   }
   cout << endl << CLR << "Set B: -> b = |_M * (2 + 2^(1/2))_|\n" << BLUE;
   // Set B (floor of m * (2 + root2))
   for (i = 1; i < max; i++)
   {
      setB[i-1] = (long long)(i * sqrt2p2);
      cout << setB[i-1] << " ";
   }
   cout << endl << CLR << "Mixed together?\nA U B:\n";

   string color[3] = {BLUE, GRAY, RED};
   int val;
   // Set A U B 
   for (i = 1; i < max; i++)
   {
      val = 1;
      for (int j = 0; j < max; j++)
      {
         if (i == setA[j])
            val++;
         if (i == setB[j])
            val--;
      }     
      cout << color[val] << i << " ";
   }
   /*                       Conjecture                        */
   cout << CLR << "\nGiven the current trend, I would suggest this pattern"
        << " holds true for all\npositive integers. The trend being that"
        << " any given positive integer\nwill be in one set or the other"
        << " but not both.\n"
        << "I.E. A UNIONED W/ B = Z+  &  A INTERSECTED W/ B = \\0\n"
        << "Test this for all integers up to: ";

   long long num;
   cin >> num;
   
   while (cin.fail())
   {
      cin.clear();
      cin.ignore();
      cout << "That's not a valid number...\nTry again: ";
      cin >> num;
   }
   cout << endl;
   
      bool      holds = true;
      long long m     = 1;
      long long aSet  = 1;
      long long bSet  = 1;

   /*                       Test Values                        */
   while (m <= num)       
   {
      holds = false;
      if (m == (long long)(aSet * sqrt2))
      {
         aSet++;
         holds = true;
      }
      
      if (m == (long long)(bSet * sqrt2p2))
      {
         bSet++;
         if (!holds)
            holds = true;
         else
            holds = false;
      }
      if (!holds)
         break;
      else
         m++;
   }
   /*                         Conclusion                       */
   if (holds)
      cout << "The conjecture holds for all integers up through "
           << num << endl;
   else
      cout << "The conjecture fails at value " << RED <<  m << CLR
           << "..." << endl
           << "Guess I was wrong, or maybe the precision is\n"
           << "just off because I used long longs, and long doubles\n"
           << "instead of ZZs and RRs because they hate me...\n"
           << "\nThis conjecture actually does hold true for all\n"
           << "positive integers. The proof is in my pdf.\n";

   delete [] setA;
   delete [] setB;
   return 0;
}
