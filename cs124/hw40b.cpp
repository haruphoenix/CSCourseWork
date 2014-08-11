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
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

const int BOARD_SIZE = 3;
const int BUFFER = 256;

void getFileName(char fileName[]);
void getDestination(char fileName[]);
bool readFile(const char fileName[], char board[][BOARD_SIZE]);
void displayBoard(char board[][BOARD_SIZE]);
bool writeFile(const char fileName[], const char board[][BOARD_SIZE]);

/***********************************************************************
* 
***********************************************************************/
int main()
{
   char inFileName[BUFFER];
   char outFileName[BUFFER];
   char board[BOARD_SIZE][BOARD_SIZE];
   
   // ask the user for the board file to read
   getFileName(inFileName);
   
   // read in the board
   readFile(inFileName, board);

   // display the board
   displayBoard(board);

   // get the destination file
   getDestination(outFileName);
   
   // write the board
   writeFile(outFileName, board);
   
   return 0;
}

void getFileName(char fileName[])
{
   cout << "Enter source filename: ";
   cin >> fileName;
   return;
}

void getDestination(char fileName[])
{
   cout << "Enter destination filename: ";
   cin >> fileName;
   return;
}

bool readFile(const char fileName[], char board[][BOARD_SIZE])
{
   ifstream fin(fileName);

   if (fin.fail())
   {
      return false;
   }

   for (int row = 0; row < BOARD_SIZE; row++)
   {
      for (int col = 0; col < BOARD_SIZE; col++)
      {
         fin >> board[row][col];
      }
   }
   
   fin.close();
   return true;
}

void displayBoard(char board[][BOARD_SIZE])
{
   for (int row = 0; row < BOARD_SIZE; row++)
   {
      for (int col = 0; col < BOARD_SIZE; col++)
      {
         if (board[row][col] == '.')
         {
            cout << "   ";
         }
         else
         {
            cout << " " << board[row][col] << " ";
         }
         if (board[row][col+1] != '\0')
         {
            cout << "|";
         }
      }
      cout << endl;
      if (board[row + 1][0] != '\0')
      {
         cout << "---+---+---";
      }
   }
   return;
}

bool writeFile(const char fileName[], const char board[][BOARD_SIZE])
{
   ofstream fout(fileName);

   if (fout.fail())
   {
      return false;
   }

   for (int row = 0; row < BOARD_SIZE; row++)
   {
      for (int col = 0; col < BOARD_SIZE; col++)
      {
         fout << board[row][col];
      }
   }
   
   fout.close();
   return true;
}
