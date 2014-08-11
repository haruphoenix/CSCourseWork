/***********************************************************************
 * Program:
 *    Exploration 3, RSA
 *    Brother Neff, CS237
 *
 * Author:
 *    Brother Neff/Haru McClellan
 *
 * Summary:
 *    RSA Encryption/Decryption Driver
 *    Compile with:
 *      g++ -c rsaZZmain.cpp
 ***********************************************************************/
#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

NTL_CLIENT

ZZ to_ZZ(string number);
ZZ pow(ZZ b, ZZ p);

/******************************************************************************
 * Find b^n % m.
 ******************************************************************************/
ZZ modExp(ZZ b, ZZ n, ZZ m)
{
   return PowerMod(b, n, m);
}


/******************************************************************************
 * Find i such that a * i is congruent to 1 (mod m).
 ******************************************************************************/
ZZ findInverse(ZZ a, ZZ m)
{
   ZZ gcd, x, y;
   XGCD(gcd, x, y, a, m);
   if (x < 0) x += m;
   return x;
}

/******************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ******************************************************************************/
ZZ fromBase27(string message)
{
   ZZ number = to_ZZ(0);
   for (int i = 0; i < message.size(); i++)
   {
      if (message[i] == ' ')
         message[i] = 64;
      number += (to_ZZ(message[i] - 64) *
                 pow(to_ZZ(27), to_ZZ(message.size() - i - 1)));
   }
   return number;
   
}

/******************************************************************************
 * Convert from a ZZ number to a base 27 number represented by a text message.
 ******************************************************************************/
string toBase27(ZZ n)
{
   string word;
   char temp;
   string tempS;
   while (n != 0)
   {
      temp = (char)((n % 27) + 64);
      tempS = temp;
      if (temp == '@')
         tempS = " ";
      word = tempS + word;
      n /= 27;
   }
   return word;
}

/******************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 ******************************************************************************/
ZZ findE(ZZ t)
{
   ZZ e = to_ZZ(2);
   while (GCD(e, t) != 1) e++;
   return e;   
}

/******************************************************************************
 * Find suitable primes p and q for encrypting a ZZ number that is the message.
 ******************************************************************************/
void findPandQ(ZZ m, ZZ& p, ZZ& q)
{
   ZZ start = SqrRoot(m);
   NextPrime(p, start);
   NextPrime(q, (p + 1));
}

/******************************************************************************
 * converts a string with numbers in it to a ZZ data type
 ******************************************************************************/
ZZ to_ZZ(string word)
{
   ZZ zzNum = to_ZZ(0);
   for (int i = 0; i < word.size(); i++)
      zzNum += to_ZZ(word[i] - 48) *
         pow(to_ZZ(10), to_ZZ(word.size() - i - 1));
   return zzNum;
}

/******************************************************************************
 * Returns b^p
 ******************************************************************************/
ZZ pow(ZZ b, ZZ p)
{
   ZZ result = to_ZZ(1);
   for (int i = 0; i < p; i++)
      result *= b;
   return result;
}

