/**
 * FILENAME: DoublyLinkedList.h
 */
#pragma once
#include <iostream>
#include <stdexcept>
#include "List.h"
using namespace std;

template <typename T>
struct DoublyNode
{
    T data;
    DoublyNode<T> *prev;
    DoublyNode<T> *next;

    DoublyNode(T &data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

    DoublyNode(T &data, DoublyNode<T> *prev)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = prev;
    }

    DoublyNode(T &data, DoublyNode<T> *next, DoublyNode<T> *prev)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template <typename T>
class CiruclarLinkedList : public List<T>
{
    DoublyNode<T> *head;
    int size;

public:
    CiruclarLinkedList();

    CiruclarLinkedList(T *array, int size);

    ~CiruclarLinkedList();

    T &get(int index);

    template <typename Compare>
    int customIndexOf(T element, Compare compare);

    void add(T element);

    void add(T element, int index);

    T remove(int index);

    bool remove(T element);

    bool find(T element);

    template <typename Compare>
    bool customFind(T element, Compare compare);

    int getSize();

    void clear();

    T *cloneArray();

    void showForward()
    // temporary function
    {
        DoublyNode<T> *current = this->head;
        cout << "--- DISPLAY LINKED LIST [FORWARD] = " << size << " elements ---" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void showBackward()
    // temporary function
    {
        DoublyNode<T> *current;
        if (this->head != nullptr)
        {
            current = this->head->prev;
        }
        cout << "--- DISPLAY LINKED LIST [BACKWARD] = " << size << " elements ---" << endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

template <typename T>
CiruclarLinkedList<T>::CiruclarLinkedList()
{
    this->head = nullptr;
    this->size = 0;
}

template <typename T>
CiruclarLinkedList<T>::CiruclarLinkedList(T *array, int size)
{
    if (size <= 0 || array == nullptr)
    {
        throw invalid_argument("Invalid array or size");
    }

    this->head = nullptr;
    this->size = 0;

    for (int i = 0; i < size; i++)
    {
        add(array[i]);
    }
}

template <typename T>
CiruclarLinkedList<T>::~CiruclarLinkedList()
{
    clear();
}

template <typename T>
T &CiruclarLinkedList<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of bounds");
    }
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}

template <typename T>
template <typename Compare>
int CiruclarLinkedList<T>::customIndexOf(T element, Compare compare)
{
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < size; i++)
    {
        if (compare(current->data, element))
        {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template <typename T>
void CiruclarLinkedList<T>::add(T element)
{
    DoublyNode<T> *newNode = new DoublyNode<T>(element);
    if (this->head == nullptr)
    {
        this->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else
    {
        newNode->next = this->head;
        newNode->prev = this->head->prev;
        this->head->prev->next = newNode;
        this->head->prev = newNode;
    }
    this->size++;
}

template <typename T>
void CiruclarLinkedList<T>::add(T element, int index)
{
    if (index < 0 || index > size)
    {
        throw out_of_range("Index out of bounds");
    }
    if (this->head == nullptr && index == 0)
    {
        add(element);
        return;
    }
    DoublyNode<T> *current = this->head;
    int mid = this->size / 2;

    if (index <= mid)
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        for (int i = size; i > index; i--)
        {
            current = current->prev;
        }
    }
    DoublyNode<T> *newNode = new DoublyNode<T>(element, current, current->prev);
    current->prev->next = newNode;
    current->prev = newNode;
    if (index == 0)
    {
        this->head = newNode;
    }
    this->size++;
}

template <typename T>
T CiruclarLinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("Index out of bounds");
    }

    DoublyNode<T> *current = this->head;
    int mid = this->size / 2;

    if (index <= mid)
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        for (int i = size; i > index; i--)
        {
            current = current->prev;
        }
    }
    T data = current->data;

    if (size == 1)
    {
        this->head = nullptr;
    }
    else
    {
        current->next->prev = current->prev;
        current->prev->next = current->next;
        if (index == 0)
        {
            this->head = current->next;
        }
    }
    delete current;
    this->size--;
    return data;
}

template <typename T>
bool CiruclarLinkedList<T>::remove(T element)
{
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < size; i++)
    {
        if (current->data == element)
        {
            if (size == 1)
            {
                this->head = nullptr;
            }
            else
            {
                current->next->prev = current->prev;
                current->prev->next = current->next;
                if (i == 0)
                {
                    this->head = current->next;
                }
            }
            delete current;
            this->size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool CiruclarLinkedList<T>::find(T element)
{
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < size; i++)
    {
        if (current->data == element)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
template <typename Compare>
bool CiruclarLinkedList<T>::customFind(T element, Compare compare)
{
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < size; i++)
    {
        if (compare(current->data, element))
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
int CiruclarLinkedList<T>::getSize()
{
    return this->size;
}

template <typename T>
void CiruclarLinkedList<T>::clear()
{
    DoublyNode<T> *current;
    for (int i = 0; i < size; i++)
    {
        current = this->head->next;
        delete this->head;
        this->head = current;
    }
    this->head = nullptr;
    this->size = 0;
}

template <typename T>
T *CiruclarLinkedList<T>::cloneArray()
{
    T *newArray = new T[this->size];
    DoublyNode<T> *current = head;
    for (int i = 0; i < size; i++)
    {
        newArray[i] = current->data;
        current = current->next;
    }
    return newArray;
}