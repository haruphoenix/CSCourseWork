/*************************************************************************
* Predicate class declaration (IMPLEMENT in your own pq.cpp file.)
* (Add to this file, if desired, but do NOT change what is already in it.)
*************************************************************************/
#include <iostream>
#include <string>
using namespace std;

const int MAX_PROPS = 10;

/**************************************************************************
* 
**************************************************************************/
class Item
{
public:
   Item(void);
   Item(const Item& original);
   Item(int max);
   ~Item(void);
   void   name   (string theName); // Names the item
   string name   (void) const;     // Returns name of item
   int    size   (void) const;     // Returns number of properties
   void   addProp(string prop);    // Adds a property to an Item
   string prop   (int num);        // Returns specified property

   Item& operator = (const Item& rtSide);
        
private:
   int     maxSize;
   int     numProps;
   string  itemName;
   string* property;
};

#ifndef _PREDICATE_H
#define _PREDICATE_H 1
/**************************************************************
* The Predicate class is an abstract base class with pure virtual
* abstract functions (per the =0 suffix).
***************************************************************/
template<class T1, class T2>
class Predicate
{
public:
   virtual bool isTrue (T1 x, T2 y) = 0;
   virtual bool isFalse(T1 x, T2 y) = 0;
   bool forAllForAll   (T1 setX[], int sizeX, T2 setY[], int sizeY);
   bool forAllForSome  (T1 setX[], int sizeX, T2 setY[], int sizeY);
   bool forSomeForAll  (T1 setX[], int sizeX, T2 setY[], int sizeY);
   bool forSomeForSome (T1 setX[], int sizeX, T2 setY[], int sizeY);
};

#endif /* predicate.h */

/**************************************************************************
* 
**************************************************************************/
template <class T1, class T2> 
class HasProperty : public Predicate<T1, T2>
{
public:
   virtual bool isTrue (Item theItem, string theProperty);
   virtual bool isFalse(Item theItem, string theProperty);
};

int getInt(string prompt);
string word(int num);
bool vowel(char letter);

/**************************************************************************
* 
**************************************************************************/
int main()
{
   string universe;
   int    numItems;
   int    numProps;
   string theName;
   string theNameX;
   string attrib;
   string prompt;

   // Word of wisdom
   cout << "\nTry to keep numbers small as this program will prompt\n"
        << "you for every value you give it\n\n";
   
   // describe first set
   cout << "Name a universe of discourse(e.g. fruits): ";
   getline(cin, universe);

   universe[0] = tolower(universe[0]);
   if (universe[universe.size() - 1] != 's') // At least it works for
      universe += "s";                       // words that s makes
   string universeX = "";                    // plural...
   for (int i = 0; i < (universe.size() - 1); i++)
   {
      universeX += universe[i];
   }
   string article = " a ";
   if (vowel(universe[0]))
      article = " an ";

   prompt = "How many " + universe + " are there: ";
   numItems = getInt(prompt);
   cin.ignore();
   cout << endl;
   Item* setItems = new Item[numItems];
   for (int i = 0; i < numItems; i++)
   {
      cout << "What is the name of the " << (i + 1) << word(i + 1)
           << " " << universeX << ": ";
      getline(cin, theName);
      theName[0] = tolower(theName[0]);
      if (theName[theName.size() - 1] != 's')
         theName += "s";
      
      string theNameX = "";                    
      for (int j = 0; j < (theName.size() - 1); j++)
      {
         theNameX += theName[j];
      }
      setItems[i].name(theName);

      string tempArt = " a ";
      if (vowel(theName[0]))
         tempArt = " an ";
      
      cout << "With how many words can you describe" << tempArt << theNameX << ".("
           << MAX_PROPS << " max): ";
      numProps = getInt("");
      cin.ignore();
      if (numProps > 0)
         cout << "Please list these descriptive words, one line at a time\n";
      for (int j = 0; j < numProps; j++)
      {
         cout << "> ";
         getline(cin, attrib);
         setItems[i].addProp(attrib);
      }
      cout << endl;
   }
   // describe second set
   prompt = "With how many words can you describe" + article + universeX + ": ";
   numProps = getInt(prompt);
   cin.ignore();
   string* setProperties = new string[numProps];
   cout << "Please list these descriptive words one line at a time\n";
   for (int i = 0; i < numProps; i++)
   {
      cout << "> ";
      getline(cin, setProperties[i]);
   }
   
   // Evaluate
   cout << endl;
   HasProperty<Item, string> thisProperty;
   // forAllForAll
   if (thisProperty.forAllForAll(setItems, numItems, setProperties, numProps))
      cout << "All listed " << universe
           << " have every listed attribute of" << article << universeX << ".\n";
   else
      cout << "Not all listed " << universe
           << " have every listed attribute of" << article << universeX << ".\n";
   // forAllForSome
   if (thisProperty.forAllForSome(setItems, numItems, setProperties, numProps))
      cout << "All listed " << universe
           << " have some listed attribute of" << article << universeX << ".\n";
   else
      cout << "Not all listed " << universe
           << " have some listed attribute of" << article << universeX << ".\n";
   // forSomeForSome
   if (thisProperty.forSomeForSome(setItems, numItems, setProperties, numProps))
      cout << "There are some listed " << universe
           << " that have a listed attribute of" << article<< universeX << ".\n";
   else
      cout << "All listed " << universe
           << " have no listed attributes of" << article << universeX << ".\n";
   // forSomeForAll
   if (thisProperty.forSomeForAll(setItems, numItems, setProperties, numProps))
      cout << "There are some listed " << universe
           << " that have all listed attributes of" << article << universeX << ".\n";
   else
      cout << "There are no listed " << universe
           << " that have all listed attributes of" << article << universeX << ".\n";

   cout << endl;
   
   delete [] setProperties;
   delete [] setItems;
   return 0;
}

/**************************************************************************
* Is this Predicate true for all x for all y in the supplied sets?
**************************************************************************/
template<class T1, class T2>
bool Predicate<T1, T2>::forAllForAll(T1 setX[], int sizeX, T2 setY[], int sizeY)
{
   bool trueForAllForAll = true;
   for (int i = 0; i < sizeX; i++)
   {
      for (int j = 0; j < sizeY; j++)
      {
         if (isFalse(setX[i], setY[j]))
         {
            trueForAllForAll = false;
            break;
         }
      }
   }
   return trueForAllForAll;
}

/**************************************************************************
* Is this Predicate true for all x for some y in the supplied sets?
**************************************************************************/
template<class T1, class T2>
bool Predicate<T1, T2>::forAllForSome(T1 setX[], int sizeX, T2 setY[], int sizeY)
{
   bool trueForAllForSome = true;
   bool trueForSome = false;
   for (int i = 0; i < sizeX; i++)
   {
      trueForSome = false;
      for (int j = 0; j < sizeY; j++)
      {
         if (isTrue(setX[i], setY[j]))
            trueForSome = true;
      }
      if (!trueForSome)
      {
         trueForAllForSome = false;
         break;
      }
   }
   return trueForAllForSome;
}

/**************************************************************************
* Is this Predicate true for some x for all y in the supplied sets?
**************************************************************************/
template<class T1, class T2>
bool Predicate<T1, T2>::forSomeForAll(T1 setX[], int sizeX, T2 setY[], int sizeY)
{
   bool trueForSomeForAll = false;
   bool trueForAll = true;
   for (int i = 0; i < sizeX; i++)
   {
      trueForAll = true;
      for (int j = 0; j < sizeY; j++)
      {
         if (isFalse(setX[i], setY[j]))
            trueForAll = false;
      }
      if (trueForAll)
      {
         trueForSomeForAll = true;
         break;
      }
   }
   return trueForSomeForAll;
}

/**************************************************************************
* Is this Predicate true for some x for some y in the supplied sets?
**************************************************************************/
template<class T1, class T2>
bool Predicate<T1, T2>::forSomeForSome(T1 setX[], int sizeX, T2 setY[], int sizeY)
{
   bool trueForSomeForSome = false;
   for (int i = 0; i < sizeX; i++)
   {
      for (int j = 0; j < sizeY; j++)
      {
         if (isTrue(setX[i], setY[j]))
         {
            trueForSomeForSome = true;
            break;
         }
      }
   }
   return trueForSomeForSome;
}

/**************************************************************************
* 
**************************************************************************/
template<class T1, class T2>
bool HasProperty<T1, T2>::isTrue(Item theItem, string theProperty)
{
   bool trueStatement = false;
   int size = theItem.size();
   for (int i = 0; i < size; i++)
   {
      if (theItem.prop(i) == theProperty)
         trueStatement = true;
   }
   return trueStatement;
}

/**************************************************************************
* 
**************************************************************************/
template<class T1, class T2>
bool HasProperty<T1, T2>::isFalse(Item theItem, string theProperty)
{
   return (!isTrue(theItem, theProperty));
}

/**************************************************************************
* 
**************************************************************************/
Item::Item(void)
{
   maxSize = MAX_PROPS;
   property = new string[maxSize];
   itemName = "Unknown";
   numProps = 0;
}

/**************************************************************************
* 
**************************************************************************/
Item::Item(int max)
{
   maxSize = max;
   property = new string[maxSize];
   itemName = "Unknown";
   numProps = 0;
}

/**************************************************************************
* 
**************************************************************************/
Item::Item(const Item& original)
{
   maxSize = original.maxSize;
   property = new string[maxSize];
   for (int i = 0; i < original.numProps; i++)
   {
      property[i] = original.property[i];
   }
   itemName = original.itemName;
   numProps = original.numProps;
}

/**************************************************************************
* 
**************************************************************************/
Item::~Item(void)
{
   delete [] property;
}

/**************************************************************************
* 
**************************************************************************/
void Item::name(string theName)
{
   itemName = theName;
   return;
}

/**************************************************************************
* 
**************************************************************************/
string Item::name(void) const
{
   return itemName;
}

/**************************************************************************
* Adds a property to an object
**************************************************************************/
void Item::addProp(string prop)
{
   if (numProps < maxSize)
   {
      property[numProps] = prop;
      numProps++;
   }
   return;
}

/**************************************************************************
* Returns the number of properties given an object
**************************************************************************/
int Item::size(void) const
{
   return numProps;
}

/**************************************************************************
* Returns a specified property
**************************************************************************/
string Item::prop(int num)
{
   string theProp = "";
   if ((num > -1) && (num < numProps))
      theProp = property[num];
   return theProp;
}

/**************************************************************************
* 
**************************************************************************/
Item& Item::operator = (const Item& rtSide)
{
   delete [] property;
   maxSize = rtSide.maxSize;
   property = new string[maxSize];
   for (int i = 0; i < rtSide.numProps; i++)
   {
      property[i] = rtSide.property[i];
   }
   itemName = rtSide.itemName;
   numProps = rtSide.numProps;
   return *this;
}

/**************************************************************************
* Safe way to get a valid int. takes in a string with the prompt,
* and returns the valid integer
**************************************************************************/
int getInt(string prompt)
{
   int goodInt;
   bool valid = false;
   cout << prompt;
   while (!valid)
   {
      cin >> goodInt;
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(80, '\n');
         cout << "Invalid number. Try again: ";
      }
      else
         valid = true;
   }
   return goodInt;
}

/**************************************************************************
* 
**************************************************************************/
string word(int num)
{
   string theWord = "";
   switch (num)
   {
      case 1:
      {
         theWord = "st";
         break;
      }
      case 2:
      {
         theWord = "nd";
         break;
      }
      case 3:
      {
         theWord = "rd";
         break;
      }
      default:
      {
         theWord = "th";
         break;
      }      
   }
   return theWord;
}

/**************************************************************************
* 
**************************************************************************/
bool vowel(char letter)
{
   bool isVowel = false;
   letter = tolower(letter);
   
   switch (letter)
   {
      case 'a':
      {
         isVowel = true;
         break;
      }
      case 'e':
      {
         isVowel = true;
         break;
      }
      case 'i':
      {
         isVowel = true;
         break;
      }
      case 'o':
      {
         isVowel = true;
         break;
      }
      case 'u':
      {
         isVowel = true;
         break;
      }
      default:
      {
         isVowel = false;
         break;
      }
   }
   
   return isVowel;
}
