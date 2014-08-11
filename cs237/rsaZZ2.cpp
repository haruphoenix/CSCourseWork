/***********************************************************************
* Program:
*    Exploration 3, RSA Encryption/Decryption
*    Brother Neff, CS237
* Author:
*    Brother Neff?, modified by Haru McClellan
* Description:
*    Encrypts or decrypts a message using the RSA system given
*    two multiples n, and an encryption key e.
***********************************************************************/
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <NTL/ZZ.h>
using namespace std;

NTL_CLIENT

int modExp(int b, int n, int m);
int findInverse(int a, int m);
void eea(int a, int b, int& gcd, int& x, int& y);

/******************************************************************************
 * Run it through its paces.
 ******************************************************************************/
int main(int argc, char* argv[])
{
   if (argc < 5)
   {
      cout << "Usage: " << argv[0] << " p q e message\n";
      return 1;
   }

   int p = atoi(argv[1]);
   int q = atoi(argv[2]);
   int n = p * q;
   int e = atoi(argv[3]);
   int d = 0;

   char* message = argv[4];
   int offset = 'A';    // offset for conversion without spaces
   bool spaces = false; // true => there are spaces in the message

   int length = strlen(message);

   if (isalpha(message[0]))
   {
      int size = (int) (ceil(length / 2.0));
      int numeric[size];
      int number;

      for (int i = 0; i < length; i++)
      {
         // is there a space?
         if (message[i] == ' ')
         {
            spaces = true;
            offset--;
            break;
         }
      }

      cerr << "RSA Encryption:\n\n";

      cerr << "Translate the letters in '" << message << "' into their "
           << "numerical\nequivalents and then group the numbers into "
           << "blocks of four, result is:\n";

      for (int i = 0; i < length; i++)
      {
         message[i] = toupper(message[i]); // Change to all upper case
         if (message[i] == ' ')
         {
            number = 0; // spaces translate as zero
         }
         else
         {
            number = message[i] - offset; // find numeric equivalent
         }
         if (i % 2 == 0)
         {
            numeric[i / 2] = number * 100; // 2 hundreds digits
         }
         else
         {
            numeric[i / 2] += number; // 2 tens digits
         }
      }

      // output the converted letters as a number with leading zeros
      for (int i = 0; i < size; i++)
      {
         cout << setfill('0') << setw(4) << numeric[i] << " ";
      }
      cout << endl;
      cout.flush();

      cerr << "\nEncrypt each block using the mapping C = M^e mod n, ";
      cerr << "result is:\n";

      for (int i = 0; i < size; i++)
      {
         cout << setfill('0') << setw(4) << modExp(numeric[i], e, n)
              << " ";
      }
      cout << endl;
   }
   else
   {
      cerr << "RSA Decryption:\n\n";

      length = argc - 4;
      int numeric[length];

      for (int i = 0; i < length; i++)
      {
         numeric[i] = atoi(argv[i + 4]);
      }

      cerr << "Find the inverse of " << e << " modulo " << p - 1 << " * "
           << q - 1 << " = " << ((p - 1) * (q - 1)) << ", result is: ";
      d = findInverse(e, ((p - 1) * (q - 1)));
      cerr << d << endl << endl;

      cerr << "Decrypt the message ";
      for (int i = 0; i < length; i++)
      {
         cerr << setfill('0') << setw(4) << numeric[i] << " ";
      }

      cerr << "\nusing fast modular exponentiation to compute P = C^"
           << d << " mod " << n << ", result is:\n";

      for (int i = 0; i < length; i++)
      {
         numeric[i] = modExp(numeric[i], d, n);
         cerr << setfill('0') << setw(4) << numeric[i] << " ";
      }
      cerr << endl;
      cerr.flush();

      cerr << "\nTranslate back to English letters, result is:\n";
      cerr.flush();

      if (d > 1000) offset--;

      for (int i = 0; i < length * 2; i++)
      {
         char c = ((i % 2 == 0) ?
                   (numeric[i / 2] / 100) + offset
                   :
                   (numeric[i / 2] % 100) + offset);
         cout << ((c < 'A') ? ' ' : c);
      }
      cout << endl;
   }

   return 0;
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

/********************************************************
* Extended Euclidean Algorithm
* Given a,b, Find x,y,g that solve the equation:
*       ax + by = g = gcd(a,b)
*   * Source: en.literateprograms.org
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
