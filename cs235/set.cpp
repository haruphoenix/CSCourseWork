/*****************************************************************************
* Program:
*    Assignment 01, Set Class
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This Program reads in a list of numbers from a file, and stores them into
*    sets which can have operations done on them. Displays examples of the
*    different operations.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int SET_SIZE = 100;

/*****************************************************************************
* A set with an unordered group of ints, without any numbers repeating.
* has functions available to add integers to the set, search the set for a
* particular integer, or intersect, combine, or find the difference of two
* sets. Can display the set in numerical order from least to greatest.
******************************************************************************/
class Set
{
   
   public:
      Set();
      Set(int theSize);
      Set(const Set &orig);
      ~Set();

      void operator = (Set newSet);

      void add(int num);
      int  getSize() const {return size;};
      int  getMax()  const {return maxSize;};
      bool search(int num);

      Set operator && (Set otherSet); // Intersection
      Set operator || (Set otherSet); // Union
      Set operator -  (Set otherSet); // Difference 

      void sort();
      void display();
   
   private:
      int* array;
      int size;
      int maxSize;
   
};

/*****************************************************************************
* Main takes in parameters from the command line of files to test this program
* with.  It will read the number of ints for line 2 and 4, and then place the
* ints into two different sets.  Afterwards it will find the result of the
* two sets after having the operations, intersection, union, and difference
* done on them.
******************************************************************************/
int main(int argc, char* argv[])
{
   ifstream fin;

   for (int i = 1; i < argc; i++) // Lets you do more than one file at once
   {
      char* pFilename = argv[i];
      fin.open(pFilename);
      try
      {
         if (fin.fail())          // Make sure file names are valid
         {
            throw pFilename;
         }
         int numInts;
         int num;
      
         fin >> numInts;          // Read in number of ints in the first set
         Set a(numInts);          // and make a new set with those values
         for (int i = 0; i < numInts; i++)
         {
            fin >> num;
            a.add(num);
         }
      
         fin >> numInts;          // Read in number of ints in the second set
         Set b(numInts);          // and make a new set with those values
         for (int i = 0; i < numInts; i++)
         {
            fin >> num;
            b.add(num);
         }

         cout << "Set A:\n";      // Display sets and operations of them
         a.display();

         cout << "\nSet B:\n";
         b.display();

         cout << "\nIntersection of A and B:\n";
         Set c = a && b;
         c.display();

         cout << "\nUnion of A and B:\n";
         Set d = a || b;
         d.display();

         cout << "\nDifference of A and B:\n";
         Set e = a - b;
         e.display();

         cout << "\nDifference of B and A:\n";
         Set f = b - a;
         f.display();

         cout << endl;
      }
      catch (char* file)
      {
         cout << "Could not open file " << file << ".\n";
      }
      fin.close();
   }
   
   return 0;
}


/*****************************************************************************
* Constructor for a new set. Sets the array size to the default described at
* the head of this file. Initializes all values in the set to zero. and sets
* the size to zero.
******************************************************************************/
Set::Set()
{
   try
   {
      size = 0;
      maxSize = SET_SIZE;
      array = new(nothrow) int[maxSize];
      if (array == NULL)
         throw 0;
      for (int i = 0; i < maxSize; i++)
      {
         array[i] = 0;
      }
   }
   catch (int e)
   {
      cout << "Error: Failure to allocate memory in"
           << "Set::Set()\n";
   }
}

/*****************************************************************************
* Constructor initializes set to a size described at declaration. Allocated
* memory for the new set, and initializes all values to zero.
******************************************************************************/
Set::Set(int theSize)
{
   try
   {
      size = 0;
      maxSize = theSize;
      array = new(nothrow) int[maxSize];
      if (array == NULL)
         throw 0;
      for (int i = 0; i < maxSize; i++)
      {
         array[i] = 0;
      }
   }
   catch (int e)
   {
      cout << "Error: Failure to allocate memory in"
           << " Set::Set(int theSize)\n";
   }
}

/*****************************************************************************
* Copy constructor copies the values of the original set and makes an exact
* duplicate.
******************************************************************************/
Set::Set(const Set &orig)
{
   try
   {
      size = orig.size;
      maxSize = orig.maxSize;
      array = new(nothrow) int[maxSize];
      if (array == NULL)
         throw 0;
      for (int i = 0; i < maxSize; i++)
      {
         array[i] = orig.array[i];
      }
   }
   catch (int e)
   {
      cout << "Error: Failure to allocate memory in"
           << " Set::Set(const Set &orig)\n";
   }
}

/*****************************************************************************
* Assigns one set to another as far as it is capable. Will not increase the
* max size of the left side parameter to match the right side unless the left
* side parameter is being declared also, in which case the copy constructor
* will be called.
******************************************************************************/
void Set::operator = (Set newSet)
{
   for (int i = 0; i < newSet.maxSize; i++)
   {
      if (i == maxSize)
      {
         break;
      }
      else
      {
         array[i] = newSet.array[i];
      }
   }
   return;
}

/*****************************************************************************
* Destructor, deletes the array of integers.
******************************************************************************/
Set::~Set()
{
   delete [] array;
}

/*****************************************************************************
* Adds an integer to the set. Will not add duplicates. Parameter is the number
* to add to the set. No return.
******************************************************************************/
void Set::add(int num)
{
   if ((!search(num)) && (size < maxSize))
   {
      array[size] = num;
      size++;
   }
   return;
}

/*****************************************************************************
* Searches a set for a given number. The number to search for is the parameter.
* If the number is found, the function will return true. If the number is not
* found the function will return false.
******************************************************************************/
bool Set::search(int num)
{
   bool inSet = false;
   for (int i = 0; i < size; i++)
   {
      if (num == array[i])
         inSet = true;
   }
   return inSet;
}

/*****************************************************************************
* Compares two sets and returns a set with only the numbers they have in common
******************************************************************************/
Set Set::operator && (Set otherSet)
{
   int theSize;
   if (size < otherSet.size)
      theSize = size;
   else
      theSize = otherSet.size;

   Set newSet(theSize);

   for (int i = 0; i < size; i++)
   {
      if (otherSet.search(array[i]))  // Check to see if the number is in
         newSet.add(array[i]);        // both sets.
   }
   
   return newSet;
}

/*****************************************************************************
* Compares two sets and returns a set having all the numbers from both sets.
******************************************************************************/
Set Set::operator || (Set otherSet)
{
   int theSize = (size + otherSet.size);
   Set newSet(theSize);

   int bigSize;
   if (size > otherSet.size)
      bigSize = size;
   else
      bigSize = otherSet.size;
   
   for (int i = 0; i < bigSize; i++)
   {
      if (i < size)                      // Add all numbers from both sets.
         newSet.add(array[i]);
      if (i < otherSet.size)
         newSet.add(otherSet.array[i]);
   }
   
   return newSet;
}

/*****************************************************************************
* Compares two sets and returns a set with only the items in the first set
* that are not in common with the second set.
******************************************************************************/
Set Set::operator - (Set otherSet)
{
   int theSize;  
   if (size > otherSet.size)
      theSize = size;
   else
      theSize = otherSet.size;

   Set newSet(size);
   
   for (int i = 0; i < size; i++)
   {
      if (!otherSet.search(array[i])) // Make sure it's not in the first set
         newSet.add(array[i]);
   }
   
   return newSet;
}

/*****************************************************************************
* Simple bubble sort. Sorts the set in numerical order. Smallest to largest
******************************************************************************/
void Set::sort()
{
   int temp;
   bool isSorted = false;
   for (int i = 0; (i < size) && !isSorted; i++)
   {
      isSorted = true;
      for (int j = 0; j < (size - 1); j++)
      {
         if (array[j + 1] < array[j])  // compare numbers
         {
            temp = array[j];           // Switch numbers
            array[j] = array [j + 1];
            array[j + 1] = temp;
            isSorted = false;
         }
      }
   }
   return;
}

/*****************************************************************************
* Calls function to sort the set, and then displays it in rows of 10
******************************************************************************/
void Set::display()
{
   int count = 0;
   sort();
   for (int i = 0; i < size; i++)
   {
      count++;
      cout << "  " << setw(2) << array[i];
      if ((count % 10) == 0)
         cout << endl;
   }
   if (((count % 10) != 0) || (count == 0))
      cout << endl;
   return;
}
