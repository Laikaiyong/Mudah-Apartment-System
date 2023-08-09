#pragma once
#include <iostream>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/manager.h"

using namespace std;

class ManagerDao
{
    static ManagerDao *instancePtr;

    CiruclarLinkedList<Manager> *list;

    ManagerDao()
    {
        list = new CiruclarLinkedList<Manager>();
    }

public:
    static ManagerDao *getInstance();

    Manager getManagerByUsername(string &username);

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

Manager ManagerDao::getManagerByUsername(string &username)
{
    Manager dummyManager;
    dummyManager.setUsername(username);

    for (int i = 0; i < list->getSize(); i++) 
    {
        Manager manager = list->get(i);
        if (manager.getUsername() == dummyManager.getUsername())
        {
            return manager;
        }
    }

    throw runtime_error("Manager not found");
}