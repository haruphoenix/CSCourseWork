#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <NTL/ZZ.h>

NTL_CLIENT

using namespace std;
using namespace NTL;

ZZ to_ZZ(string word);
string to_string(ZZ number);

int main()
{
   cout << "Word: ";
   string word;
   getline(cin, word);
   ZZ number = to_ZZ(word);
   word = to_string(number);
   cout << "Word: " << word << endl;
   cout << "Num: " << number << endl;
   cout << "Word: " << word << endl;
   return 0;
}

ZZ to_ZZ(string word)
{
   ZZ newNum = to_ZZ(0);
   string temp;

   for (int i = 0; i < word.size(); i++)
   {
      if (word[i] != ' ')
      {
         if (word[i] < 'j')
            temp += "0";
         temp += ((word[i]) - (16));
      }
      else
         temp += "00";
   }

   for (int i = 0; i < temp.size(); i++)
      newNum += ((temp[i] - 48) * pow(10, (temp.size() - i - 1)));

   return newNum;
}

string to_string(ZZ number)
{
   string newString;
   ZZ temp = number;
   int last;
   while (temp != 0)
   {
      last = temp % 100;
      if (last != 0)
      {
         newString = (char)(last + 64) + newString;
      }
      else
      {
         newString = " " + newString;
      }
      temp = (temp / 100);
   }
   return newString;
}

