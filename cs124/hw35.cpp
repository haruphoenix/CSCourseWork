/***********************************************************************
* Program:
*    Assignment 35, Count Letters (Part 2)  
*    Brother Andreasen, CS124
* Author:
*    Haru McClellan
* Summary: 
*    This program will count the number of letters in a string using
*    pointers.
*
*    Estimated:  1.0 hrs   
*    Actual:     1.0 hrs
*      It was hard figuring out how to correctly pass a pointer into
*      a function.
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
   char *ptext;
   ptext = &text[0];
   
   // Ask User for letter to count
   cout << "Enter a letter: ";
   cin >> letter;
   cin.ignore();
   
   // Ask user for text to count letters in.
   cout << "Enter text: ";
   cin.getline(text, 256);
   
   // Call function to count amount of letters in text
   count = countLetters(letter, ptext);
   
   // Display to user number of that letter in text
   cout << "Number of '" << letter << "'s: " << count << endl;
   return 0;
}

/**********************************************************************
* Counts the number of letters in the string.
***********************************************************************/
int countLetters(char letter, char *ptext)
{
   int count = 0;
   while (*ptext != '\0')
   {
      if (*ptext == letter)
      {
         count++;
      }
      ptext++;
   }
   return count;
}
