#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 50;

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
