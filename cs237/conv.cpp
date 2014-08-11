#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

int num(string word);
string see(int numWord);

int main()
{
   cout << "Word: ";
   string word;
   cin >> word;
   int numWord = num(word);
   string seeWord = see(numWord);
   cout << "Word: " << word << endl;
   cout << "Num: " << numWord << endl;
   cout << "See: " << seeWord << endl;
   return 0;
}

int num(string word)
{
   int newNum = 0;
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

string see(int numWord)
{
   string newString;
   int temp = numWord;
   int last;
   while (temp != 0)
   {
      last = temp % 100;
      newString = (char)(last + 64) + newString;
      temp /= 100;
   }
   return newString;
}

