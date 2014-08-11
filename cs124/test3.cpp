/**************************************************
* Program:
*    Test 3,
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will read a text file, and then display
*    it backwards
************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

const int FILE_SIZE = 4000;
const int NAME_SIZE = 32;

int readFile(char text[]);
void getFileName(char fileName[]);
void display(char text[], int sizeOfFile);

/***********************************************************
* Calls functions to read the file, and then display it
* backwards.
************************************************************/
int main()
{
   char text[FILE_SIZE];
   int sizeOfFile;
   sizeOfFile = readFile(text);  // Read the file
   display(text, sizeOfFile);    // Display the file
   return 0;
}

/***********************************************************
* Reads a file
************************************************************/
int readFile(char text[])
{
   char fileName[NAME_SIZE];
   getFileName(fileName);   // Get the name of the file
   ifstream fin;
   fin.open(fileName);       // Open the file
   int sizeOfFile = 0;
   while (fin >> text[sizeOfFile]) // While it's reading
   {
      sizeOfFile++;            // Increment size of file
   }
   return sizeOfFile;
}

/***********************************************************
* Gets the name of the file from the user
************************************************************/
void getFileName(char fileName[])
{
   cout << "Please enter the filename: ";
   cin >> fileName;            // Ask user for file name
   return;
}

/***********************************************************
* Displays the file backwards
************************************************************/
void display(char text[], int sizeOfFile)
{
   // Display backwards
   for (int i = sizeOfFile - 1; i > -1; i--) 
   {
      cout << text[i];
   }
   cout << endl;
   return;
}
