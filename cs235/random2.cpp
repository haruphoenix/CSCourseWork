/*****************************************************************************
* Random
*
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <cstdlib>
#include <time.h>
using namespace std;

const int RANDOM_SEED = 2500;

/*****************************************************************************
* 
******************************************************************************/
class Random
{
   public:
      Random(void);
      int poissonRandom(double expected);
};


/*****************************************************************************
* main description
******************************************************************************/
int main()
{
   Random rand;
   int number = 0;
   int count = 0;
   int count2 = 0;
   double percent = 0.0;
   cout << "number: ";
   cin >> number;
   cout << "percent: ";
   cin >> percent;
   for (int i = 0; i < number; i++)
   {
      cout << rand.poissonRandom(percent);
      count++;
      if (count == 4)
      {
         cout << endl;
         count = 0;
         count2++;
         if (count2 == 4)
         {
            cout << endl;
            count2 = 0;
         }
      }
   }
   cout << endl;
   return 0;
}


/*****************************************************************************
* 
******************************************************************************/
Random::Random()
{
   srand(RANDOM_SEED);
}

/*****************************************************************************
* 
******************************************************************************/
int Random::poissonRandom(double expected)
{
   int n = 0;
   double limit = exp(-expected);
   double x = rand() / ((double)RAND_MAX + 1);

   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   
   return n;
}

