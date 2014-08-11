#include <iostream>
using namespace std;

int main()
{
   char what;
   cin >> what;
   if (isalpha(what))
      cout << "isalpha\n";
   return 0;
}
