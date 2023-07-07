/**
 * FILENAME: DoublyLinkedList.h
 */

#include <iostream>
using namespace std;

/**
 * with class implementation...
 */

template <typename T>
class DoublyNode : public List<T>
{
public:
    T data;
    DoublyNode<T> *prev;
    DoublyNode<T> *next;
};

template <typename T>
class CiruclarLinkedList
{
    DoublyNode<T> *head;
    int size;

    CiruclarLinkedList();

    CiruclarLinkedList(T *array, int size);

    ~CiruclarLinkedList();

    void insertAtBeginning(T element);

    void insertAtEnd(T element);

    void deleteFirst();

    void deleteLast();

    void deleteItemAt(T index);

    bool find(T element);

    T *cloneArray();
};

template<typename T>
CiruclarLinkedList<T>::CiruclarLinkedList()
{
    this->head = nullptr;
    this->size = 0;
}

template<typename T>
CiruclarLinkedList<T>::CiruclarLinkedList(T *array, int size)
{

}

template<typename T>
CiruclarLinkedList<T>::~CiruclarLinkedList()
{
    DoublyNode<T> *next;
    while (this->head != nullptr)
    {
        next = this->head->nextAddress;
        delete this->head;
        this->head = next;
    }
}

template <typename T>
void CiruclarLinkedList<T>::insertAtBeginning(T element) {
    
}