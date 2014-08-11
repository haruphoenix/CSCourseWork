#include <iostream>
#include <string>
#include <NTL/ZZ.h>
#include <math.h>
using namespace std;

NTL_CLIENT

ZZ encode(string word);
string decipher(ZZ number);

ZZ to_ZZ(string number);
ZZ pow(ZZ b, ZZ p);

int main()
{
   ZZ number;
   string word;
   cout << "Word: ";
   getline(cin, word);
   number = encode(word);
   word = decipher(number);
   cout << "Number: " << number << endl;
   cout << "Word: " << word << endl;
   return 0;
}

ZZ encode(string word)
{
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
   return to_ZZ(temp);  
}

string decipher(ZZ number)
{
   string phrase;
   int last;
   while (number != 0)
   {
      last = number % 100;
      if (last != 0)
      {
         phrase = (char)(last + 64) + phrase;
      }
      else
      {
         phrase = " " + phrase;
      }
      number = (number / 100);
   }
   return phrase;
}

ZZ to_ZZ(string word)
{
   ZZ zzNum = to_ZZ(0);
   for (int i = 0; i < word.size(); i++)
      zzNum += to_ZZ(word[i] - 48) *
         pow(to_ZZ(10), to_ZZ(word.size() - i - 1));
   return zzNum;
}

ZZ pow(ZZ b, ZZ p)
{
   ZZ result = to_ZZ(1);
   for (int i = 0; i < p; i++)
      result *= b;
   return result;
}
