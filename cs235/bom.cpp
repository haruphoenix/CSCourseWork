/*****************************************************************************
* Program:
*    Assignment 16, Book of Mormon word count
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program reads in a file, (for this assignment the Book of Mormon)
*    and prints out the 100 most frequently used words.
******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
using namespace std;

string fix(string word);

/*****************************************************************************
* Reads in words from a file. Places them into a map. Displays the most
* frequent 100 words.
******************************************************************************/
int main(int argc, char** argv)
{
   try
   {
      if (argc != 2)
         throw argc;
      ifstream read;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      map <string, int> words;
      string word;
      int numWords;
      while (read >> word)
      {
         word = fix(word);
         words[word]++;
         numWords++;
      }
      cout << "\nNumber of words processed: " << numWords
           << "\n100 most common words found and their frequencies:\n";
      
      map<string, int>::iterator i;
      map<string, int>::iterator most = words.begin();
      for (int j = 0; j < 100; j++)
      {
         for (i = words.begin(); i != words.end(); ++i)
            if ((*i).second > (*most).second)
               most = i;
         cout << setw(23) << (*most).first << " - " << (*most).second << endl;
         words.erase(most);
         most = words.begin();
      }
   }
   catch (int e)
   {
      cout << "Error: Must use two arguments\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   return 0;
}

/*****************************************************************************
* Removes punctuation from words. Makes sure all letters are lowercase. Input
* is a string. Returns fixed string.
******************************************************************************/
string fix(string word)
{
   string fixed;
   for (int i = 0; i < word.size(); i++)
   {
      if (isalpha(word[i]))
         fixed += tolower(word[i]);
      else if (word[i] == '-')
         fixed += word[i];
   }
   return fixed;
}
