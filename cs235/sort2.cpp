/*************************************************************************
 * Simple Sorts
 *
 ************************************************************************/
#include <iostream>
using namespace std;

template <class T>
void sort(T* array, int first, int last);

template <class T>
int partition(T* array, int first, int last);

/*************************************************************************
 *
 ************************************************************************/
int main()
{
   int* array = new int[25];
   
   for (int i = 0; i < 25; i++)
      array[i] = i + 1;
   
   for (int i = 0; i < 25; i++)
      cout << array[i] << " ";
   
   cout << endl;
   sort(array, 0, 24);
   
   for (int i = 0; i < 25; i++)
      cout << array[i] << " ";

   cout << endl;
   return 0;
}

/*************************************************************************
 *
 ************************************************************************/
template <class T>
void sort(T* array, int first, int last)
{
   if (first < last)
   {
      int middle = partition(array, first, last);
      sort(array, first, middle);
      sort(array, middle+1, last);
   }
}

/*************************************************************************
 *
 ************************************************************************/
template <class T>
int partition(T* array, int first, int last)
{
   T pivot = array[first];
   T temp;
   
   while (first < last)
   {
      while (pivot > array[last])
         last--;
      while (pivot < array[first])
         first++;
      if (first < last)
      {
         temp = array[first];
         array[first] = array[last];
         array[last] = temp;
      }  
   }
   return last;
}
