#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string fix(string line, string badWord, string newWord);

int main(int argc, char** argv)
{
   try
   {
      if (argc != 4)
         throw argc;
      ifstream read;
      string badWord = argv[2];
      string newWord = argv[3];
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      string line;
      vector<string> document;
      while (getline(read, line))
      {
         line = fix(line, badWord, newWord);
         document.push_back(line);
      }
      read.close();
      ofstream write;
      write.open(argv[1]);
      if (write.fail())
         throw argv[1];
      for (int i = 0; i < document.size(); i++)
         write << document[i] << endl;
      write.close();
   }
   catch (int e)
   {
      cout << "Error: Must take exactly 4 arguments.\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
}

string fix(string line, string badWord, string newWord)
{
   string fixedString;
   string word;
   vector<string> words;
   for (int i = 0; i < line.size(); i++)
   {
      word += line[i];
      if ((line[i] == ' ') || (i == line.size() - 1))
      {
         words.push_back(word);
         word = "";
      }  
   }
   string temp;
   string newString;
   bool added = false;
   for (int i = 0; i < words.size(); i++)
   {
      newString = "";
      added = false;
      temp = "";
      for (int j = 0; j < words[i].size(); j++)
      {
         if (isalpha(words[i][j]))
            temp += words[i][j];
      }
      if (temp == badWord)
         temp = newWord;
      for (int j = 0; j < words[i].size(); j++)
      {
         if (!(isalpha(words[i][j])))
         {
            newString += words[i][j];
         }
         else if (!added)
         {
            newString += temp;
            added = true;
         }
      }
      words[i] = newString;
   }
   for (int i = 0; i < words.size(); i++)
      fixedString += words[i];

   return fixedString;
}
