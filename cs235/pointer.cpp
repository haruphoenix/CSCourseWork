#include <iostream>
using namespace std;



int main()
{
   char** x = new char*[10];
   char m = 'a';
   x[0] = &m;
   cout << *x << endl;
   return 0;
}
