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

const string LEFT   = "\E[D";
const string RIGHT  = "\E[C";
const string UP     = "\E[A";
const string DOWN   = "\E[B";

const string CLEAR  = "\e[2K";

int main(int argc, char* argv[])
{
   char* pAction = argv[1];
   string action = (string)pAction;
   if (action == "left")
      cout << LEFT;
   else if (action == "right")
      cout << RIGHT;
   else if (action == "up")
      cout << UP;
   else if (action == "down")
      cout << DOWN;
   
   else if (action == "clear")
      cout << CLEAR;
   return 0;
}
