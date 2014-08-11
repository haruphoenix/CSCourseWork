/*************************************************************************
* Program:
*    Assignment 14, Binary Search Tree
*    Brother Ercanbrack, cs235
* Author:
*    Haru McClellan
* Summary:
*    Implementation file for binary search tree class
**************************************************************************/
#include <iostream>
using namespace std;

#include "tree.h"
#include "bst.h"

const int MAX = 50;

/*************************************************************
 * Constructor, sets data to item or zero by default. Sets
 * all pointers to NULL.
 ************************************************************/
BTree::BTree(int item)
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
BTree::~BTree(void)
{
}

/*************************************************************
 * Creates a new node and inserts node to left
 ************************************************************/
void BTree::insertLeft(int item)
{
   BTree* newBranch = new BTree(item);
   left = newBranch;
   newBranch->parent = this;
   return;
}

/*************************************************************
 * Creates a new node and inserts node to right
 ************************************************************/
void BTree::insertRight(int item)
{
   BTree* newBranch = new BTree(item);
   right = newBranch;
   newBranch->parent = this;
   return;
}

/*************************************************************
 * Return the ptr to the left child
 ************************************************************/
BTree* BTree::getLeftChild(void)
{
   return left;
}

/*************************************************************
 * Return the ptr to the right child
 ************************************************************/
BTree* BTree::getRightChild(void)
{
   return right;
}

/*************************************************************
 * Return parent
 ************************************************************/
BTree* BTree::getParent(void)
{
   return parent;
}

/*************************************************************
 * Returns the data (integer)
 ************************************************************/
int BTree::getData(void)
{
   return data;
}

/*************************************************************
 * Sets the data to given input integer
 ************************************************************/
void BTree::setData(int item)
{
   data = item;
   return;
}

/*************************************************************
 * Sets the left pointer to given input pointer
 ************************************************************/
void BTree::setLeft(BTree* tree)
{
   left = tree;
   if (tree != NULL)
      tree->parent = this;
   return;
}

/*************************************************************
 * Sets the right pointer to given input pointer
 ************************************************************/
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
   return;
}

/*************************************************************
 * Do infix traversal (displays data in tree)
 ************************************************************/
void BTree::infix(void)
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
void BTree::prefix(void)
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
void BTree::postfix(void)
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
void BTree::level(void)
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

/*************************************************************************
* Constructor for binary search tree
**************************************************************************/
BST::BST()
{
   root = NULL;
}

/*************************************************************************
* Returns true if the tree is empty. False if not
**************************************************************************/
int BST::empty(void)
{
   if (root == NULL)
      return 1;
   else
      return 0;
}

/*************************************************************************
* Searches the Binary tree for a given value. Returns the address of the
* item, or NULL if not found
**************************************************************************/
BTree* BST::search(int item)
{
   BTree* loc = root;
   while (loc != NULL)
   {
      if (loc->getData() == item)
         break;
      else if (item < loc->getData())
         loc = loc->getLeftChild();
      else
         loc = loc->getRightChild();
   }
   return loc;
}

/*************************************************************************
* Inserts an item into the Binary search tree in the correct location.
* Input is the item to insert.
**************************************************************************/
void BST::insert(int item)
{
   BTree* loc = root;
   if (root == NULL)
   {
      BTree* leaf = new BTree(item);
      root = leaf;
      return;
   }
   while (true)
   {
      if (item < loc->getData())
      {
         if (loc->getLeftChild() != NULL)
            loc = loc->getLeftChild();
         else
         {
            loc->insertLeft(item);
            break;
         }
      }
      else
      {
         if (loc->getRightChild() != NULL)
            loc = loc->getRightChild();
         else
         {
            loc->insertRight(item);
            break;
         }
      }
   }
   return;
}

/*************************************************************************
* Searches through the tree for the item to remove. Removes the item.
**************************************************************************/
void BST::remove(int item)
{
   BTree* target = search(item);
   if (target != NULL)
   {
      //               Deleting a Leaf
      if ((target->getLeftChild() == NULL) &&   
          (target->getRightChild() == NULL))
      {
         if (target != root)
         {
            if (target->getParent()->getLeftChild() == target)
               target->getParent()->setLeft(NULL);
            else
               target->getParent()->setRight(NULL);
         }
         else
            root = NULL;
         delete target;
      }
      //       Deleting a Branch with a Right Child
      else if (target->getLeftChild() == NULL) 
      {
         if (target != root)
         {
            if (target->getParent()->getLeftChild() == target)
               target->getParent()->setLeft(target->getRightChild());
            else
               target->getParent()->setRight(target->getRightChild());
         }
         else
            root = target->getRightChild();
         delete target;                         
      }
      //        Deleting a Branch with a Left Child
      else if (target->getRightChild() == NULL)   
      {
         if (target != root)
         {
            if (target->getParent()->getLeftChild() == target)
               target->getParent()->setLeft(target->getLeftChild());
            else
               target->getParent()->setRight(target->getLeftChild());
         }
         else
            root = target->getLeftChild();
         delete target;                         
      }
      //        Deleting a Branch with Two Children
      else                                    
      {
         BTree* newBranch = target->getRightChild();
         while (newBranch->getLeftChild() != NULL)
            newBranch = newBranch->getLeftChild();
         target->setData(newBranch->getData());
         if (newBranch->getRightChild() != NULL)
         {
            if (newBranch->getParent() != target)
               newBranch->getParent()->setLeft(newBranch->getRightChild());
            else
               newBranch->getParent()->setRight(newBranch->getRightChild());
         }
         else
         {
            if (newBranch->getParent() != target)
               newBranch->getParent()->setLeft(NULL);
            else
               newBranch->getParent()->setRight(NULL);
         }
         delete newBranch;
      }
   }
   else
      cout << "Item " << item << " is not found, cannot delete it!\n";
}

/*************************************************************************
* Displays the Binary Search Tree in Infixed order. (smallest to greatest)
**************************************************************************/
void BST::BSTInfix(void)
{
   if (root != NULL)
      root->infix();
   return;
}
