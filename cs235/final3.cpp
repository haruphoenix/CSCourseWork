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
#include "clist.cpp"
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

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

bool   parse  (LList<Ancestor> &list, string filename);
bool   parse2 (LList<Ancestor> &list, string filename, Ancestor& head);
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

      if (!parse(names, filename))
         return 1;

      names.sort();

      if (!parse2(names, filename, head))
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
* in a linked list. Returns false if the read fails.
******************************************************************************/
bool parse(LList<Ancestor> &list, string filename)
{
   ifstream read;
   try
   {
      read.open(filename.c_str());
      if (read.fail())
         throw filename;
      string word;
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
         }
      }
   }
   catch (string e)
   {
      cout << "Error: Could not open " << e << endl;
      return false;
   }
   return true;
}

/*****************************************************************************
* Searches a GEDCOM file for family ties, and searches a linked list for the
* individual Ancesters. Sets each ancestor to point to it's parents. Requires 
* a Linked List of ancestors, a GEDCOM filename, and an Ancestor to be the 
* head of the "tree". Returns false if the read fails.
******************************************************************************/
bool parse2(LList<Ancestor> &list, string filename, Ancestor &head)
{
   ifstream read;
   try
   {
      read.open(filename.c_str());
      if (read.fail())
         throw filename;
      string word;
      string father = "";
      string mother = "";
      string child  = "";
      bool first = true;
      Ancestor tChild;
      Ancestor tFather;
      Ancestor tMother;
      Ancestor* pChild;
      Ancestor* pFather;
      Ancestor* pMother;
      
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
