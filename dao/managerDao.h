#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/manager.h"

using namespace std;

class ManagerDao
{
    static ManagerDao *instancePtr;
    static Manager *currentManager;

    CiruclarLinkedList<Manager> *list;

    ManagerDao()
    {
        list = new CiruclarLinkedList<Manager>();
    }

public:
    static ManagerDao *getInstance();

    static Manager *getCurrentManager();

    static void setCurrentManager(int id);

    Manager getManagerByUsername(string &username);

    optional<Manager> getManagerById(int id);
};

ManagerDao *ManagerDao::instancePtr = nullptr;
Manager *ManagerDao::currentManager = nullptr;

ManagerDao *ManagerDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new ManagerDao();
    }
    return instancePtr;
}

Manager *ManagerDao::getCurrentManager()
{
    return currentManager;
}

void ManagerDao::setCurrentManager(int id)
{
    ManagerDao *managerDao = ManagerDao::getInstance();
    optional<Manager> optionalTenant = managerDao->getManagerById(id);
    if (optionalTenant.has_value())
    {
        currentManager = &(optionalTenant.value());
    }
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

optional<Manager> ManagerDao::getManagerById(int id)
{
    Manager manager;
    manager.setUserId(id);
    int index = this->list->customIndexOf(manager, [](Manager &m1, Manager &m2)
                                          { return m1.getUserId() == m2.getUserId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->list->get(index);
}