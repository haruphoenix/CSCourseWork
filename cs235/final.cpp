/*****************************************************************************
* Program:
*    Assignment 256, Final
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This program reads in a GEDCOM file, and parses it for names.  It sorts
*    the names in alphabetical order, and writes them to a file. It then, 
*    displays the generations of ancestors of the first individual in the file.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

template <class T>
class LList;

/******************************************************************
 * Node class contains a pointer, and data, along with getters
 * and setters for each. Basic unit for a linked list
 ******************************************************************/
template <class T>
class Node
{
   public:
      friend class LList<T>;
      Node();
      Node(T theData);
      Node<T>* getNext();
      Node<T>* getPrev();
      T        getData();
      void     setData(T item);
      void     setNext(Node<T>* node);
      void     setPrev(Node<T>* node);

   private:
      T data;
      Node<T>* next;
      Node<T>* prev;
};

/******************************************************************
 * Linked List class, contains all the functions for a fluid list,
 * plus indexing for ease of use.
 ******************************************************************/
template <class T>
class LList
{
   public:
      LList();
      LList(const LList& original);
      ~LList();

      void insert(T item, int loc = -1);
      void remove(int loc = -1);

      Node<T>* position(int loc = 0);
      int  size ();
      bool empty();
      void clear();
      void sort (bool ascending = true, int first = 0, int last = -1);

      T& operator [] (int index); // Directly access elements
      T& operator () ();          // Directly access current
      T& access      (Node<T>* loc);

      void setCurrent(int loc);   // set current to loc
      void operator ++ (int);     // increment current
      void operator -- (int);     // decrement current

      LList<T>& operator =  (const LList<T>& rtSide);
   
      Node<T>* find(T item);

   private:
      Node<T>* head;
      Node<T>* current;
      Node<T>* last;
      int theSize;
};

/*****************************************************************************
* Date, stores a month, year, and day.
******************************************************************************/
struct Date
{
   string month;
   string year;
   string day;
};

bool     operator <  (Date& left, Date& right);
ostream& operator << (ostream&   out, Date& data);

/*****************************************************************************
* Name, stores first, middle, and last name.
******************************************************************************/
struct Name
{
   string first;
   string middle;
   string last;
};

bool     operator <  (Name& left, Name& right);
ostream& operator << (ostream&   out, Name& data);

/*****************************************************************************
* Ancestor has a name, birthday, as well as pointers to their father mother,
* and a single child. Can display their ancestors.
******************************************************************************/
class Ancestor
{
   public:
      Ancestor();

      string name();
      string birthday();
      string getID();
      void   setName(string name);
      void   setName(Name   name);
      void   setBDay(string date);
      void   setBDay(Date   date);
      void   setID  (string iVal);

      bool operator <  (Ancestor& right);
      bool operator == (Ancestor& right);
      bool operator == (string  rightID);

      Ancestor* getFather(void);   
      Ancestor* getMother(void);  
      Ancestor* getChild (void);      
      void      setFather(Ancestor* pFather);
      void      setMother(Ancestor* pMother);
   
      void      showAncestry(void);
   
   private:
      void printGeneration(int gen);
      Name     fName;
      Date     bDay;
      string   ID;
      Ancestor* father;
      Ancestor* mother;
      Ancestor* child;
};

ostream& operator << (ostream& out, Ancestor& data);
istream& operator >> (istream& in,  Ancestor& data);

bool   parse(LList<Ancestor> &list, string filename, Ancestor& head);
string depunct(string word);

/*****************************************************************************
* Opens a file, and parses it for names. Writes the names to a file, then opens
* up the file again to search out family ties. Links Ancestors together, and
* displays their tree.
******************************************************************************/
int main(int argc, char** argv)
{
   try
   {
      string filename = "cameron.ged";
      string sortFile = "sorted.dat";
      LList<Ancestor> names;
      Ancestor head;
      ofstream write;
      
      if (argc > 1)
      {
         filename = argv[1];
         if (argc > 2)
            sortFile = argv[2];
      }

      if (!parse(names, filename, head))
         return 1;

      write.open(sortFile.c_str());   
      if (write.fail())
         throw sortFile;
      for (int i = 0; i < names.size(); i++)
         write << names[i] << endl;
      write.close();
      
      head.showAncestry();
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   return 0;
}

/*****************************************************************************
* Searches a GEDCOM file for key data relating to ancestors. Places ancestors
* in a linked list, links families by assigning pointers to parents. Returns
* the ancestor that is the head of the tree by reference.  Bool returns whether
* or not the read was successful
******************************************************************************/
bool parse(LList<Ancestor> &list, string filename, Ancestor &head)
{
   ifstream  read;
   string    word;
   string    father = "";
   string    mother = "";
   string    child  = "";
   bool      first = true;
   Ancestor  tChild;
   Ancestor  tFather;
   Ancestor  tMother;
   Ancestor* pChild;
   Ancestor* pFather;
   Ancestor* pMother;

   // Read Names
   try
   {
      read.open(filename.c_str());
      if (read.fail())
         throw filename;
      while (read >> word)
      {
         if (word == "0")
         {
            read >> word;
            if (word[1] == 'I')
            {
               int i = 1;
               string ID;
               while (word[i] != '@')
                  ID += word[i++];
               read >> word >> word >> word;
               Ancestor person;
               person.setID(ID);
               read >> person;
               list.insert(person);
            }
            else if (word[1] == 'F')
            {
               read >> word;
               if (word == "FAM")
                  break;
            }
         }
      }
      list.sort();
      read.clear();
      read.seekg(0, ios::beg);
      // Read Family Ties
      while (read >> word)
      {
         if (word == "0")
         {
            read >> word;
            if (word[1] == 'F')
            {
               while ((word != "HUSB") && (word != "WIFE") && (word != "CHIL"))
                  read >> word;
               if (word == "HUSB")
               {
                  read >> word;
                  father = depunct(word);
                  read >> word >> word;
               }
               if (word == "WIFE")
               {
                  read >> word;
                  mother = depunct(word);
                  read >> word >> word;
               }
               if (word == "CHIL")
               {
                  read >> word;
                  child = depunct(word);
               }
               tChild.setID(child);
               tFather.setID(father);
               tMother.setID(mother);
               pChild  = &(list.access(list.find(tChild)));
               pFather = &(list.access(list.find(tFather)));
               pMother = &(list.access(list.find(tMother)));
               if (pChild != NULL)
               {
                  if (pFather != NULL)
                      pChild->setFather(pFather);
                  if (pMother != NULL)
                     pChild->setMother(pMother);
               }
               father = "";
               mother = "";
               child  = "";
               if (first && (pChild != NULL))
               {
                  head = *pChild;
                  first = false;
               }
            }
         }
      }
      read.close();
   }
   catch (string e)
   {
      cout << "Error: Could not open " << e << endl;
      return false;
   }

   return true;
}


/*****************************************************************************
* Removes all non-alphabet and non-numeric characters from a string, except
* periods. Input is the string to modify. Returns depunctuated string.
******************************************************************************/
string depunct(string word)
{
   string newWord;
   for (int i = 1; i < word.size(); i++)
   {
      if ((isalpha(word[i])
           || ((word[i] == ' ') && (i != word.size() - 1))
           || (word[i] == '.'))
           || (isdigit(word[i])))
         newWord += word[i];
   }

   return newWord;
}


/*****************************************************************************
* Constructor for Ancestor.
******************************************************************************/
Ancestor::Ancestor()
{
   fName.first  = "";
   fName.middle = "";
   fName.last   = "";
   bDay.year    = "";
   bDay.month   = "";
   bDay.day     = "";
   ID           = "";
   father     = NULL;
   mother     = NULL;
   child      = NULL;
}

/*****************************************************************************
* Returns the full name of the ancestor as a string.
******************************************************************************/
string Ancestor::name()
{
   string name = "";
   bool first = true;
   if (fName.first != "")
   {
      first = false;
      name += fName.first;
   }
   if (fName.middle != "")
   {
      if (!first)
         name += " ";
      name += fName.middle;
      first = false;
   }
   if (fName.last != "")
   {
      if (!first)
         name += " ";
      name += fName.last;
   }
   return name;
}

/*****************************************************************************
* Returns the full birthday of the Ancestor as a string.
******************************************************************************/
string Ancestor::birthday()
{
   string fullBDay = "";
   bool prev = false;

   if (bDay.day != "")
   {
      fullBDay += bDay.day;
      prev = true;
   }
   if (bDay.month != "")
   {
      if (prev)
         fullBDay += " ";
      fullBDay += bDay.month;
      prev = true;
   }
   if (bDay.year != "")
   {
      if (prev)
         fullBDay += " ";
      fullBDay += bDay.year;
   }
   return fullBDay;
}

/*****************************************************************************
* Returns the ancestor's ID.
******************************************************************************/
string Ancestor::getID()
{
   return ID;
}
   
/*****************************************************************************
* Returns true if the name of the left operand Ancestor is alphabetically lower
* in the alphabet than the right operand. If they are the same, it returns
* true, if the left operand Ancestor's birthday is before the right Ancestors.
* Returns false otherwise.
******************************************************************************/
bool Ancestor::operator < (Ancestor& right)
{
   if (fName < right.fName)
      return true;
   else if (right.fName < fName)
      return false;
   else if (bDay < right.bDay)
      return true;
   else
      return false;
}

/*****************************************************************************
* Sets the first, middle, and last name of the Ancestor given a string name
* in the GEDCOM format. No return.
******************************************************************************/
void Ancestor::setName(string name)
{
   bool first = true;
   bool second = false;
   fName.first  = "";
   fName.middle = "";
   fName.last   = "";
   
   for (int i = 0; i < name.size(); i++)
   {
      while (name[i] == ' ') if (i++ == name.size()) break;   
      if (name[i] == '/')
      {
         i++;
         while (name[i] != '/')
         {
            fName.last += name[i++];
            if (i == name.size())
               break;
         }
      }
      else if (first)
      {
         first = false;
         while (name[i] != ' ')
         {
            fName.first += name[i++];
            if (i == name.size())
               break;
         }
      }
      else
      {
         if (second)
            fName.middle += ' ';
         second = true;
         while (name[i] != ' ')
         {
            fName.middle += name[i++];
            if (i == name.size())
               break;
         }
      }
   }
   return;
}

/*****************************************************************************
* Sets the Ancestors full name given a name object.
******************************************************************************/
void Ancestor::setName(Name name)
{
   fName = name;
   return;
}

/*****************************************************************************
* Sets the Ancestors birthday given a string of the GEDCOM format. no return.
******************************************************************************/
void Ancestor::setBDay(string date)
{
   bDay.day   = "";
   bDay.year  = "";
   bDay.month = "";
  
   if (isalpha(date[0]))                     // Just month and year
   {
      for (int i = 0; i < 3; i++)
         bDay.month += date[i];
      for (int i = 4; i < date.size(); i++)
         bDay.year += date[i];
   }
   else if (isalpha(date[3]))               // Month day and year
   {
      int i = 0;
      while (date[i] != ' ')
         bDay.day += date[i++];
      i++;
      int j = i + 3;
      while (i != j)
         bDay.month += date[i++];
      i++;
      while (i < date.size())
         bDay.year += date[i++];
   }
   else                                      // Year only
      for (int i = 0; i < date.size(); i++)
         bDay.year += date[i];
   return;
}

/*****************************************************************************
* Sets the birthday of an Ancestor given a date object. no return.
******************************************************************************/
void Ancestor::setBDay(Date date)
{
   bDay = date;
   return;
}

/*****************************************************************************
* Sets the Ancestors ID to a string input value.
******************************************************************************/
void Ancestor::setID(string iVal)
{
   ID = iVal;
   return;
}

/*****************************************************************************
* Comparison operator. Returns true if both Ancestor's IDs are the same.
* false otherwise.
******************************************************************************/
bool Ancestor::operator == (Ancestor& right)
{
   if (ID == right.ID)
      return true;
   else
      return false;
}

/*****************************************************************************
* Compares an ancestor to a string.  Returns true if the string is equal
* to the Ancestor's ID.
******************************************************************************/
bool Ancestor::operator == (string rightID)
{
   if (ID == rightID)
      return true;
   else
      return false;
}


/*************************************************************
 * Return the ptr to the left child
 ************************************************************/
Ancestor* Ancestor::getFather(void)
{
   return father;
}

/*************************************************************
 * Return the ptr to the right child
 ************************************************************/
Ancestor* Ancestor::getMother(void)
{
   return mother;
}


/*************************************************************
 * Return parent
 ************************************************************/
Ancestor* Ancestor::getChild(void)
{
   return child;
}

/*************************************************************
 * Sets the left pointer to given input pointer
 ************************************************************/
void Ancestor::setFather(Ancestor* pFather)
{
   father = pFather;
   if (pFather != NULL)
      pFather->child = this;
   return;
}

/*************************************************************
 * Sets the right pointer to given input pointer
 ************************************************************/
void Ancestor::setMother(Ancestor* pMother)
{
   mother = pMother;
   if (pMother != NULL)
      pMother->child = this;
   return;
}

/*************************************************************
 * Displays the ancestry of a particular ancestor back as
 * far as it can go.
 ************************************************************/
void Ancestor::showAncestry(void)
{
   cout << "The Ancestors of " << fName << ":\n";
   
   int const MAX = 100;
   Ancestor *queue[MAX];
   Ancestor *temp;
   int front = 0;
   int back = 0;
   int lastBack = 1;
   int gen = 1;

   queue[back++] = this;

   while (front != back)
   {
      if ((lastBack == front) && (queue[front] != NULL))
      {
         printGeneration(gen++);
         lastBack = back;
      }
      
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         if (gen != 1)
            cout << "        " << *temp << endl;
         // end Visit
         queue[back] = temp->father;
         back = (back + 1) % MAX;
         queue[back] = temp->mother;
         back = (back + 1) % MAX;

      }
   }
}

/*****************************************************************************
* Prints out the generation given an integer value describing the generation.
* e.g. 1 is parents, 2 is grandparents, etc.
******************************************************************************/
void Ancestor::printGeneration(int gen)
{
   
   switch (gen)
   {
      case 1:
         cout << "Parents:\n";
         break;
      case 2:
         cout << "Grandparents:\n";
         break;
      case 3:
         cout << "Great Grandparents:\n";
         break;
      case 4:
         cout << "2nd Great Grandparents:\n";
         break;
      case 5:
         cout << "3rd Great Grandparents:\n";
         break;
      default:
         cout << gen - 2 << "th Great Grandparents:\n";
         break;
   }
   return;
}

/*****************************************************************************
* Displays/writes an Ancestor's name and birthday.
******************************************************************************/
ostream& operator << (ostream& out, Ancestor& data)
{
   out << data.name();
   if (data.birthday() != "")
      out << ", b. " << data.birthday();
   return out;
}

/*****************************************************************************
* Reads an ancestor's name and birthday from a GEDCOM file format.
******************************************************************************/
istream& operator >> (istream& in,  Ancestor& data)
{
   string name;
   getline(in, name);
   data.setName(name);
   string date;
   while (date != "BIRT")
   {
      in >> date;
      if (date == "3")
         return in;
   }
   in >> date;
   in >> date;
   if (date != "DATE")
      return in;
   getline(in, date);
   date.erase(0, 1);
   if (date[0] == ',')
      return in;
   data.setBDay(date);
   return in;
}

/*****************************************************************************
* Comparison operator, compares two dates. Returns true if the left operand
* is before the right side.
******************************************************************************/
bool operator < (Date& left, Date& right)
{
   if (atoi(left.year.c_str()) < atoi(right.year.c_str()))
      return true;
   else
      return false;
}

/*****************************************************************************
* Writes a date object to an output stream. Format: day month year. 
******************************************************************************/
ostream& operator << (ostream& out, Date& data)
{
   if (data.day != "")
      out << data.day;
   if (data.month != "")
      out << " " << data.month;
   if (data.year != "")
      out << " " << data.year;
   return out;
}

/*****************************************************************************
* Compares two names. Returns true if the left name is alphabetically less
* than the right name. False otherwise.
******************************************************************************/
bool operator < (Name& left, Name& right)
{
   string lLast = left.last;
   string rLast = right.last;
   if (lLast.size() > 0)
      lLast[0] = toupper(lLast[0]);
   if (rLast.size() > 0)
      rLast[0] = toupper(rLast[0]);   
   if (lLast < rLast)
      return true;
   else if (right.last < left.last)
      return false;
   else if (left.first < right.first)
      return true;
   else if (right.first < left.first)
      return false;
   else if (left.middle < right.middle)
      return true;
   else
      return false;
}

/*****************************************************************************
* Writes a name to an output stream. Format: First Middle (if any) Last
******************************************************************************/
ostream& operator << (ostream& out, Name& data)
{
   bool first = true;
   if (data.first != "")
   {
      first = false;
      out << data.first;
   }
   if (data.middle != "")
   {
      if (!first)
         out << " ";
      out << data.middle;
      first = false;
   }
   if (data.last != "")
   {
      if (!first)
         out << " ";
      out << data.last;
   }
   return out;
}

/******************************************************************
 * Constructor for Node. Sets next and previous pointers to NULL.
 * Since template class, data is uninitialized.
 ******************************************************************/
template <class T>
Node<T>::Node()
{
   next = NULL;
   prev = NULL;
}

/******************************************************************
 * Constructor for Node. Sets next and previous pointers to NULL.
 * Sets parameter as data.
 ******************************************************************/
template <class T>
Node<T>::Node(T theData)
{
   data = theData;
   next = NULL;
   prev = NULL;
}

/******************************************************************
 * Returns the node's pointer to the next. No input.
 ******************************************************************/
template <class T>
Node<T>* Node<T>::getNext()
{
   return next;
}

/******************************************************************
 * Returns the node's pointer to the previous. No input.
 ******************************************************************/
template <class T>
Node<T>* Node<T>::getPrev()
{
   return prev;
}

/******************************************************************
 * Returns the node's data. No input.
 ******************************************************************/
template <class T>
T Node<T>::getData()
{
   return data;
}

/******************************************************************
 * Sets the node data to input value. No return.
 ******************************************************************/
template <class T>
void Node<T>::setData(T item)
{
   data = item;
   return;
}

/******************************************************************
 * Sets the next node pointer to input pointer. No return.
 ******************************************************************/
template <class T>
void Node<T>::setNext(Node<T>* node)
{
   next = node;
   return;
}

/******************************************************************
 * Sets the previous node pointer to input pointer. No return.
 ******************************************************************/
template <class T>
void Node<T>::setPrev(Node<T>* node)
{
   prev = node;
   return;
}

/******************************************************************
 * Constructor for Linked List, initializes all pointers to NULL.
 ******************************************************************/
template <class T>
LList<T>::LList()
{
   theSize = 0;
   head = NULL;
   last = NULL;
   current = NULL;
}

/******************************************************************
 * Copy constructor, makes a duplicate of linked list.
 ******************************************************************/
template <class T>
LList<T>::LList(const LList& original)
{
   theSize = 0;
   head = NULL;
   last = NULL;
   current = NULL;
   Node<T>* temp = original.head;
   for (int i = 0; i < original.theSize; i++)
   {
      insert(temp->getData());
      temp = temp->getNext();
   }
}

/******************************************************************
 * Destructor, removes and deletes each node in the list.
 ******************************************************************/
template <class T>
LList<T>::~LList()
{
   clear();
}

/******************************************************************
 * Inserts a Node into a linked list. Input is the item to insert,
 * and the integer location of where in the list to insert it.
 ******************************************************************/
template <class T>
void LList<T>::insert(T item, int loc)
{
   Node<T>* newNode = new Node<T>;
   newNode->setData(item);

   if (loc != -1)
      current = position(loc);

   if (current == NULL)            // Empty or end of list
   {
      newNode->setPrev(last);
      if (last != NULL)
         last->setNext(newNode);
      else
         head = newNode;
      last = newNode;
   }
   else                            // Beginning or middle of list
   {
      newNode->setNext(current);
      newNode->setPrev(current->getPrev());
      if (newNode->getPrev() != NULL)
         newNode->getPrev()->setNext(newNode);
      else
         head = newNode;
      current->setPrev(newNode);
   }

   current = newNode->getNext();
   theSize++;

   return;
}

/******************************************************************
 * Removes a node from the linked list. Node to remove is the
 * integer index passed by value.
 ******************************************************************/
template <class T>
void LList<T>::remove(int loc)
{
   if (theSize == 0)
      return;

   if ((loc < 0) || (loc >= theSize))
      loc = theSize - 1;

   Node<T>* node2Remove = position(loc);

   if (node2Remove->getPrev() != NULL)
      node2Remove->getPrev()->setNext(node2Remove->getNext());
   else
      head = node2Remove->getNext();

   if (node2Remove->getNext() != NULL)
      node2Remove->getNext()->setPrev(node2Remove->getPrev());
   else
      last = node2Remove->getPrev();

   delete node2Remove;
   theSize--;

   return;
}

/******************************************************************
* Returns the address of a integer position in the list.
*******************************************************************/
template <class T>
Node<T>* LList<T>::position(int loc)
{
   if (loc > theSize)
      loc = theSize;

   Node<T>* temp = head;

   for (int i = 0; i < loc; i++)
      temp = temp->getNext();

   return temp;
}

/******************************************************************
 * Returns the size of the list.
 ******************************************************************/
template <class T>
int LList<T>::size()
{
   return theSize;
}

/******************************************************************
 * Returns true if the list is empty. false otherwise
 ******************************************************************/
template <class T>
bool LList<T>::empty()
{
   if (theSize == 0)
      return true;
   else
      return false;
}

/******************************************************************
 * Clears the list of all its nodes
 ******************************************************************/
template <class T>
void LList<T>::clear()
{
   while (theSize != 0)
      remove();
   head = NULL;
   last = NULL;
   current = NULL;
   return;
}

/******************************************************************
 * Overloaded square brackets allow direct access to elements of
 * the list. Input is the index, returns the address of the item
 * contained by the node at that location.
 ******************************************************************/
template <class T>
T& LList<T>::operator [] (int index)
{
   return position(index)->data;
}

/******************************************************************
 * Accesses the data of the current node pointer. Allows more
 * efficient traversing through list when used with ++ and --
 * operators.
 ******************************************************************/
template <class T>
T& LList<T>::operator () ()
{
   if (current != NULL)
      return current->data;
   else
      return position(theSize - 1)->data;
}

/******************************************************************
 * Accesses the data of a particular node. Allows for flexibility.
 * Realize this grants complete access to modify and read.
 ******************************************************************/
template <class T>
T& LList<T>::access(Node<T>* loc)
{
   return loc->data;
}

/******************************************************************
 * Sets the current pointer location to given index location.
 ******************************************************************/
template <class T>
void LList<T>::setCurrent(int loc)
{
   current = position(loc);
   return;
}

/******************************************************************
 * Increments current pointer forwards through the list. Loops
 * back to the beginning when it basses the end.
 ******************************************************************/
template <class T>
void LList<T>::operator ++ (int)
{
   if (current != NULL)
      current = current->getNext();
   else
      current = head;
   return;
}

/*****************************************************************
* Increments current pointer backwards through the list. Loops
* back to end when it passes the beginning.
******************************************************************/
template <class T>
void LList<T>::operator -- (int)
{
   if (current != NULL)
      current = current->getPrev();
   else
      current = last;
   return;
}

/******************************************************************
 * Overloaded assignment operator replicates a list on the right
 * side, and creates an identical list on the left side.
 ******************************************************************/
template <class T>
LList<T>& LList<T>::operator = (const LList<T>& rtSide)
{
   clear();
   Node<T>* temp = rtSide.head;
   for (int i = 0; i < rtSide.theSize; i++)
   {
      insert(temp->getData());
      temp = temp->getNext();
   }

   return *this;
}

/******************************************************************
 * Sorts the list in ascending order by default. Set input to false
 * to sort in descending order.
 ******************************************************************/
template <class T>
void LList<T>::sort(bool ascending, int low, int high)
{
   if (high == -1) high = theSize - 1;
   if (high - low < 1)
      return;
   int left  = low;
   int right = high;
   T pivot = (*this)[low + (high - low) / 2];
   while(left <= right)
   {
      if (ascending)
      {
         while((*this)[left] < pivot)
            left++;
         while(pivot < (*this)[right])
            right--;
      }
      else
      {
         while(pivot < (*this)[left])
            left++;
         while((*this)[right] < pivot)
            right--;
      }
      if(left <= right)
      {  T temp = (*this)[left];
         (*this)[left] = (*this)[right];
         (*this)[right] = temp;
         left++;
         right--;
      }
   }
   sort(ascending, low, right);
   sort(ascending, left, high);
}

/******************************************************************
 * Finds an item in the list. Input is the item to find. Returns
 * NULL if not found, otherwise, returns the pointer to the node
 * where value is.
 ******************************************************************/
template <class T>
Node<T>* LList<T>::find(T item)
{
   current = head;
   for (int i = 0; i < theSize; i++)
      if (current != NULL)
      {
         if (current->getData() == item)
            return current;
         current = current->getNext();
      }
   return NULL;
}
