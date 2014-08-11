#include <iostream>
#include <string>
using namespace std;

const string BLUE   = "\E[7;34m";
const string GREEN  = "\E[7;32m";
const string RED    = "\E[7;31m";

const string YELLOW = "\E[7;33m";
const string PURPLE = "\E[7;35m";

const string BROWN  = "\E[7;33m";
const string CYAN   = "\E[7;36m";
const string GRAY   = "\E[7;37m";

const string WHITE  = "\E[7;0m"; //Second as 0 is default color for console
const string BLACK  = "\E[7;30m";

int main(int argc, char* argv[])
{
   char* pColor = argv[1];
   string color = (string)pColor;
   if (color == "blue")
      cout << BLUE;
   else if (color == "green")
      cout << GREEN;
   else if (color == "red")
      cout << RED;
   
   else if (color == "yellow")
      cout << YELLOW;
   else if (color == "purple")
      cout << PURPLE;
   else if (color == "brown")
      cout << BROWN;
   else if (color == "cyan")
      cout << CYAN;
   else if (color == "gray")
      cout << GRAY;
   
   else if (color == "black")
      cout << BLACK;
   else if (color == "white")
      cout << WHITE;
   return 0;
}
