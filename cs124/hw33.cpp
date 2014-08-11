/***********************************************************************
* Program:
*    Assignment 33, Count Letters  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will count the number of letters in a string.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      It was difficult finding out how to correctly use cin.getline.
************************************************************************/

#include <iostream>
using namespace std;

int countLetters(char letter, char text[256]);

/**********************************************************************
* Main prompts user for a line of input, calls countLetters(), and
* displays the number of letters.
***********************************************************************/
int main()
{
   char letter;
   char text[256];
   int count;
   // Ask User for letter to count
   cout << "Enter a letter: ";
   cin >> letter;
   cin.ignore();
   // Ask user for text to count letters in.
   cout << "Enter text: ";
   cin.getline(text, 256);
   // Call function to count amount of letters in text
   count = countLetters(letter, text);
   // Display to user number of that letter in text
   cout << "Number of '" << letter << "'s: " << count << endl;
   return 0;
}

/**********************************************************************
* Counts the number of letters in the string.
***********************************************************************/
int countLetters(char letter, char text[256])
{
   int count = 0;
   for (int i = 0; text[i]; i++)
   // So long as there are more characters in string
   {
      if (text[i] == letter)
   // If the character is the same as the letter we're counting
      {
         count++; // Add one to count
      }
   }
   return count; // Return total number of that letter
}
