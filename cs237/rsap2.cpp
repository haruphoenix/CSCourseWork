/***********************************************************************
 * RSA Encryption/Decryption
 ***********************************************************************/
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;


int modExp(int b, int n, int m);
void eea(int a, int b, int& gcd, int& x, int&y);
int findInverse(int a, int m);
int crt(int rems[], int mods[], int size);

/******************************************************************************
* Run it through its paces.
******************************************************************************/
int main(int argc, char* argv[])
{
   int size;
   cout << "Size: ";
   cin >> size;
   int primes[size];
   cout << "Primes: ";
   for (int i = 0; i < size; i++)
      cin >> primes[i];
   int remainders[size];
   cout << "Remainders: ";
   for (int i = 0; i < size; i++)
      cin >> remainders[i];
   int x = crt(remainders, primes, size);
   cout << x << endl;
   return 0;
}

/*********************************************************
*  
**********************************************************/
int crt(int rems[], int mods[], int size)
{  
   int m  = 1;
   int Mn[size];
   int Jn[size];
   int x  = 0;
   
   for (int i = 0; i < size; i++)
      m *= mods[i];
   for (int i = 0; i < size; i++)
      Mn[i] = (m / mods[i]);
   for (int i = 0; i < size; i++)
      Jn[i] = findInverse(Mn[i], mods[i]);
   for (int i = 0; i < size; i++)
      x += (rems[i] * Mn[i] * Jn[i]);
   
   return (x % m);
}

/*********************************************************
* Finds b^n % m
**********************************************************/
int modExp(int b, int n, int m)
{
   int x = 1;
   int power = b % m;
   while (n > 0)
   {
      if (n % 2 == 1)
      {
         x = (x * power) % m;
      }
      power = (power * power) % m;
      n /= 2;
   }
   return x;
}

/*********************************************************
* Extended Euclidean Algorithm
* Given a,b, Find x,y,g that solve the equation:
*       ax + by = g = gcd(a,b)
*   * Source: en.literateprograms.org
*   * Modified by Haru
*********************************************************/
void eea(int a, int b, int& gcd, int& x, int& y)
{
   x = 0;
   y = 1;
   int u = 1, v = 0, m, n, q, r;
   gcd = b;
   while (a != 0)
   {
      q = gcd / a;
      r = gcd % a;
      m = x - (u * q);
      n = y - (v * q);
      gcd = a;
      a = r;
      x = u;
      y = v;
      u = m;
      v = n;
   }
   return;
}

/**************************************************************
* Finds i such that a * i is congruent to 1 (mod m)
***************************************************************/
int findInverse(int a, int m)
{
   int gcd, x, y;
   eea(m, a, gcd, x, y);
   while (y < 0)
      y += m;
   return y % m;
}
