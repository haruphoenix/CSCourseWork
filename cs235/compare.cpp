/**********************************************************************************************
* The way to compile with a name other than a.out is to type "g++ -o exe_name source_name"
**********************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const string RED   = "\E[22;31m";
const string GREEN = "\E[22;32m";
const string WHITE = "\E[0m";

/**********************************************************************************************
* argc is the number of arguments. argv are the arguments themselves
**********************************************************************************************/
int main(int argc, char* argv[])
{
   ifstream read1;
   ifstream read2;
   string line1;
   string line2;
   char* pFilename1 = argv[1];
   char* pFilename2 = argv[2];
   int errors = 0;
   int lineNum = 1;
   read1.open(pFilename1);
   read2.open(pFilename2);
   while (getline(read1, line1))
   {
      // getline(read1, line1);
      getline(read2, line2);
      if (line1 == line2)
      {
         cout << GREEN << lineNum << ": " << line1 << WHITE << endl;
         lineNum++;
      }
      else
      {
         cout << RED << lineNum << ": "  << line1 << endl;
         cout << WHITE << lineNum << ": " << line2 << endl;
         errors++;
      }
  }
   if (errors == 0)
      cout << "\nThere were no errors.\n";
   else if (errors == 1)
      cout << RED << "\nThere was " << errors << " error.\n" << WHITE;
   else
      cout << RED << "\nThere were " << errors << " errors.\n" << WHITE;
   read1.close();
   read2.close();
   return 0;
}
