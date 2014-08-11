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

int main()
{
   int array[10] = {4, 2, 3, 5, 3, 9, 7, 8, 5, 10};
   for (int i = 0; i < 5; i++)
      cout << array[i] << " ";
   cout << endl;
   sort(array, 0, 9);
   for (int i = 0; i < 10; i++)
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

   while (first <= last)
   {
      while (array[first] < pivot) // > = descending
         first++;
      while (array[last]  > pivot) // < = descending
         last--;
      if (first <= last)
      {
         temp = array[first];
         array[first] = array[last];
         array[last] = temp;
         first++;
         last--;
      }
   }
   return last;
}

