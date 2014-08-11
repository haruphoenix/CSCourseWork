/******************************************************************************
* Program:
*    Assignment 15, Huffman Code
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Summary:
*    This Program reads in a list of frequencies from a file, and inserts
*    them as letters into a binary tree. The tree uses the location of the
*    letter to generate a binary code. This program displays the code for
*    each letter.
******************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 50;

/*****************************************************************************
* Binary Tree class. Has a generic data item, and three pointers. one to its
* parent, and one to each of its two children.  Includes getters and setters
* for these values, as well as traversals to display it's different items
******************************************************************************/
template <class T>
class BTree
{
private:
   T data;            // --- data stored in node of tree
   BTree* left;       // --- pointer to left subtree
   BTree* right;      // --- pointer to right subtree
   BTree* parent;     // --- pointer to the parent node;

public:
   BTree();
   BTree(T data);
   ~BTree(void);

   void insertLeft (T item);      // creates a new node and inserts node to left
   void insertRight(T item);      // creates a new node and inserts node to right

   BTree* getLeftChild (void);    // return the ptr to the left child
   BTree* getRightChild(void);    // return the ptr to the right child
   BTree* getParent    (void);    // return parent
   T      getData      (void);

   void setData (T item);
   void setLeft (BTree* tree);
   void setRight(BTree* tree);

   void infix  (void);            // do infix traversal
   void prefix (void);            // do prefix traversal
   void postfix(void);            // do postfix traversal
   void level  (void);            // do level order traversal

   bool operator < (BTree*& rightSide);
};

/******************************************************************************
* A Letter is made specifically to work with the code. It has a value,
* "character", and a frequency, which represents how often the letter occurs.
* This class could be condensed into a struct, but its constructors and
* uses of assignment operators make it easy to work with. It also has a bool
* inserted which has use in determining whether the letter is inserted into
* the tree.
******************************************************************************/
class Letter
{
   public:
      Letter(void);
      Letter(int freq, char val = ' ');
      Letter(char val, int freq = 0);
      void operator = (int freq);
      void operator = (char val);
      char   value;
      int    frequency;
      bool   inserted;
};

typedef BTree<Letter> codeBit;

/******************************************************************************
* This code object allows you to insert Letters into a binary tree, and then
* generate a huffman code, coorelating with the frequencies of the letters.
* once the code is generated. a message string can be ciphered into the code
* or a code string can be deciphered into the message again.
******************************************************************************/
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
      void     find (char value, codeBit* &ptr, codeBit* place);

      codeBit* root;
      codeBit  array[52];
      int      numPar;
      int      size;
};
   
/******************************************************************************
* Main reads in a file of frequencies, assigns them to letters and inserts
* them into a code object. It then generates a huffman code, and displays
* the different codes for each letter.
******************************************************************************/
int main(int argc, char** argv)
{
   try
   {
      if (argc != 2)
         throw argc;
      ifstream read;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      
      Code   code1;
      int    frequency;
      Letter input = 'a';

      while (read >> frequency)      // Add letters to the code
      {
         input = frequency;
         code1.addLetter(input);
         input.value += 1;
      }
      code1.generate();              // Generate the code
      string character = "a";
      string coded;
      for (int i = 0; i < 26; i++)   // Display code for each character
      {
         cout << character << " = " << code1.cipher(character) << endl;
         character[0] = character[0] + 1;
      }
   }
   catch (int e)
   {
      cout << "Error: Must take exactly two arguments\n";
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }

   return 0;
}

/******************************************************************************
* Constructor for code object. Sets the number of characters and parent nodes
* to zero. Root pointer is set to NULL.
******************************************************************************/
Code::Code(void)
{
   size = 0;
   root = NULL;
   numPar = 0;
}

/******************************************************************************
* Adds a character to the code. All characters must be added before code is
* generated. Input is a Letter object containing a value (character) and its
* frequency.
******************************************************************************/
void Code::addLetter(Letter newChar)
{
   array[size].setData(newChar);
   size++;
   return;
}

/******************************************************************************
* Generates the huffman code from the letters added. Arranges the letters
* into a binary tree. No input.
******************************************************************************/
void Code::generate(void)
{
   codeBit* smallA;
   codeBit* smallB;
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
      array[26 + numPar].setData(temp);
      array[26 + numPar].setLeft(smallA);
      array[26 + numPar].setRight(smallB);
      numPar++;
   }
   // Set root to last item in array
   root = &array[25 + numPar];
   return;
}
   
/******************************************************************************
* Deciphers a string of huffman code. Input is a string representing a huffman
* code. It converts the code back into the original string. Can be a character
* or a word. sentences will lose their spaces. Returns the deciphered message.
******************************************************************************/
string Code::decipher(string value)
{
   string message;
   codeBit* ptr = root;

   for (int i = 0; i <= value.size(); i++) // Travel down the tree
   {
      if (value[i] == '0')
      {
         if (ptr->getRightChild() != NULL)
            ptr = ptr->getRightChild();
         else
         {
            message += ptr->getData().value;  // When the direction to go is
            ptr = root;                       // NULL, You've found it!
            i--;                              // Repeat last code value.
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

/******************************************************************************
* Ciphers a message one character at a time, and adds the 1s and 0s to a string
* Returns the string with the code of the full message.
******************************************************************************/
string Code::cipher(string message)
{
   string value;
   for (int i = 0; i < message.size(); i++)
      value += part(message[i]);
   return value;
}
  
/******************************************************************************
* Returns the code for a particular character. Input is the character to find
* the code for.
******************************************************************************/
string Code::part(char value)
{
   string charCode;
   string bit;
   codeBit* ptr = NULL;
   codeBit* place = root;
   
   find(value, ptr, place);     // Find the value in the tree.
   place = ptr;
   
   if (place == NULL)           // Work backwards through parents to find the
      charCode = " ";           // code.
   else
   {
      while (place->getParent() != NULL)
      {
         if (place->getParent()->getRightChild() == place)
               bit = "0";
         else
            bit = "1";
         charCode = bit + charCode;
         place = place->getParent();
      }
   }
   return charCode;
}

/******************************************************************************
* Finds the smallest frequency of all the letters. Returns the address of the
* smallest. Sets the bool in that letter to inserted to stop it from being
* included in the comparison.
******************************************************************************/
codeBit* Code::small(void)
{
   codeBit tempBit;
   Letter start;
   tempBit.setData(start);
   codeBit* ptr = &tempBit;
   
   int index = 0;

   // Search among letters
   for (int i = 0; i < size; i++)
   {
      if ((array[i].getData().frequency < ptr->getData().frequency) &&
          (array[i].getData().inserted == false))
      {
         ptr = &array[i];
         index = i;
      }
   }
   // Search among parents
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

/******************************************************************************
* Recursively finds a certain character in the binary tree using a prefix
* traversal. Once found, returns by value the address of the codeBit-Letter.
* Inputs are the character value to find, the pointer passed by reference that
* will be the location of the value. (will be null if not found). The last 
* parameter is a pointer pointing to the root of the tree. It will be the 
* start for the traversal.
******************************************************************************/
void Code::find(char value, codeBit* &ptr, codeBit* place)
{
   if (place->getData().value == value)   // Check the value
      ptr = place;
   else
   {
      if (place->getLeftChild() != NULL)  // Try Left
      {
         find(value, ptr, place->getLeftChild());
         if (ptr != NULL) return;         // Stop if found.
      }
      if (place->getRightChild() != NULL) // Try Right
         find(value, ptr, place->getRightChild());
   }
   return;
}

/******************************************************************************
* Constructor for a Letter. Sets to a high frequency so as to not be included
* in comparisons.
******************************************************************************/
Letter::Letter(void)
{
   frequency   = 1000000;
   value       = ' ';
   inserted    = false;
}

/******************************************************************************
* Constructor for Letter. Inputs interchangeable - a character and an integer
******************************************************************************/
Letter::Letter(int freq, char val)
{
   frequency = freq;
   value = val;
   inserted    = false;
}

/******************************************************************************
* Constructor for Letter. Inputs interchangeable - a character and an integer
******************************************************************************/
Letter::Letter(char val, int freq)
{
   frequency = freq;
   value = val;
   inserted    = false;
}      

/******************************************************************************
* Sets the frequency to an integer value input.
******************************************************************************/
void Letter::operator = (int freq)
{
   frequency = freq;
   return;
}

/******************************************************************************
* Sets the value to a character value input.
******************************************************************************/
void Letter::operator = (char val)
{
   value = val;
   return;
}
   
/*************************************************************
 * Constructor, sets data to item or zero by default. Sets
 * all pointers to NULL.
 ************************************************************/
template <class T>
BTree<T>::BTree()
{
   right  = NULL;
   left   = NULL;
   parent = NULL;
}

/*************************************************************
 * Constructor, sets data to item or zero by default. Sets
 * all pointers to NULL.
 ************************************************************/
template <class T>
BTree<T>::BTree(T item)
{
   data   = item;
   right  = NULL;
   left   = NULL;
   parent = NULL;
}

/*************************************************************
 * Destructor for BTree (Doesn't do anything) Left for the user
 * of the class
 ************************************************************/
template <class T>
BTree<T>::~BTree(void)
{
}

/*************************************************************
 * Creates a new node and inserts node to left
 ************************************************************/
template <class T>
void BTree<T>::insertLeft(T item)
{
   left = new BTree(item);
   left->parent = this;
   return;
}

/*************************************************************
 * Creates a new node and inserts node to right
 ************************************************************/
template <class T>
void BTree<T>::insertRight(T item)
{
   right = new BTree(item);
   right->parent = this;
   return;
}

/*************************************************************
 * Return the ptr to the left child
 ************************************************************/
template <class T>
BTree<T>* BTree<T>::getLeftChild(void)
{
   return left;
}

/*************************************************************
 * Return the ptr to the right child
 ************************************************************/
template <class T>
BTree<T>* BTree<T>::getRightChild(void)
{
   return right;
}

/*************************************************************
 * Return parent
 ************************************************************/
template <class T>
BTree<T>* BTree<T>::getParent(void)
{
   return parent;
}

/*************************************************************
 * Returns the data (integer)
 ************************************************************/
template <class T>
T BTree<T>::getData(void)
{
   return data;
}

/*************************************************************
 * Sets the data to given input integer
 ************************************************************/
template <class T>
void BTree<T>::setData(T item)
{
   data = item;
   return;
}

/*************************************************************
 * Sets the left pointer to given input pointer
 ************************************************************/
template <class T>
void BTree<T>::setLeft(BTree* tree)
{
   left = tree;
   if (tree != NULL)
      tree->parent = this;
   return;
}

/*************************************************************
 * Sets the right pointer to given input pointer
 ************************************************************/
template <class T>
void BTree<T>::setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
   return;
}

/*************************************************************
 * Do infix traversal (displays data in tree)
 ************************************************************/
template <class T>
void BTree<T>::infix(void)
{
   if (left != NULL)
      left->infix();
   cout << data << " ";
   if (right != NULL)
      right->infix();
   return;
}

/*************************************************************
 * Do prefix traversal (displays data in tree)
 ************************************************************/
template <class T>
void BTree<T>::prefix(void)
{
   cout << data << " ";
   if (left != NULL)
      left->prefix();
   if (right != NULL)
      right->prefix();
   return;
}

/*************************************************************
 * Do postfix traversal (displays data in tree)
 ************************************************************/
template <class T>
void BTree<T>::postfix(void)
{
   if (left != NULL)
      left->postfix();
   if (right != NULL)
      right->postfix();
   cout << data << " ";
   return;
}

/*************************************************************
 * Do level order traversal (displays data in tree)
 ************************************************************/
template <class T>
void BTree<T>::level(void)
{
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << " Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;

      }
   }
}

/*************************************************************
 *
 ************************************************************/
template <class T>
bool BTree<T>::operator < (BTree*& rightSide)
{
   if (data < rightSide.data)
      return true;
   else
      return false;
}



