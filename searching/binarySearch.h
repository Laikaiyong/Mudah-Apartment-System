#include <iostream>
using namespace std;

template <typename T, typename Compare>
int binarySearch(T *array, int size, T value, Compare compare)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (compare(array[mid], value)) // comparison must use < if ascending order
        {
            left = mid + 1; // Value is greater, ignore left half
        }
        else if (compare(value, array[mid]))
        {
            right = mid - 1; // Value is smaller, ignore right half
        }
        else
        {
            return mid; // Value found at index mid
        }
    }

    return -1; // Value not found
}