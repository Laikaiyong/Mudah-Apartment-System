/**
 * FILENAME: DoublyLinkedList.h
 */

#include <iostream>
using namespace std;

template <typename T>
struct DoublyNode
{
    T data;
    DoublyNode<T> *prev;
    DoublyNode<T> *next;

    DoublyNode(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

    DoublyNode(T data, DoublyNode<T> *prev)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = prev;
    }

    DoublyNode(T data, DoublyNode<T> *next, DoublyNode<T> *prev)
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

    T get(int index);

    void add(T element);

    void add(T element, int index);

    // T remove(int index);

    // bool remove(T object);

    // bool find(T element);

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
        DoublyNode<T> *current = this->head->prev;
        cout << "--- DISPLAY LINKED LIST [FORWARD] = " << size << " elements ---" << endl;
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
        throw std::invalid_argument("Invalid array or size");
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
T CiruclarLinkedList<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    DoublyNode<T> *current = this->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
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
        throw std::out_of_range("Index out of bounds");
    }
    DoublyNode<T> *current;
    int mid = this->size / 2;

    if (index <= mid)
    {
        current = this->head;
        for (int i = 0; i < size; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = this->head->prev;
        for (int i = size; i > 0; i--)
        {
            current = current->prev;
        }
    }
    DoublyNode<T> *newNode = new DoublyNode<T>(element, current, current->prev);
    current->prev->next = newNode;
    current->prev = newNode;
    this->size++;
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