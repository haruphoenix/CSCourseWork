#include <iostream>
#include <string>
using namespace std;

const string BLUE   = "\E[0;34m"; // First number describes bg color. Second fg color. 22 is whatever bg was.
const string GREEN  = "\E[0;32m";
const string RED    = "\E[0;31m";

const string YELLOW = "\E[0;33m";
const string PURPLE = "\E[0;35m";

const string BROWN  = "\E[0;33m";
const string CYAN   = "\E[0;36m";
const string GRAY   = "\E[0;37m";

const string WHITE  = "\E[0;0m";
const string BLACK  = "\E[0;30m";

const string UP     = "\E[A";
const string CLEAR  = "\e[2K";

int main(int argc, char* argv[])
{
   char* pColor = argv[1];
   string color = (string)pColor;
   if (color == "blue")
      cout << UP << CLEAR << BLUE;
   else if (color == "green")
      cout << UP << CLEAR << GREEN;
   else if (color == "red")
      cout << UP << CLEAR << RED;
   
   else if (color == "yellow")
      cout << UP << CLEAR << YELLOW;
   else if (color == "purple")
      cout << UP << CLEAR << PURPLE;
   else if (color == "brown")
      cout << UP << CLEAR << BROWN;
   else if (color == "cyan")
      cout << UP << CLEAR << CYAN;
   else if (color == "gray")
      cout << UP << CLEAR << GRAY;
   
   else if (color == "black")
      cout << UP << CLEAR << BLACK;
   else if (color == "white")
      cout << UP << CLEAR << WHITE;
   return 0;
}
