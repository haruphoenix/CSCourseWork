/***********************************************************************
* Program:
*    Assignment 40, Tic Tac Toe  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will read a tic tac toe file, display it, and then
*    write it to another file.
*
*    Estimated:  4.0 hrs   
*    Actual:     0.0 hrs
*      It was difficult to format the board display
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

const int BUFF_SIZE = 256;

void readFile(char game[][BUFF_SIZE]);
void getInFile(char fileName[]);
void display(char game[][BUFF_SIZE]);
void writeFile(char game[][BUFF_SIZE]);
void getOutFile(char fileName[]);

/**********************************************************************
* Calls functions to read, change,  display, and rewrite the game
***********************************************************************/
int main()
{
   char game[BUFF_SIZE][BUFF_SIZE];
   // Read the file
   readFile(game);
   // Display the file
   display(game);
   // Write the file
   writeFile(game);
   return 0;
}

/**********************************************************************
* Read the game file
***********************************************************************/
void readFile(char game[][BUFF_SIZE])
{
   // Get the file name
   char inFileName[BUFF_SIZE];
   getInFile(inFileName);
   // Open the file
   ifstream fin;
   fin.open(inFileName);
   // Read the file
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         fin >> game[i][j];
      }
   }
   // Close the file
   fin.close();
   return;
}

/**********************************************************************
* Ask user for the name of the file to read from
***********************************************************************/
void getInFile(char inFileName[])
{
   cout << "Enter source filename: ";
   cin >> inFileName; // Get the file name
   return;
}

/**********************************************************************
* Display the tic tac toe game
***********************************************************************/
void display(char game[][BUFF_SIZE])
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (game[i][j] != '.')
         {
            cout << " " << game[i][j] << " ";
         }
         else
         {
            cout << "   ";
         }
         if (game[i][j + 1] != '\0')
         {
            cout << "|";
         }
      }
      if ((game[i + 1][0] == '.') ||
          (game[i + 1][0] == 'X') ||
          (game[i + 1][0] == 'O'))
      {
         cout << endl;
         cout << "---+---+---";
      }
      cout << endl;
   }
   return;
}

/**********************************************************************
* Write the modified tic tac toe game to another file
***********************************************************************/
void writeFile(char game[][BUFF_SIZE])
{
   // Get file name
   char outFileName[BUFF_SIZE];
   getOutFile(outFileName);
   // Open the file
   ofstream fout;
   fout.open(outFileName);
   // Write to the file
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         fout << game[i][j];
      }
   }
   // Close the file
   fout.close();
   cout << "File written\n";
   return;
}

/**********************************************************************
* Ask user for the name of the file to write to
***********************************************************************/
void getOutFile(char outFileName[])
{
   cout << "Enter destination filename: ";
   cin >> outFileName; // Get the file name
   return;
}
