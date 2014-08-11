/********************************************************************
*
********************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "dllist.cpp"
#include <math.h>
using namespace std;

/********************************************************************
*
********************************************************************/
class BIG
{
   public:
      BIG();
      BIG(int number);
      BIG(string number);
   
      int  segment(int seg);
      int  length();
   
      void setDigits(string number);
      void setDigits(int number);
   
      BIG  operator +  (BIG &number);
      void operator += (BIG &number);
   
      BIG& operator =  (int    number);
      BIG& operator =  (string number);

      bool operator <  (BIG &number);
      bool operator >  (BIG &number);
      bool operator <= (BIG &number);
      bool operator >= (BIG &number);
      bool operator == (BIG &number);
   
   private:
      LList<int> digits;
      int sToI(string number);
      void add(int number, int seg);
};

ostream& operator << (ostream& out, BIG number);

/********************************************************************
*
********************************************************************/
int main()
{
   BIG A;
   A = "999999999";
   BIG B;
   B = 1;
   B += A;
//   BIG B;
//   B = 1;
//   cout << "A: " << A << endl;
//   cout << "B: " << B << endl;  
//   cout << "A + B: " << A + B << endl;
   BIG C;
   C = "1";
   C += B;
   cout << "C: " << C << endl;
   return 0;
}

/********************************************************************
*
********************************************************************/
ostream& operator << (ostream& out, BIG number)
{
   int size = number.length() - 1;
   for (int i = size; i >= 0; i--)
   {
      if (i != size)
         out << setfill('0') << setw(9);
      out << number.segment(i);
   }
   out << setfill(' ');
   return out;
}

/********************************************************************
*
********************************************************************/
BIG::BIG()
{
   digits.insert(0);
}

/********************************************************************
*
********************************************************************/
BIG::BIG(int number)
{
   digits.insert(number);
}

/********************************************************************
*
********************************************************************/
BIG::BIG(string number)
{
   setDigits(number);
}

/********************************************************************
*
********************************************************************/
int BIG::segment(int seg)
{
   return digits[seg];
}

/********************************************************************
*
********************************************************************/
int BIG::length()
{
   return digits.size();
}

/********************************************************************
*
********************************************************************/
void BIG::setDigits(string number)
{
   digits.clear();
   int size = number.size() - 1;
   string seg = "";
   for (int i = size; i >= 0; i--)
   {
      seg = number[i] + seg;
      if ((((size - i + 1) % 9) == 0) || (i == 0))
      {
         digits.insert(sToI(seg));
         seg = "";
      }
   }
   return;
}

/********************************************************************
*
********************************************************************/
void BIG::setDigits(int number)
{
   digits.clear();
   digits.insert(number, 0);
   return;
}

/********************************************************************
*
********************************************************************/
BIG BIG::operator + (BIG &number)
{
   BIG sum;
   sum.digits = digits;
   for (int i = 0; i < number.digits.size(); i++)
      sum.add(number.digits[i], i);
   return sum;
}

/********************************************************************
*
********************************************************************/
void BIG::operator += (BIG &number)
{
   for (int i = 0; i < number.digits.size(); i++)
      add(number.digits[i], i);
   return;
}

/********************************************************************
*
********************************************************************/
int BIG::sToI(string number)
{
   int size = number.size() - 1;
   int num = 0;
   for (int i = size; i >= 0; i--)
      num += (((int)(number[i] - 48)) * pow(10, (size - i)));
   return num;
}

/********************************************************************
*
********************************************************************/
void BIG::add(int number, int seg)
{
   if (seg >= digits.size())
      digits.insert(0, seg);
   int total = number + digits[seg];
   int remainder = total / 1000000000;
   digits[seg] = total % 1000000000;
   if (remainder != 0)
   {
      if (seg < digits.size() - 1)
         add(remainder, (seg + 1));
      else
         digits.insert(remainder, digits.size());
   }
   return; 
}

/********************************************************************
*
********************************************************************/
BIG& BIG::operator = (int number)
{
   digits.clear();
   digits.insert(number);
   return *this;
}

/********************************************************************
*
********************************************************************/
BIG& BIG::operator = (string number)
{
   setDigits(number);
   return *this;
}

/********************************************************************
*
********************************************************************/
bool BIG::operator < (BIG &number)
{
   bool isLess = false;
   if (digits.size() < number.digits.size())
      isLess = true;
   else if (digits.size() == number.digits.size())
   {
      for (int i = digits.size() - 1; i >= 0; i--)
      {
         if (digits[i] < number.digits[i])
         {
            isLess = true;
            break;
         }
         else if (digits[i] != number.digits[i])
            break;
      }
   }
      
   return isLess;
}

/********************************************************************
*
********************************************************************/
bool BIG::operator > (BIG &number)
{
      bool isGreater = false;
   if (digits.size() > number.digits.size())
      isGreater = true;
   else if (digits.size() == number.digits.size())
   {
      for (int i = digits.size() - 1; i >= 0; i--)
      {
         if (digits[i] > number.digits[i])
         {
            isGreater = true;
            break;
         }
         else if (digits[i] != number.digits[i])
            break;
      }
   }
      
   return isGreater;
}

/********************************************************************
*
********************************************************************/
bool BIG::operator <= (BIG &number)
{
   return !(*this > number);
}

/********************************************************************
*
********************************************************************/
bool BIG::operator >= (BIG &number)
{
   return !(*this < number);
}

/********************************************************************
*
********************************************************************/
bool BIG::operator == (BIG &number)
{
   bool isEqual = false;
   if (digits.size() == number.digits.size())
   {
      isEqual = true;
      for (int i = 0; i < digits.size(); i++)
         if (digits[i] != number.digits[i])
            isEqual = false;
   }
   return isEqual;
}

