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
int crt(int r1, int r2, int r3, int m1, int m2, int m3);

/******************************************************************************
* Run it through its paces.
******************************************************************************/
int main(int argc, char* argv[])
{
   int a, b, c;
   int q, r, s;
   cout << "Three primes: ";
   cin >> q >> r >> s;
   cout << "Three remainders: ";
   cin >> a >> b >> c;
   int x = crt(a, b, c, q, r, s);
   cout << x << endl;
   return 0;
}

/*********************************************************
* 
**********************************************************/
int crt(int r1, int r2, int r3, int a, int b, int c)
{  
   int m  = a * b * c;
   
   int M1 = b * c;
   int M2 = a * c;
   int M3 = a * b;
   
   int j1 = findInverse(M1, a);
   int j2 = findInverse(M2, b);
   int j3 = findInverse(M3, c);
   
   return (((r1 * M1 * j1) + (r2 * M2 * j2) + (r3 * M3 * j3)) % m);
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
