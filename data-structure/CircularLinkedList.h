/**
 * FILENAME: DoublyLinkedList.h
 */

#include <iostream>
using namespace std;

/**
 * with class implementation...
 */

template <typename T>
struct DoublyNode
{
    T data;
    DoublyNode<T> *prev;
    DoublyNode<T> *next;
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

    void insertAtBeginning(T element);

    void insertAtEnd(T element);

    void insertItemAt(T element, int index);

    void deleteFirst();

    void deleteLast();

    void deleteItemAt(int index);

    T get(int index);

    bool find(T element);

    int getSize();

    void clear();

    T *cloneArray();
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
}

template <typename T>
CiruclarLinkedList<T>::~CiruclarLinkedList()
{
    DoublyNode<T> *next;
    while (this->head != nullptr)
    {
        next = this->head->next;
        delete this->head;
        this->head = next;
    }
}

template <typename T>
void CiruclarLinkedList<T>::insertAtBeginning(T element)
{
}