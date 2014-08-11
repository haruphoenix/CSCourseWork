/*****************************************************************************
* Program:
*    Queue
*
******************************************************************************/
#include <iostream>
using namespace std;

const int DEFAULT_QUEUE = 5;

/*****************************************************************************
* 
******************************************************************************/
template <class T>
class Queue
{
   public:
      Queue(void);
      Queue(int size);
      Queue(const Queue& original);
      ~Queue(void);

      void insert(T item); // Inserts an item at the back
      void remove(void);   // Removes front item

      T front(void); // Returns front item
      T next (void); // Returns front item and removes it

      bool full(void);
      bool empty(void);
      int  size(void);

      Queue<T>& operator = (const Queue<T>& rtSide);
   
   private:
      T*  line;
      int theFront;
      int back;
      int maxSize;
      int currentSize;
};


/*****************************************************************************
* main description
******************************************************************************/
int main()
{
   Queue<char> a;
      
   
   return 0;
}


/*****************************************************************************
* 
******************************************************************************/
template <class T>
Queue<T>::Queue(void)
{
   maxSize = DEFAULT_QUEUE;
   line = new T[maxSize];
   currentSize = 0;
   theFront = 0;
   back = 0;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
Queue<T>::Queue(int size)
{
   maxSize = size;
   line = new T[maxSize];
   currentSize = 0;
   theFront = 0;
   back = 0;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
Queue<T>::Queue(const Queue& original)
{
   maxSize = original.maxSize;
   line = new T[maxSize];
   theFront = 0;
   back = 0;
   for (int i = 0; i < original.currentSize; i++)
   {
      insert(original.line[i]);
   }
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
Queue<T>::~Queue(void)
{
   delete [] line;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
void Queue<T>::insert(T item)
{
   if (currentSize < maxSize)
   {
      if (back == maxSize)
         back = 0;
      line[back] = item;
      back++;
      currentSize++;
   }
   else
   {
      T* newLine = new T[(maxSize * 2)];
      int newBack = theFront;
      for (int i = 0; i < maxSize; i++)
      {
         newLine[i] = line[newBack];
         newBack++;
         if (newBack == maxSize)
            newBack = 0;
      }
      delete [] line;
      maxSize *= 2;
      line = newLine;
      line[back] = item;
      back++;
      currentSize++;
   }
      
   return;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
void Queue<T>::remove(void)
{
   if (currentSize > 0)
   {
      theFront++;
      currentSize--;
      if (theFront == maxSize)
         theFront = 0;
   }
   return;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
T Queue<T>::front(void)
{
   return line[theFront];
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
T Queue<T>::next(void)
{
   T item = line[theFront];
   remove();
   return item;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
bool Queue<T>::full(void)
{
   bool isFull = false;
   if (currentSize == maxSize)
      isFull = true;
   return isFull;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
bool Queue<T>::empty(void)
{
   bool isEmpty = false;
   if (currentSize == 0)
      isEmpty = true;
   return isEmpty;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
int Queue<T>::size(void)
{
   return currentSize;
}

/*****************************************************************************
* 
******************************************************************************/
template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& rtSide)
{
   delete [] line;
   maxSize = rtSide.maxSize;
   line = new T[maxSize];
   currentSize = rtSide.currentSize;
   for (int i = 0; i < currentSize; i++)
      line[i] = rtSide.line[i];
   theFront = rtSide.theFront;
   back = rtSide.back;
   
   return *this;
}
