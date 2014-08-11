#include <iostream>
#include <math.h>
using namespace std;

int main()
{
   int x;
   int y;
   char op;
   while (true)
   {
      cout << "> ";
      cin >> x >> op >> y;
      switch (op)
      {
         case '%':
         {
            cout << (x % y) << endl;
            break;
         }
         case '+':
         {
            cout << (x + y) << endl;
            break;
         }
         case '-':
         {
            cout << (x - y) << endl;
            break;
         }
         case '*':
         {
            cout << (x * y) << endl;
            break;
         }
         case '/':
         {
            cout << (x / y) << endl;
            break;
         }
         case '^':
         {
            cout << (pow(x, y)) << endl;
            break;
         }
         case 'q':
         {
            return 0;
         }
         default:
            break;
      }
   }
   return 0;
}
