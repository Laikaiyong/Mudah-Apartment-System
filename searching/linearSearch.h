#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H
#include <iostream>
using namespace std;

template <typename T, typename Compare>
int linearSearch(T *array, int size, T value, Compare compare)
{
    for (int i = 0; i < size; ++i)
    {
        if (compare(array[i], value))
        {
            return i;
        }
    }

    return -1;
}
#endif
