#include <iostream>
#include <stdlib.h>
#include "clist.cpp"
using namespace std;

int main()
{
   LList<int> list;
   string numbers;
   cout << "Numbers: ";
   getline(cin, numbers);
   string number;
   for (int i = 0; i < numbers.size(); i++)
   {
      if ((numbers[i] == ' ') || (i == numbers.size() - 1))
      {
         if (numbers[i] != ' ')
            number += numbers[i];
         cout << "number: " << number << endl;
         list.insert(atoi(number.c_str()));
         number = "";
      }
      else
         number += numbers[i];
   }
   list.sort();
   for (int i = 0; i < list.size(); i++)
      cout << list[i] << " ";
   cout << endl;
}
