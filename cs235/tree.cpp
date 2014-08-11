/*************************************************************
* Program:
*    Assignment 13, Tree Class
*    Brother Ercanbrack, CS235
* Author:
*    Haru McClellan
* Description:
*    This file includes the functions required to implement
*    a tree.
************************************************************/
#include <iostream>
#include "tree.h"
using namespace std;

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


