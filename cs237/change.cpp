#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string replace(string line, string word, string newWord);

int main(int argc, char** argv)
{
   ifstream read;
   if (argc != 4)
      return 0;
   read.open(argv[1]);
   if (read.fail())
      return 0;
   
   string word = argv[2];
   string newWord = argv[3];
   string file;
   string line;

   while (getline(read, line))
   {
      line = replace(line, word, newWord);
      file += line;
      file += "\n";
   }

   read.close();

   ofstream write;
   write.open(argv[1]);
   if (write.fail())
      return 0;

   write << file;

   write.close();

   return 0;
}

string replace(string line, string badWord, string newWord)
{
   int size = line.size();
   int numWords = 0;
   
   for (int i = 0; i < size; i++)
      if (!(isalpha(line[i])))
         numWords++;

   string* words = new string[numWords];

   int j = 0;
   for (int i = 0; i < size; i++)
   {
      if (isalpha(line[i]))
         if (j < numWords)
            words[j] += line[i];
      else
      {
         j++
         if (j < numWords)
            words[j] = line[i];  //
      }
   }

   for (int i = 0; i < numWords; i++)
   {
      if (words[i] == badWord)
         words[i] = newWord;
   }
   
   string newLine;

   for (int i = 0; i < numWords; i++)
      newLine += words[i];

   delete [] words;
   return newLine;
}
