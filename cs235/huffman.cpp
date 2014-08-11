/*************************************************************************
* Program:
*    Assignment 15, Huffman Code
*    Brother Ercanbrack, cs235
* Author:
*    Haru McClellan
* Summary:
*    Implementation file for binary search tree class
**************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 50;
const int NUM_CHARS = 26;

/*************************************************************
* 
**************************************************************/
template <class T>
class BTree
{
   private:
      T data;          // --- data stored in node of tree
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


/*************************************************************
* 
**************************************************************/
struct codeLetter
{
   int frequency;
   char letter;
};

bool operator <  (codeLetter first, codeLetter second);
bool operator >  (codeLetter first, codeLetter second);
bool operator == (codeLetter first, codeLetter second);
ostream& operator << (ostream& out, codeLetter& letter);

/*************************************************************
* 
**************************************************************/
class huffmanCode
{
   public:
      huffmanCode();
      ~huffmanCode();
   
      void   addLetter(codeLetter letter);
      void   generateCode();
   
      string getCode  (string phrase );
      string getPhrase(string codeSeg);

      string findCodeSeg(char segment);
      
   private:
      BTree<codeLetter>* code;
      BTree<codeLetter>** letters;
      int size;
};

/*************************************************************
* 
**************************************************************/
int main(int argc, char** argv)
{
   try
   {
      huffmanCode myCode;
      if (argc != 2)
         throw argc;
      ifstream read;
      read.open(argv[1]);
      if (read.fail())
         throw argv[1];
      
      int freq;
      int numLetters = 0;
      codeLetter cLetter;
      cLetter.letter = ('a' - 1);
         
      for (int i = 0; i < NUM_CHARS; i++)
      {
         read >> freq;
         cLetter.frequency = freq;
         cLetter.letter = cLetter.letter + 1;
         myCode.addLetter(cLetter);
      }
      
      read.close();
      
      myCode.generateCode();
      char start = 'a';
      for (int i = 0; i < NUM_CHARS; i++)
         cout << char(start + i) << " = " << myCode.findCodeSeg(start + i) << endl;
   }
   catch (char* e)
   {
      cout << "Error: Cannot open " << e << endl;
   }
   catch (int e)
   {
      cout << "Error: Please specify file to open\n";
   }
   return 0;
}

/*************************************************************
* 
**************************************************************/
huffmanCode::huffmanCode()
{
   size = 0;
   letters = new BTree<codeLetter>*[NUM_CHARS];
}

/*************************************************************
* 
**************************************************************/
huffmanCode::~huffmanCode()
{
   for (int i = (size - 1); i > -1; i--)
      delete letters[i];
   delete [] letters;
}
   
/*************************************************************
* 
**************************************************************/
void huffmanCode::addLetter(codeLetter letter)
{
   letters[size] = new BTree<codeLetter>;
   letters[size]->setData(letter); // letters[0] == NULL...
   size++;
   return;
}

/*************************************************************
* 
**************************************************************/
void huffmanCode::generateCode()
{
   int j;
   int k;
   
   BTree<codeLetter>* start = new BTree<codeLetter>;
   codeLetter startData;
   startData.frequency = 99999999;
   startData.letter = ' ';
   start->setData(startData);

   BTree<codeLetter>** smallestA = &start;
   BTree<codeLetter>** smallestB = &start;
   
   for (int i = 0; i < size - 1; i++)
   {
      smallestA = &start;
      smallestB = &start;
      
      // Find smallest
      for (j = 0; j < size; j++)
         if ((letters[j]->getData() < (*smallestA)->getData()) && (letters[j]->getData().frequency > 0))
         {
            cout << "j: " << i << endl;
            smallestA = &letters[j];
         }
      startData.letter = (*smallestA)->getData().letter;
      startData.frequency = -(*smallestA)->getData().frequency;
      (*smallestA)->setData(startData);
            
      // Find next smallest
      for (k = 0; k < size; k++)
         if ((letters[k]->getData() < (*smallestB)->getData()) && (letters[k]->getData().frequency > 0))
         {
            cout << "k: " << i << endl;
            smallestB = &letters[k];
         }
      startData.letter = (*smallestB)->getData().letter;
      startData.frequency = -(*smallestB)->getData().frequency;
      (*smallestB)->setData(startData);
            

      // Create a new node with a frequency the sum of two smallest
      startData.frequency = (-(*smallestA)->getData().frequency) +
         (-(*smallestB)->getData().frequency);
      BTree<codeLetter>* fork = new BTree<codeLetter>(startData);

      // Set children of new node to two smallest
      fork->setRight(*smallestB);
      fork->setLeft(*smallestA);
      
      // Add new node back to the array
      letters[j] = fork;
   }

   // Set the only value left to be the root of the tree
   for (int i = 0; i < size; i++)
   {
      if (letters[i]->getData().frequency > 0)
      {
         code = letters[i];
         break;
      }
   }
   
   return;
}
   
/*************************************************************
* 
**************************************************************/
string huffmanCode::getCode(string phrase)
{
   string newCode;

   for (int i = 0; i < phrase.size(); i++)
   {
      newCode += findCodeSeg(phrase[i]);
   }
   
   return newCode;
}

/*************************************************************
* 
**************************************************************/
string huffmanCode::findCodeSeg(char segment)
{
   string seg   = "";
   int segSize  = 0;
   int segPlace = 0;
   BTree<codeLetter>* pointer = code;
   
   int levelLeft  = 0;
   bool end = false;
   bool lastLeft = false;

   while (!end && (pointer != NULL))
   {
      if (pointer->getData().letter == segment)
         break;
      else if ((pointer->getLeftChild() != NULL) && !lastLeft)
      {
         pointer = pointer->getLeftChild();
         if (seg.size() < segSize)
            seg[segPlace] = '0';
         else
         {
            segSize++;
            segPlace++;
            seg += "0";
            levelLeft++;
         }
      }
      else if (pointer->getRightChild() != NULL)
      {
         lastLeft = false;
         pointer = pointer->getRightChild();
         if (seg.size() < segSize)
            seg[segPlace] = '1';
         else
         {
            segSize++;
            segPlace++;
            seg += "1";
         }
      }
      else if (levelLeft != 0)
      {
         if (pointer->getParent()->getLeftChild() == pointer)
            levelLeft--;
         pointer = pointer->getParent();
         segPlace--;
         lastLeft = true;
      }
      else
         end = true;
   }

   return seg;
}

/*************************************************************
* 
**************************************************************/
string huffmanCode::getPhrase(string codeSeg)
{
   string phrase;
   
   BTree<codeLetter>* pointer = code;
   for (int i = 0; i < codeSeg.size(); i++)
   {
      if (codeSeg[i] == 1)
      {
         if (pointer->getRightChild() != NULL)
            pointer = pointer->getRightChild();
         else
         {
            phrase += pointer->getData().letter;
            pointer = code;
            i--;
         }
      }
      else
      {
         if (pointer->getLeftChild() != NULL)
            pointer = pointer->getLeftChild();
         else
         {
            phrase += pointer->getData().letter;
            pointer = code;
            i--;
         }
      }
   }
  
   return phrase;
}

/*************************************************************
* 
**************************************************************/
bool operator < (codeLetter first, codeLetter second)
{
   if (first.frequency < second.frequency)
      return true;
   else
      return false;
}

/*************************************************************
* 
**************************************************************/
bool operator > (codeLetter first, codeLetter second)
{
   if (first.frequency > second.frequency)
      return true;
   else
      return false;
}

/*************************************************************
* 
**************************************************************/
bool operator == (codeLetter first, codeLetter second)
{
   if (first.frequency == second.frequency)
      return true;
   else
      return false;
}

/*************************************************************
* 
**************************************************************/
ostream& operator << (ostream& out, codeLetter& letter)
{
   out << letter.letter;
   return out;
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
