#include <iostream>
#include <string>
#include <NTL/ZZ.h>
using namespace std;

NTL_CLIENT

ZZ to_ZZ(string word);
string to_string(ZZ number);
ZZ pow(ZZ b, ZZ p);

NTL_CLIENT

int main()
{
   string word;
   ZZ number;
   cout << "Word: ";
   getline(cin, word);

   number = to_ZZ(word);
   word   = to_string(number);

   cout << "Number: " << number << endl;
   cout << "Word: " << word << endl;
   return 0;
}

ZZ to_ZZ(string word)
{
   ZZ number = to_ZZ(0);

   for (int i = 0; i < word.size(); i++)
   {
      if (word[i] == ' ')
         word[i] = 64;
      number += (to_ZZ(word[i] - 64) * pow(to_ZZ(27), to_ZZ(word.size() - i - 1)));
   }

   return number;
}

string to_string(ZZ number)
{
   string word;
   char temp;
   string tempS;
  
   while (number != 0)
   {
      temp = (char)((number % 27) + 64);
      tempS = temp;
      if (temp == '@')
         tempS = " ";
      word = tempS + word;
      number /= 27;
   }
   return word;
}

ZZ pow(ZZ b, ZZ p)
{
   ZZ result = to_ZZ(1);
   for (int i = 0; i < p; i++)
      result *= b;
   return result;
}
