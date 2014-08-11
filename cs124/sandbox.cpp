/***********************************************************************
* Program:
*    Sandbox       
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This is my sandbox. It's purpose is to let me experiment and
*    practice writing code freely. 
************************************************************************/

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

const int INVALID = -1;

string getFileName();
int readFile(string fileName);
void display(int numLines);

/**********************************************************************
*  
***********************************************************************/
int main(int argc, char **argv)
{
   string fileName;
   int count = 0;
   // Try to get the file name from the command line
   if (argc == 1)
      fileName = getFileName();
   // If it isn't there, prompt for it
   else
      fileName = argv[1];
   // Read the file
   count = readFile(fileName);
   // Display the result
   if (count != INVALID)
      display(count);
   else
      cout << "Error reading file.\n";
   return 0;
}

string getFileName()
{
   string fileName;
   cout << "Please enter the file name: ";
   cin >> fileName;
   return fileName;
}

int readFile(string fileName)
{
   ifstream fin(fileName.c_str());
   if (fin.fail())
      return -1;
   int count = 0;
   string line;
   while (getline(fin, line))
   {
      count++;
   }
   fin.close();
   return count;
}

void display(int count)
{
   cout << "The number of lines is " << count << ".\n";
   return;
}


