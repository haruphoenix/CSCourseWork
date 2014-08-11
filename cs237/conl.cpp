#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

long long num(string word);
string see(long long numWord);

int main()
{
   cout << "Word: ";
   string word;
   getline(cin, word);
   long long numWord = num(word);
   string seeWord = see(numWord);
   cout << "Word: " << word << endl;
   cout << "Num: " << numWord << endl;
   cout << "See: " << seeWord << endl;
   return 0;
}

long long num(string word)
{
   long long newNum = 0;
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

string see(long long numWord)
{
   string newString;
   long long temp = numWord;
   long long last;
   while (temp != 0)
   {
      last = temp % 100;
      if (last != 0)
         newString = (char)(last + 64) + newString;
      else
         newString = " " + newString;
      temp /= 100;
   }
   return newString;
}

