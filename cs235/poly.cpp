/***********************************************************************
* Program:
*    Assignment 08, Polynomials
*    Brother Ercanbrack, CS 235
* Author:
*    Modified by Brother Ercanbrack & Haru McClellan
* Summary: 
*    This program reads two polynomials from a file, displays them,
*    adds them together, evaluates the result for a given value of x and
*    displays the result.
***********************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

const int MAX_ITEMS = 50;

/******************************************************************************
*  Author: Brother Cameron, 10/9/2001
*
*  Purpose: Defines classes for a Term and a Polynomial
******************************************************************************/
class Term
{
   private:
      float coeff;
      int   expon;
 
   public:
      Term();                   // --- Creates empty Term
      Term(float c, int e);     // --- Creates Term object with coeff. c 
                                // and expon. e
      float getCoeff(void);     // --- returns coeff of term
      int   getExpon(void);     // --- returns expon of term
      void  setCoeff(float c);  // --- sets term's coeff. to c
      void  setExpon(int c);    // --- sets term's expon to c
   
      float operator () (float x); // Evaluate Term
      bool  operator <  (Term& other); // Compare exponents
      bool  operator >  (Term& other);
      bool  operator == (Term& other);
      bool  operator <= (Term& other);
      bool  operator >= (Term& other);
};

ostream& operator << (ostream& out, Term& t1);

/***********************************************************************
* Class containing an array of Terms and the functions to operate on them
***********************************************************************/
class Poly
{
   private:
      int numTerms;            // number of terms in polynomial
      int maxItems;            // array capacity
      Term *terms;             // dynamically allocated array of terms
      void order(void);         // puts terms in correct order.

   public:
      Poly();                  // creates empty polynomial
      Poly(const Poly &poly);  // copy constructor
      ~Poly();                 // destructor free dynamically allocate ptrs.
      void insertTerm(Term t); // inserts Term t into polynomial
      int getNumTerms(void);   // returns number of terms in array
      Term getTerm(int index); // returns term at index
      Poly& operator = (const Poly& rightSide);//overloaded assignment operator
      float operator () (float x);
};

ostream& operator << (ostream& out, Poly& op1);
istream& operator >> (istream& in, Poly& op1);
Poly operator + (Poly& op1, Poly& op2);
template <class T>
void sort(T* array, int first, int last);
template <class T>
int partition(T* array, int first, int last);

/***********************************************************************
* Main reads the file, outputs the polynomials, adds them together and
* displays the results.  Don't modify this function!!!!!
***********************************************************************/
int main(int argc, char* argv[])
{
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      exit(1);
   }
   
   Poly f;
   Poly g;
   Poly p;

   int value (0); // value of x for evaluation
   inFile >> f;
   inFile >> g;

   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   // make copies of the polynomials
   Poly temp1(f);
   Poly temp2(g);

   // add polynomials f and g
   p = f + g;
   cout << "\nP(x) = (F + G)(x) = " << p << endl;

   // read in a value for X
   inFile >> value;

   // evaluate the polynomial
   cout << "P(" << value << ") = " << p(value) << endl << endl;

   // swap temp1 and temp2 - shouldn't change f & g
   Poly temp3(temp2);
   temp2 = temp1;
   temp1 = temp3;

   // Insert a new term 8x^6
   temp1.insertTerm(Term(8,6));

   cout << "temp1(x) is same as 8x^6 + G(x) or " << temp1 << endl;
   cout << "temp2(x) is same as F(x) or " << temp2 << endl;
   cout << "temp3(x) is same as G(x) or " << temp3 << endl << endl;

   cout << "Original functions were:" << endl;
   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   inFile.close();
   return 0;
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - none
*  Return Value - none
*
*  Purpose - Constructor function for Term class.  Creates empty Term.
****************************************************************************/
Term::Term(void)
{
   coeff = 0.0;
   expon = -1;  // --- guarantees insert will occur
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - a float that is the coefficient and a int that is the expon.
*  Return Value - None
*
*  Purpose: Creates a Term object set to coefficient and expon.
****************************************************************************/
Term::Term(float c, int e)
{
   coeff = c;
   expon = e;
}

/*****************************************************************************
*
*  Function: getCoeff
*
*  Parameters: None
*  Return Value - an integer representing coeff.
*
*  Purpose: Returns the coefficient data member of Term class
****************************************************************************/
float Term::getCoeff(void)
{
   return (coeff);
}

/***************************************************************************
*  Function: getExpon
*  Purpose: Returns the expon data member of Term class
*
*  Parameters - none
*  Return value - integer, representing expon.
***************************************************************************/
int Term::getExpon(void)
{
   return (expon);
}

/***************************************************************************
*  Function: setCoeff
*  Purpose: sets c to data member coeff in Term class
*
*  Parameters - float representing coeff
*  Return value - none
**************************************************************************/
void Term::setCoeff(float c)
{
   coeff = c;
}

/***************************************************************************
*  Function: setExpon
*  Purpose: sets e to data member expon in Term class
*
*  Parameters - int representing expon
*  Return value - none
**************************************************************************/
void Term::setExpon(int e)
{
   expon = e;
}

/***********************************************************************
* overloaded () operator that evaluates the term for the value
* within the parentheses
***********************************************************************/
float Term::operator () (float x)
{
   return (pow(x, expon) * coeff);
}

/***********************************************************************
* Compares two terms, returns true if first term has a smaller exponent 
***********************************************************************/
bool Term::operator < (Term& other)
{
   if (expon < other.expon)
      return true;
   else
      return false;
}

/***********************************************************************
* Compares two terms, returns true if first term has a larger exponent
***********************************************************************/
bool Term::operator > (Term& other)
{
   if (expon > other.expon)
      return true;
   else
      return false;
}

/***********************************************************************
* Compares two terms, returns true if first term has an equal exponent
***********************************************************************/
bool Term::operator == (Term& other)
{
   if (expon == other.expon)
      return true;
   else
      return false;
}

/***********************************************************************
* Compares two terms, returns true if first term has a smaller or
* equal exponent.
***********************************************************************/
bool Term::operator <= (Term& other)
{
   if ((expon < other.expon) || (expon == other.expon))
      return true;
   else
      return false;
}

/***********************************************************************
* Compares two terms, returns true if first term has a larger or
* equal exponent.
***********************************************************************/
bool Term::operator >= (Term& other)
{
   if ((expon > other.expon) || (expon == other.expon))
      return true;
   else
      return false;
}

/***************************************************************************
*
*  Function: Poly
*  Purpose:  Poly class constructor to create an empty Poly object of 50 
*            term.
*
*  Parameters - none
*  Return value - none
**************************************************************************/
Poly::Poly()
{
   numTerms = 0;
   maxItems = MAX_ITEMS;
   terms = new Term [maxItems];
}

/********************************************
 * Destructor
 *********************************************/
Poly::~Poly()
{
   delete [] terms;
}

/*******************************************
 * copy constructor
 ********************************************/
Poly::Poly(const Poly &poly)
{
   numTerms = poly.numTerms;
   maxItems = poly.maxItems;
   terms = new Term [maxItems];
   for (int i = 0; i < numTerms; i++)
   {
      terms[i] = poly.terms[i];
   }
}

/*******************************************
 * overloaded Assignment operator
 ********************************************/
Poly& Poly::operator = (const Poly &rightSide)
{
   delete [] terms;
   numTerms = rightSide.numTerms;
   maxItems = rightSide.maxItems;
   terms = new Term [maxItems];
   for (int i = 0; i < numTerms; i++)
   {
      terms[i] = rightSide.terms[i];
   }
   return *this;
}

/***********************************************************************
* Inserts a term into a polynomial in the proper location.  If a term
* is inserted with a duplicate exponent, the terms are combined.  If any
* coefficient goes to zero that term is removed from the polynomial.
***********************************************************************/
void Poly::insertTerm(Term t)
{
   if (numTerms == maxItems)
   {
      Term* temp = new Term[maxItems * 2];
      for (int i = 0; i < numTerms; i++)
      {
         temp[i] = terms[i];
      }
      delete [] terms;
      terms = temp;
      maxItems *= 2;
   }

   bool duplicate = false;
   int loc = numTerms;
   
   for (int i = 0; i < numTerms; i++)
   {
      if (t.getExpon() == terms[i].getExpon())
      {
         duplicate = true;
         loc = i;
         break;
      }
   }

   if (duplicate)
   {
      terms[loc].setCoeff(terms[loc].getCoeff() + t.getCoeff());
   }
   else
   {
      terms[numTerms] = t;
      numTerms++;
   }
   
   order();
   
   return;
}

/***********************************************************************
* Puts terms in correct order, and removes terms with a coefficient of 0
***********************************************************************/
void Poly::order(void)
{
   for (int i = 0; i < numTerms; i++)
   {
      if (terms[i].getCoeff() == 0)
      {
         terms[i] = terms[numTerms - 1];
         numTerms--;
      }
   }
   
   sort(terms, 0, (numTerms - 1));
   return;
}

/***********************************************************************
* Accessor function that returns the number of Terms in the array
***********************************************************************/
int Poly::getNumTerms()
{
   return (numTerms);
}

/***********************************************************************
* Accessor function that returns the Term at a given index
***********************************************************************/
Term Poly::getTerm(int index)
{
   return (terms[index]);
}

/***********************************************************************
* overloaded () operator that evaluates the polynomial for the value
* within the parentheses
***********************************************************************/
float Poly::operator () (float x)
{
   float result = 0;
   for (int i = 0; i < numTerms; i++)
   {
      result += terms[i](x);
   }
   return result;
}

/***********************************************************************
* overloaded + operator that combines two polynomials and returns the
* result as a polynomial
***********************************************************************/
Poly operator + (Poly& op1, Poly& op2)
{
   Poly newPoly = op1;
   for (int i = 0; i < op2.getNumTerms(); i++)
   {
      newPoly.insertTerm(op2.getTerm(i));
   }
   return newPoly;
}

/***********************************************************************
* overloaded << operator that outputs the term in the proper format
***********************************************************************/
ostream& operator << (ostream& out, Term& t1)
{
   float coeff = t1.getCoeff();
   int expon = t1.getExpon();
   if (coeff < 0)
      coeff = -coeff;
   if ((coeff > 1) || (expon == 0))
      out << coeff;
   if (((coeff >= 1) || (coeff <= -1)) && (expon >= 1))
   {
         out << "x";
      if (expon > 1)
         out << "^" << expon;
   }
   return out;
}

/***********************************************************************
* overloaded << operator that outputs the polynomial in the proper format
***********************************************************************/
ostream& operator << (ostream& out, Poly& op1)
{
   int numTerms = op1.getNumTerms();
   Term temp;
   if (numTerms > 0)
   {
      if (op1.getTerm(0).getCoeff() < 0)
         out << "-";
   }
   
   for (int i = 0; i < numTerms; i++)
   {
      temp = op1.getTerm(i);
      out << temp;
      if ((i + 1) != numTerms)
      {
         if (op1.getTerm(i + 1).getCoeff() > 0)
            out << " + ";
         else if (op1.getTerm(i + 1).getCoeff() < 0)
            out << " - ";
      }
   }
   return out;
}

/***********************************************************************
* overloaded >> operator that reads an entire polynomial into an array
* of Terms in the proper order.
***********************************************************************/
istream& operator >> (istream& in, Poly& op1)
{
   int numTerms;
   Term temp;
   float coeff;
   int   expon;
   in >> numTerms;
   for (int i = 0; i < numTerms; i++)
   {
      in >> coeff >> expon;
      temp.setCoeff(coeff);
      temp.setExpon(expon);
      op1.insertTerm(temp);
   }
   return in;
}

/*************************************************************************
 * Recursively sorts an array in descending order. Requires, the array
 * as well as first and last positions of the array to be sorted.
 ************************************************************************/
template <class T>
void sort(T* array, int first, int last)
{
   if (first < last)
   {
      int middle = partition(array, first, last);
      sort(array, first, middle);
      sort(array, middle + 1, last);
   }
   return;
}

/*************************************************************************
 * Divides an array into partitions to sort. Requires, the array, as well
 * as first and last places to sort.
 ************************************************************************/
template <class T>
int partition(T* array, int first, int last)
{
   T pivot = array[first];
   T temp;
   while (first < last)
   {
      while (pivot > array[last])
         last--;
      while (pivot < array[first])
         first++;
      if (first < last)
      {
         temp = array[first];
         array[first] = array[last];
         array[last] = temp;
      }
   }
   return last;
}
