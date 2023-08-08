#include "../sorting/oldQuickSort.h"

int main() {
  int data[] = {8, 7, 6, 1, 0, 9, 2};
  int n = sizeof(data) / sizeof(data[0]);
  
  cout << "Unsorted Array: \n";
  printArray(data, n);
  
  quickSort(data, 0, n - 1);
  
  cout << "Sorted array in ascending order: \n";
  printArray(data, n);
}