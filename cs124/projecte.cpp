/***********************************************************************
* Program:
*    Project Extra, Sudoku  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will open a sudoku file, and allow the user to display
*    it, change values, find possible values, and save the game. This
*    program has better error checking, and displays read-only values
*    in green
*    
*    Estimated:  15.0 hrs   
*    Actual:     16.0 hrs
*      Validating the board was very hard.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Game Constants
const int ROW_SIZE = 9;
const int COL_SIZE = 9;
const int FILE_SIZE = 256;

// Open File
bool readFile(int sudoku[][COL_SIZE]);
void getInFileName(char inFileName[]);
bool validateBoard(int sudoku[][COL_SIZE]);

// Play Game
void interact(int sudoku[][COL_SIZE]);

// Displays
void displayBoard(int sudoku[][COL_SIZE]);
void displayOptions();
void displayValues(int sudoku[][COL_SIZE]);

// Computations
bool getCoordinates(string square, int coordinates[]);
void findSquare(int coord[], char square[]);
void editSquare(int sudoku[][COL_SIZE]);
void computeValues(int sudoku[][COL_SIZE], int coordinates[], int values[]);
bool computeSection(int sudoku[][COL_SIZE], int coordinates[], int number);

// Save File
void writeFile(int sudoku[][COL_SIZE]);
void getOutFileName(char outFileName[]);


/**********************************************************************
* main opens the game, plays the game, and closes the game.
***********************************************************************/
int main()
{
   int sudoku[ROW_SIZE][COL_SIZE];
   bool isReadable = false;
   // Open sudoku File
   isReadable = readFile(sudoku);
   // Error Checking
   if (!isReadable)
   {
      return 0;
   }
   // Play the game
   interact(sudoku);
   // Save sudoku File
   writeFile(sudoku);
   return 0;
}


/**********************************************************************
* Reads the file, and assigns it into an array "sudoku"
***********************************************************************/
bool readFile(int sudoku[][COL_SIZE])
{
   // Get the file name
   char inFileName[FILE_SIZE];
   getInFileName(inFileName);
   
   // Open the file
   ifstream fin(inFileName);
   
   // Make sure the file opens
   if (fin.fail())
   {
      cout << "ERROR: Cannot open file\n";
      return false;
   }
   
   // Read the file
   for (int i = 0; i < ROW_SIZE; i++)
   {
      for (int j = 0; j < COL_SIZE; j++)
      {
         fin >> sudoku[i][j];
      }
   }
   
   // Validate the board
   if (!validateBoard(sudoku))
      return false;
   
   // Close the file
   fin.close();
   return true;   
}

/**********************************************************************
* Get the name of the sudoku file
***********************************************************************/
void getInFileName(char inFileName[])
{
   // Prompt for sudoku file
   cout << "Where is your board located? ";
   // Get the sudoku file
   cin >> inFileName;
   // Ignore enter from getting file name
   cin.ignore();
}

/**********************************************************************
* Make sure the board is valid
***********************************************************************/
bool validateBoard(int sudoku[][COL_SIZE])
{
   // For every value in the array
   for (int i = 0; i < ROW_SIZE; i++)
   {
      for (int j = 0; j < COL_SIZE; j++)
      {
         // So long as it's not an empty space
         if (sudoku[i][j] != 0)
         {
            bool isValid = false;
            int coord[1];
            int values[9];
            // Create temporary variable
            int temp = sudoku[i][j];
            sudoku[i][j] = 0;
            coord[0] = i;
            coord[1] = j;

            // Compute valid numbers for each square
            computeValues(sudoku, coord, values);
            
            // Make sure each number is valid
            for (int q = 0; q < 9; q++)
            {
               if ((values[q] == temp) ||
                   (values[q] == -temp))
               {
                  isValid = true;
               }
            }

            // Error if invalid board
            if (!isValid)
            {
               // Determine the invalid square
               char square[1];
               findSquare(coord, square);
               
               // Display error message
               cout << "ERROR: Duplicate value '" << temp
                    << "' in inside square represented by '"
                    << square[0] << square[1]
                    << "'" << endl;
               
               // End program
               return false;
            }

            // Set back to normal value
            else
            {
               sudoku[i][j] = temp;
            }
         }
      }
   }
   return true;
}

/**********************************************************************
* Interact takes commands from the user, and calls functions accordingly
***********************************************************************/
void interact(int sudoku[][COL_SIZE])
{
   // Display options
   displayOptions();
   // Display the sudoku board
   displayBoard(sudoku);

   // Get a command from the user
   char command;
   while (command != 'Q')
   {
      cout << "\n> ";                            // Prompt for a command
      cin >> command;                                 // Get the command
      // Make sure it's caps
      command = toupper(command);
      switch (command)
      {
         case '?':                   // ? calls function to show options
            displayOptions();
            break;
         case 'D':                  // D calls function to display board
            displayBoard(sudoku);
            break;
         case 'E':                  // E calls function to edit a square
            editSquare(sudoku);
            break;
         case 'S':                        // S calls function to display  
            displayValues(sudoku);        //             possible values
            break;
         case 'Q':                                    // Q ends the loop
            break;
         default:                     // Anything else will result in an
            cout << "ERROR: Invalid command\n";         // Error message
            break;
      }
   }
}

/**********************************************************************
* Display Board displays the sudoku array in its game format
***********************************************************************/
void displayBoard(int sudoku[][COL_SIZE])
{
   // Display Header
   cout << "   A B C D E F G H I\n";
   
   // Display by Row
   for (int row = 0; row < ROW_SIZE; row++)
   {
      cout << row + 1 << "  ";   
      // Display by Column
      for (int col = 0; col < COL_SIZE; col++)
      {
         if (sudoku[row][col] != 0)
         {
            // Original values in green
            if (sudoku[row][col] > 0)
               cout << "\E[22;32m" << sudoku[row][col] << "\E[0m" ;
            else
               cout << -sudoku[row][col];
         }
         else
         {
            cout << " ";
         }
         // Display column spacing, and lines
         if ((col - 2) % 3 != 0)
         {
            cout << " ";
         }
         else if ((col + 1) != COL_SIZE)
         {
            cout << "|";
         }
      }
      // Display Row spacing and lines
      cout << endl;
      if (((row + 1) % 3 == 0) && (row + 1) != ROW_SIZE)
      {
         cout << "   -----+-----+-----\n";
      }
   }
}

/**********************************************************************
* Display the different options for function "interact"
***********************************************************************/
void displayOptions()
{
   // Only displays options. In own function, since must be done more
   // than once
   cout << "Options:\n"
        << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n"
        << endl;
}

/**********************************************************************
* Display the different possible values for a certain square
* Called by "interact"
***********************************************************************/
void displayValues(int sudoku[][COL_SIZE])
{
   string square;
   int coordinates[1];
   int values[9];
   bool isValid = true;
   string newSquare;
   
   // Get the square
   cout << "What are the coordinates of the square: ";
   cin >> square;
   
   // Check for proper formatting
   if (isalpha(square[0]))
   {
      square[0] = toupper(square[0]);
      newSquare[0] = square[0];
      newSquare[1] = square[1];
   }
   else
   {
      square[1] = toupper(square[1]);
      newSquare[0] = square[1];
      newSquare[1] = square[0];
   }
   
   // Convert to coordinates
   isValid = getCoordinates(newSquare, coordinates);
   
   // Return if not valid
   if (!isValid)
   {
      return;
   }
   
   // Make sure the value isn't read-only
   if (sudoku[coordinates[0]][coordinates[1]] > 0)
   {
      cout << "ERROR: Square '" << newSquare[0] << newSquare[1]
           << "' is read-only\n";
      return;
   }
   
   // Compute possible values for that square
   computeValues(sudoku, coordinates, values);
   
   // Display possible values
   cout << "The possible values for '" << newSquare[0] << newSquare[1]
        << "' are: ";
   
   // Display every possible value
   for (int i = 0; i < 9; i++)
   {
      // Only display the value if it's a number other than 0
      if (values[i] != 0)
      {
         cout << values[i];
         
         // Put a comma as long as it's not the last in it's series
         if (values[i + 1] != 0)
         {
            cout << ", ";
         }
      }
      
      // If already displayed all the possible values, get out
      // of for loop to avoid unnecessary comparisons
      else
      {
         break;
      }
   }
   cout << endl;
}

/**********************************************************************
* Convert the sudoku coordinates into square to interact with user
***********************************************************************/
void findSquare(int coord[], char square[])
{
   // Convert Row
   switch (coord[0])
   {
      case 0:
         square[0] = 'A';
         break;
      case 1:
         square[0] = 'B';
         break;
      case 2:
         square[0] = 'C';
         break;
      case 3:
         square[0] = 'D';
         break;
      case 4:
         square[0] = 'E';
         break;
      case 5:
         square[0] = 'F';
         break;
      case 6:
         square[0] = 'G';
         break;
      case 7:
         square[0] = 'H';
         break;
      case 8:
         square[0] = 'I';
         break;
      default:
         break;
   }

   // Convert Column
   switch (coord[1])
   {
      case 0:
         square[1] = '1';
         break;
      case 1:
         square[1] = '2';
         break;
      case 2:
         square[1] = '3';
         break;
      case 3:
         square[1] = '4';
         break;
      case 4:
         square[1] = '5';
         break;
      case 5:
         square[1] = '6';
         break;
      case 6:
         square[1] = '7';
         break;
      case 7:
         square[1] = '8';
         break;
      case 8:
         square[1] = '9';
         break;
      default:
         break;
   }
}

/**********************************************************************
* Convert the sudoku square into coordinates to locate values in array
***********************************************************************/
bool getCoordinates(string square, int coordinates[])
{
   bool isValid = true;
   int i = 0;
   int j = 1;

   // Determine if the row or column was described first
   if (isalpha(square[0]))
   {
      i = 1;
      j = 0;
   }

   // Find Row Coordinate
   switch (square[i])
   {
      case '1':
         coordinates[0] = 0;
         break;
      case '2':
         coordinates[0] = 1;
         break;
      case '3':
         coordinates[0] = 2;
         break;
      case '4':
         coordinates[0] = 3;
         break;
      case '5':
         coordinates[0] = 4;
         break;
      case '6':
         coordinates[0] = 5;
         break;
      case '7':
         coordinates[0] = 6;
         break;
      case '8':
         coordinates[0] = 7;
         break;
      case '9':
         coordinates[0] = 8;
         break;
      default: // If invalid, display error message
         cout << "ERROR: Square " << square[0] << square[1]
              << " is invalid\n";
         return false;
         break;
   }

   // Make sure it's a capital
   square[j] = toupper(square[j]);
   
   // Find Column Coordinate
   switch (square[j])
   {
      case 'A':
         coordinates[1] = 0;
         break;
      case 'B':
         coordinates[1] = 1;
         break;
      case 'C':
         coordinates[1] = 2;
         break;
      case 'D':
         coordinates[1] = 3;
         break;
      case 'E':
         coordinates[1] = 4;
         break;
      case 'F':
         coordinates[1] = 5;
         break;
      case 'G':
         coordinates[1] = 6;
         break;
      case 'H':
         coordinates[1] = 7;
         break;
      case 'I':
         coordinates[1] = 8;
         break;
      default:
         
         // If invalid, display error message
         cout << "ERROR: Square " << square[0] << square[1]
              << " is invalid\n";
         return false;
         break;
   }
   return true;
}

/**********************************************************************
* Asks user for a square to edit, and then changes the value if the
* desired value is a possible value.
***********************************************************************/
void editSquare(int sudoku[][COL_SIZE])
{
   string square;
   int coordinates[1];
   int values[9];
   int newValue;
   string newSquare;
   
   // Get the coordinates of the square
   cout << "What are the coordinates of the square: ";
   cin >> square;
   
   // Check for proper formatting
   if (isalpha(square[0]))
   {
      square[0] = toupper(square[0]);
      newSquare[0] = square[0];
      newSquare[1] = square[1];
   }
   else
   {
      square[1] = toupper(square[1]);
      newSquare[0] = square[1];
      newSquare[1] = square[0];
   }

   // Convert to coordinates
   getCoordinates(newSquare, coordinates);
   
   // Make sure it's a blank or editable square
   if (sudoku[coordinates[0]][coordinates[1]] > 0)
   {
      cout << "ERROR: Square '" << newSquare[0] << newSquare[1]
           << "' is read-only\n";
      return;
   }
   
   // Ask for the new value at that square
   cout << "What is the value at '" << newSquare[0] << newSquare[1] << "': ";
   cin >> newValue;
   
   // Compute possible values for that square
   computeValues(sudoku, coordinates, values);
   
   // Determine if the requested value is a possible value
   bool isValid = false;
   for (int i = 0; i < 9; i++)
   {
      if (newValue == values[i])
      {
         isValid = true;
      }
   }
   
   // Change value if it's valid
   if (isValid)
   {
      sudoku[coordinates[0]][coordinates[1]] = -newValue;
   }
   
   // Tell the user if it's invalid
   else
   {
      cout << "ERROR: Value '" << newValue << "' in square '"
           << newSquare[0] << newSquare[1] << "' is invalid\n";
   }
}

/**********************************************************************
* Determines what values are possible for any given square
***********************************************************************/
void computeValues(int sudoku[][COL_SIZE], int coordinates[], int values[])
{
   // Initialize all the possible values to 0
   for (int q = 0; q < 9; q++)
   {
      values[q] = 0;
   }
   
   // num represents placement in array   
   int num = 0;

   // Try every number to see if it's a possible value
   for (int i = 1; i < 10; i++)
   {
      bool isVal = true;
      
      for (int j = 0; j < 9; j++)
      {
         // If that number is equal to a number in the same row, set to false
         if ((sudoku[coordinates[0]][j] == i) ||
             (sudoku[coordinates[0]][j] == -i))
         {
            isVal = false;
         }
         
         // If that number is equal to a number in the same column,
         // set to false
         else if ((sudoku[j][coordinates[1]] == i) ||
                  (sudoku[j][coordinates[1]] == -i))
         {
            isVal = false;
         }
      }
      
      // If that number is the same as one in it's section, set to false
      if (computeSection(sudoku, coordinates, i))
      {
         isVal = false;
      }
      
      // If it's the number isn't the same as one in row or column, set it to
      // be a possible value
      if (isVal == true)
      {         
         values[num] = i;

         // Increment placement in array
         num++;
      }
   }
}

/**********************************************************************
* Determine if a desired value is already in a section
***********************************************************************/
bool computeSection(int sudoku[][COL_SIZE], int coordinates[], int number)
{
   // Determine the row coordinate for first row in section
   int firstRowCoor = (coordinates[0] - (coordinates[0] % 3));
   
   // Determine the column coordinate for first column in section
   int firstColCoor = (coordinates[1] - (coordinates[1] % 3));
   
   // Check every value 3 down, and 3 across
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         // If there's the same number, return true
         if ((sudoku[firstRowCoor + i][firstColCoor + j] == number) ||
            (sudoku[firstRowCoor + i][firstColCoor + j] == -number))
         {
            return true;
         }
      }
   }
   
   // Otherwise return false
   return false;
}

/**********************************************************************
* Write the sudoku array to a file
***********************************************************************/
void writeFile(int sudoku[][COL_SIZE])
{
   // Get the name of the file to write to
   char outFileName[FILE_SIZE];
   getOutFileName(outFileName);

   // Open output stream
   ofstream fout(outFileName);

   // Write the file by row, then by column
   for (int i = 0; i < ROW_SIZE; i++)
   {
      for (int j = 0; j < COL_SIZE; j++)
      {
         fout << sudoku[i][j];
         if (j != (COL_SIZE - 1))
         {
            fout << " ";
         }
         else
         {
            fout << endl;
         }
      }
   }

   // Close the file
   fout.close();

   cout << "Board written successfully\n";
   return;
}

/**********************************************************************
* Prompt the user for the name of the file to write to
***********************************************************************/
void getOutFileName(char outFileName[])
{
   // Prompt for sudoku file to write to
   cout << "What file would you like to write your board to: ";
   
   // Get the sudoku file to write to
   cin >> outFileName;
}
