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

    Manager *getCurrentManager();

    void setCurrentManager(int id);

    Manager getManagerByUsername(string &username);

    optional<Manager> getManagerById(int id);

    void createManager(string &username, string &password);

    bool updateManagerStatus(int id, bool newActiveStatus);
    // temporary function
    void printall()
    {
        this->list->showForward();
    }
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
    Manager manager;
    manager.setUserId(id);
    int index = this->list->customIndexOf(manager, [](Manager &m1, Manager &m2)
                                          { return m1.getUserId() == m2.getUserId(); });
    if (index == -1)
    {
        cout << "Warning, manager id " << id << "does not exist" << endl;
        return;
    }
    currentManager = &(this->list->get(index));
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
    // cout << "Searching for manager with ID: " << id << endl;

    Manager manager;
    manager.setUserId(id);
    int index = this->list->customIndexOf(manager, [](Manager &m1, Manager &m2)
                                          { return m1.getUserId() == m2.getUserId(); });

    // cout << "Index found: " << index << endl;

    if (index == -1)
    {
        // cout << "Manager not found." << endl;
        return nullopt;
    }
    // cout << "Manager found at index: " << index << endl;
    return this->list->get(index);
}

void ManagerDao::createManager(string &username, string &password)
{
    Manager manager;
    manager.setUserId(User::getAndIncrementId());
    manager.setUsername(username);
    manager.setPassword(password);
    manager.setRole(2);
    manager.setActive(true);
    list->add(manager);
}

bool ManagerDao::updateManagerStatus(int id, bool newActiveStatus) {
    optional<Manager> optionalManager = getManagerById(id);
    if (!optionalManager.has_value()) {
        cout << "Manager not found." << endl;
        return false; // Manager not found
    }

    Manager &manager = optionalManager.value();

    manager.setActive(newActiveStatus);
    cout << "Manager status updated successfully." << endl;

    return true;
}