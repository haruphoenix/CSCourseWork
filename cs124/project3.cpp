/***********************************************************************
* Program:
*    Project 3, Madlib  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will ask for a filename of a madlib, and will then
*    prompt the user for words, will place the words in the story,
*    and will ask the user if they would like to play again.
*
*    Estimated:  6.0 hrs   
*    Actual:     16.0 hrs
*      Punctuation was so annoying, and It was hard to understand how to
*      take more than one word and put it into an array for ask questions
*      There's a weird "!" that shows up on testBed that DOESN'T
*      show up when ran normally. (Using the same madlib file)
*      No idea where that's coming from. Lastly, style checker gets
*      after me for curly braces on their own line, but they're being
*      used as chars. Each project gets harder and harder. :)
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

const int WORD_SIZE = 32;
const int FILE_SIZE = 256;
const int NAME_SIZE = 256;

int readFile(char madlib[][WORD_SIZE]);

/**********************************************************************
* Functions are called by readFile to find and change the story
**********************************************************************/
void getFileName(char fileName[NAME_SIZE]);
void askQuestions(char text[WORD_SIZE]);

/**********************************************************************
* Display Functions
***********************************************************************/
void display(char madlib[][WORD_SIZE], int numWords);
void isPunc(char symbol);

bool continuePlaying();

/**********************************************************************
* Main loops through functions until the user no longer wants to play
***********************************************************************/
int main()
{
   char madlib[FILE_SIZE][WORD_SIZE];
   int numWords;
   bool wantsToPlay = true;
   while (wantsToPlay) // While the user still wants to play
   {
      // Read the file
      numWords = readFile(madlib);
      // Display the madlib
      if (numWords != 0)
      {
         display(madlib, numWords);
      }
      // Ask the user if they would like to play again
      wantsToPlay = continuePlaying();
   }
   return 0;
}

/**********************************************************************
* Reads and manipulates the madlib. calls functions to get the file
* name, and ask questions.
**********************************************************************/
int readFile(char madlib[][WORD_SIZE])
{
   char fileName[NAME_SIZE];
   getFileName(fileName);
   ifstream fin(fileName);
   // Determine if the file exists
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return 0;
   }
   int numWords = 0;
   // While still reading, ask questions.
   while ((numWords <= FILE_SIZE) && (fin >> madlib[numWords]))
   {
      askQuestions(madlib[numWords]);
      numWords++;
   }
   // Close file
   fin.close();
   return numWords;
}

/**********************************************************************
* Asks user for name of the madlib file.
**********************************************************************/
void getFileName(char fileName[NAME_SIZE])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin >> fileName; // Get the file name
   // cin.getline to be used later. It can handle more than one word
   // so cin.ignore is important.
   cin.ignore();
   return;
}

/**********************************************************************
* Asks the user questions from the madlib.
**********************************************************************/
void askQuestions(char text[WORD_SIZE])
{
   // Only continue through this function if
   // there are words between </> operators.
   if ((text[0] != '<') || !(isalpha(text[1])))
   {
      return;
   }
   // Capitalize the first letter of each word
   text[1] = toupper(text[1]);
   // Put a tab before each question
   cout << "\t" << text[1];
   // Display each question
   for (int i = 2; text[i] != '>'; i++)
   {
      // Replace underscores with spaces
      if (text[i] == '_')
      {
         cout << " ";
      }
      // Display each letter.
      else
      {
         text[i] = tolower(text[i]);
         cout << text[i];
      }
   }
   // Get the word to replace for each question
   cout << ": ";
   cin.getline (text, WORD_SIZE);
   return;
}

/**********************************************************************
* Displays the final madlib. Calls isPunc.
***********************************************************************/
void display(char madlib[][WORD_SIZE], int numWords)
{
   cout << endl;
   for (int i = 0; i <= numWords; i++)            // Loops through words
   {
   // increment word at end
      if (madlib[i][0] != '<')        // If it's not a special character
      {
         cout << madlib[i];                         // Display each word
         
         // If it's not followed by a non-letter, and it's not at the
         // end of the file, put a space after each word
         if ((isalpha(madlib[i + 1][0])) &&
             (madlib[i + 1] != '\0'))
         {
            cout << " ";
         }
         // Otherwise, only put a space if it's followed by a colon or
         // a boolean operator, for emoticons and the like.
         else
         {
            switch (madlib[i + 1][0])
            {
               case ':':
                  cout << " ";
               case '=':
                  cout << " ";
               case '+':
                  cout << " ";
               case '-':
                  cout << " ";
               case '(':
                  cout << " ";
               default:
                  break;
            }
         }
      }
      // If there is a special character, put through the isPunc
      // function to display it.
      else
      {
         isPunc(madlib[i][1]);
         // If there are quotes, and they're in the middle of a
         // sentence, there needs to be a space after the closing
         // quotes.
         if (isalpha(madlib[i + 1][0]))
         {
            if ((madlib[i][1] == '}') ||
               (madlib[i][1] == ']'))
            {
               cout << " ";
            }
         }
      }
   }
   return;
}

/***********************************************************************
* Determines what type of punctuation to display.
***********************************************************************/
void isPunc(char symbol)
{
   switch (symbol)
   {
      case '#':
         cout << endl;
         break;
      case '{':
         cout << " \"";
         break;
      case '}':
         cout << "\"";     // Closing quotes don't have a space after in
         break;            // case they're at the end of a sentence.
      case '[':
         cout << " '";
         break;
      case ']':
         cout << "'";
         break;
      default:                       // If an unwanted value is entered
         break;                      // nothing will be displayed
   }
   return;
}

/**********************************************************************
* Find out if the user would like to continue playing
**********************************************************************/
bool continuePlaying()
{
   char response;
   // Ask if user wants to play again
   cout << endl << "Do you want to play again (y/n)? ";
   cin >> response; 
   switch (response)
   {
         // If they don't, send false to exit loop in main
      case 'n':
         cout << "Thank you for playing." << endl;
         return false;
      default:
         // Otherwise send true to continue playing.
         return true;
   }
}
