#include <iostream>
#include "ttree.cpp"
using namespace std;

class Letter
{
   public:
      Letter(void);
      Letter(int freq, char val = ' ');
      Letter(char val, int freq = 0);

      bool operator < (Letter& rtSide);
      bool operator < (int number);
      bool operator ==(Letter& rtSide);
      void operator = (int freq);
      void operator = (char val);
   
      char   value;
      int    frequency;
      bool   inserted;
};

typedef BTree<Letter> codeBit;

ostream& operator << (ostream& out, Letter& item);
int operator -(Letter& item);
Letter operator + (Letter& first, Letter& second);

class Code
{
   public:
      Code(void);
      void addLetter(Letter newChar);
      void generate(void);
   
      string decipher(string value);
      string cipher  (string value);
   private:
      string   part (char value);
      codeBit* small(void);
      void     add  (codeBit parent);
      void     find(char value, codeBit* &ptr, codeBit* place);

      codeBit* root;
      codeBit  array[52];
      int      numPar;
      int      size;
};
   
int main()
{
   Code myCode;
   Letter m(1, 'a');
   for (int i = 2; i < 28; i++)
   {
      myCode.addLetter(m);
      m.value += 1;
      m.frequency += 1;
   }
   myCode.generate();
   string message = "hello world";
   cout << "Message: " << message << endl;
   message = myCode.cipher(message);
   cout << "Message: " << message << endl;
   message = myCode.decipher(message);
   cout << "Message: " << message << endl;
   return 0;
}

Code::Code(void)
{
   size = 0;
   root = NULL;
   numPar = 0;
}

void Code::addLetter(Letter newChar)
{
   array[size].setData(newChar);
   size++;
   return;
}

void Code::generate(void)
{
   codeBit* smallA;
   codeBit* smallB;
   codeBit parent;   
   Letter temp;
   temp.value = ' ';
   for (int i = 0; i < size - 1; i++)
   {
      // Find two smallest
      smallA = small(); 
      smallB = small();
      // Connect with parent
      temp.frequency = smallA->getData().frequency +
         smallB->getData().frequency;
      parent.setData(temp);
      parent.setRight(smallA);
      parent.setLeft(smallB);
      // Add parent back to array
      add(parent);
   }
   // Set root to last item in array
   root = &array[25 + numPar];
   return;
}
   
string Code::decipher(string value)
{
   string message;
   codeBit* ptr = root;

   for (int i = 0; i < value.size(); i++)
   {
      if (value[i] == '1')
      {
         if (ptr->getRightChild() != NULL)
            ptr = ptr->getRightChild();
         else
         {
            message += ptr->getData().value;
            ptr = root;
            i--;
         }
      }
      else
      {
         if (ptr->getLeftChild() != NULL)
            ptr = ptr->getLeftChild();
         else
         {
            message += ptr->getData().value;
            ptr = root;
            i--;
         }
      }
   }
   return message;
}

string Code::cipher(string message)
{
   string value;
   for (int i = 0; i < message.size(); i++)
      value += part(message[i]);
   return value;
}
  
string Code::part(char value)
{
   string charCode;
   string bit;

   codeBit* ptr = NULL;
   codeBit* plc = root;
   find(value, ptr, plc);
   
   plc = ptr;

//   if (ptr != NULL)
//      cout << ptr->getData().value << " ";
//   cout << endl;
//   if (plc != NULL)
//      if (plc->getParent() != NULL)
//         cout << plc->getParent()->getData().value << endl;

   
   if (plc == NULL)
      charCode = " ";
   else
   {
      while (plc->getParent() != NULL)
      {
         //cout << "data " << plc->getData().value << endl;
         if (plc->getParent()->getLeftChild() == plc)//
            bit = "0";
         else
            bit = "1";
         charCode = bit + charCode;
         plc = plc->getParent();
      }
   }
   return charCode;
}

codeBit* Code::small(void)
{
   codeBit tempBit;
   Letter start;
   tempBit.setData(start);
   codeBit* ptr = &tempBit;
   
   int index = 0;

   // Search among initial items
   for (int i = 0; i < size; i++)
   {
      if ((array[i].getData().frequency < ptr->getData().frequency) &&
          (array[i].getData().inserted == false))
      {
         ptr = &array[i];
         index = i;
      }
   }
   // Search among added items
   for (int i = 26; i < (26 + numPar); i++)
      if ((array[i].getData().frequency < ptr->getData().frequency) &&
          (array[i].getData().inserted == false))
      {
         ptr = &array[i];
         index = i;
      }
   
   // Take value out of array
   Letter temp = array[index].getData();
   temp.inserted = true;
   array[index].setData(temp);
   
   return ptr;
}

void Code::add(codeBit parent)
{
   array[26 + numPar] = parent;
   numPar++;
   return;
}

void Code::find(char value, codeBit* &ptr, codeBit* place)
{
   if (place->getData().value == value)
      ptr = place;
   else
   {
      if (place->getLeftChild() != NULL)
      {
         find(value, ptr, place->getLeftChild());
         if (ptr != NULL) return;
      }
      if (place->getRightChild() != NULL)
         find(value, ptr, place->getRightChild());
   }
   return;
}

Letter::Letter(void)
{
   frequency   = 1000000;
   value       = ' ';
   inserted    = false;
}

Letter::Letter(int freq, char val)
{
   frequency = freq;
   value = val;
   inserted    = false;
}

Letter::Letter(char val, int freq)
{
   frequency = freq;
   value = val;
   inserted    = false;
}
      
bool Letter::operator < (Letter& rtSide)
{
   if (frequency < rtSide.frequency)
      return true;
   else
      return false;
}

bool Letter::operator < (int number)
{
   if (frequency < number)
      return true;
   else
      return false;
}

bool Letter::operator == (Letter& rtSide)
{
   if (frequency == rtSide.frequency)
      return true;
   else
      return false;
}

void Letter::operator = (int freq)
{
   frequency = freq;
   return;
}

void Letter::operator = (char val)
{
   value = val;
   return;
}
   
ostream& operator << (ostream& out, Letter& item)
{
   out << item.value;
   return out;
}

int operator -(Letter item)
{
   return -item.frequency;
}

Letter operator + (Letter& first, Letter& second)
{
   Letter temp;
   temp.frequency = first.frequency + second.frequency;
   return temp;
}
