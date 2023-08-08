#include <iostream>

using namespace std;

template<typename T>
void swap(T *p1, T *p2)
{
  T temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

template<typename T, typename Compare>
int partition(T array[], int low, int high, Compare compare)
{
  T pivot = array[high];
  
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (compare(array[j], pivot)) {
      i++;
      
      swap(&array[i], &array[j]);
    }
  }
  
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

template<typename T, typename Compare>
void quickSort(T array[], int low, int high, Compare compare) {
  if (low < high) {
    int pi = partition(array, low, high, compare);

    quickSort(array, low, pi - 1, compare);
    quickSort(array, pi + 1, high, compare);
  }
}


