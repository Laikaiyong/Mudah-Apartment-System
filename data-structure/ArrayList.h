/**
 * FILENAME: ArrayList.h
 */
#pragma once
#include <iostream>
#include <stdexcept>
#include "List.h"
using namespace std;

template <typename T>
class ArrayList : public List<T>
{
    T *array;     // pointer reference to this->array
    int capacity; // capacity of the element
    int size;     // current index of the element will be always empty

    void grow();

public:
    ArrayList();

    ArrayList(T *array, int size);

    ~ArrayList();

    T &get(int index);

    int indexOf(T object);

    void add(T object);

    void add(T object, int index);

    T remove(int index);

    bool remove(T object);

    int getSize();

    void clear();

    T *cloneArray();

    T *getArray();

    void printAll()
    // temporary function, DOES NOT WORK on object
    {
        cout << "[";
        for (int i = 0; i < size - 1; i++)
        {
            cout << this->array[i] << ",";
        }
        cout << this->array[size - 1] << "]" << endl;
    }
};

template <typename T>
ArrayList<T>::ArrayList()
{
    this->capacity = 10;
    this->size = 0;
    this->array = new T[capacity];
}

template <typename T>
ArrayList<T>::ArrayList(T *array, int size)
{
    if (size <= 0 || array == nullptr)
    {
        throw std::invalid_argument("Invalid array or size");
    }
    this->capacity = size;
    this->size = size;
    this->array = array;
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] this->array;
}

template <typename T>
void ArrayList<T>::grow()
{
    capacity *= 2;
    T *newArray = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        newArray[i] = this->array[i];
    }
    delete[] this->array; // Deallocate the old this->array
    this->array = newArray;
}

template <typename T>
T &ArrayList<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return this->array[index];
}

template <typename T>
int ArrayList<T>::indexOf(T object)
{
    for (int i = 0; i < size; i++)
    {
        if (this->array[i] == object)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void ArrayList<T>::add(T object)
{
    if (size >= capacity)
    {
        grow();
    }
    this->array[size] = object;
    size++;
}

template <typename T>
void ArrayList<T>::add(T object, int index)
{
    if (index < 0 || index > size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    if (size >= capacity)
    {
        grow();
    }

    for (int i = size; i > index; i--)
    {
        this->array[i] = this->array[i - 1];
    }
    this->array[index] = object;
    size++;
}

template <typename T>
T ArrayList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    T object = this->array[index];
    for (int i = index; i < size - 1; i++)
    {
        this->array[i] = this->array[i + 1];
    }
    // Set the last element to default value
    this->array[size - 1] = T();

    size--;
    return object;
}

template <typename T>
bool ArrayList<T>::remove(T object)
{
    int index = indexOf(object);
    if (index == -1)
    {
        return false;
    }
    for (int i = index; i < size - 1; i++)
    {
        this->array[i] = this->array[i + 1];
    }
    // Set the last element to default value
    this->array[size - 1] = T();

    size--;
    return true;
}

template <typename T>
int ArrayList<T>::getSize()
{
    return this->size;
}

template <typename T>
void ArrayList<T>::clear()
{
    for (int i = 0; i < size; i++)
    {
        this->array[i] = T();
    }
}

template <typename T>
T *ArrayList<T>::cloneArray()
{
    T *duplicateArray = new T[size];
    for (int i = 0; i < size; i++)
    {
        duplicateArray[i] = this->array[i];
    }
    return duplicateArray;
}

template <typename T>
T *ArrayList<T>::getArray()
{
    return this->array;
}
