/**********************************************************************************************
* The way to compile with a name other than a.out is to type "g++ -o exe_name source_name"
**********************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;


/**********************************************************************************************
* argc is the number of arguments. argv are the arguments themselves
**********************************************************************************************/
int main(int argc, char* argv[])
{
   try
   {
      if ((argc != 2) && (argc != 3))
         throw argc;
      ifstream read;
      string line;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      if (argc == 3)
      {
         for (int i = 0; i < atoi(argv[2]) + 1; i++)
            getline(read, line);
         cout << line << endl;
      }
      else
         while (getline(read, line))
            cout << line << endl;
      read.close();
   }
   catch (int e)
   {
      cout << "Error: Requires 2 or 3 arguments\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   return 0;
}
