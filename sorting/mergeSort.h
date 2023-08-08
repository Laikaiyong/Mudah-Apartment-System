#include <iostream>
using namespace std;

template<typename T, typename Compare>
void mergeSort(T *array, int length, Compare compare)
{
    int mid = length / 2;

    // stop if length lesss than 1
    if (length <= 1)
        return;

    T *leftArray = new T[mid];
    T *rightArray = new T[length - mid];

    int i = 0, j = 0;
    for (; i < length; i++)
    {
        // insert all the element from array middle left index into left array
        if (i < mid)
        {
            leftArray[i] = array[i];
        }
        else
        // insert all the element from array middle right index into right array
        {
            rightArray[j] = array[i];
            j++;
        }
    }
    // focus on left side
    mergeSort(leftArray, mid, compare);
    // focus on right side
    mergeSort(rightArray, length - mid, compare);
    // start to merge and sort
    merge(array, leftArray, rightArray, mid, length - mid, compare);
    delete[] leftArray;
    delete[] rightArray;
}

template<typename T, typename Compare>
void merge(T *array, T *leftArray, T *rightArray, int leftSize, int rightSize, Compare compare)
{
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize)
    {
        // compare left array and right array element, left < right if ascending order, left > right if descending order
        if (compare(leftArray[l], rightArray[r]))
        {
            array[i++] = leftArray[l++];
        }
        else
        {
            array[i++] = rightArray[r++];
        }
    }
    // insert the rest of the left array element when right array is finish insert all
    for (; l < leftSize; l++)
    {
        array[i++] = leftArray[l];
    }
    // insert the rest of the right array element when left array is finish insert all
    for (; r < rightSize; r++)
    {
        array[i++] = rightArray[r];
    }
}
