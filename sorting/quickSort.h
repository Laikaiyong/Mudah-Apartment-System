#include <iostream>
#include "../dao/propertyDao.h"
#include "../entity/property.h"
using namespace std;

template<typename T, typename P>
int partition(P& arr, int low, int high, int propertyIndex) {
    T pivot = arr[high]; // Choose the pivot as the last element
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        // Compare with the chosen property
        if (arr[j].completionYear <= pivot.completionYear) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T, typename Compare>
void quickSort(T& arr, int low, int high, int propertyIndex) {
    if (low < high) {
        int pivot = partition(arr, low, high, propertyIndex);
        quickSort(arr, low, pivot - 1, propertyIndex);
        quickSort(arr, pivot + 1, high, propertyIndex);
    }
}

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
