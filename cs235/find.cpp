#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void search(string line, int number, string word, bool show);

int main(int argc, char** argv)
{
   bool show = false;
   if (argc > 3)
      show = true;
   try
   {
      if (argc < 3)
         throw argc;
      string word = argv[2];
      ifstream read;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      string line;
      int number;
      while (getline(read, line))
         search(line, number++, word, show);
   }
   catch (int e)
   {
      cout << "Error; Must 3 or more arguments\n";
   }
   catch (char* e)
   {
      cout << "Error: Could not open " << e << endl;
   }
   return 0;
}

void search(string line, int number, string word, bool show)
{
   string words[50];
   int num = 0;
   for (int i = 0; i < line.size(); i++)
   {
      if ((line[i] == ' ') || (i == line.size() - 1))
      {
         if (i == line.size() - 1)
            words[num] += line[i];
         num++;
      }
      else
         words[num] += line[i];
   }

   for (int i = 0; i < num; i++)
   {
      if (words[i] == word)
      {
         cout << "Line: " << number;
         if (show)
            cout << " " << line;
         cout << endl;
      }
   }
   
}
