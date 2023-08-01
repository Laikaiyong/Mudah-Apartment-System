#include <iostream>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/manager.h"

using namespace std;

class ManagerDao
{
    static ManagerDao *instancePtr;

    CiruclarLinkedList<Manager> list;

    ManagerDao()
    {
    }

public:
    // deleting copy constructor
    ManagerDao(const ManagerDao &obj) = delete;

    static ManagerDao *getInstance();


};

ManagerDao *ManagerDao::instancePtr = nullptr;

ManagerDao *ManagerDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new ManagerDao();
    }
    return instancePtr;
}