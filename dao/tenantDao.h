#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/tenant.h"

using namespace std;

class TenantDao
{
    static TenantDao *instancePtr;
    static int idCounter;

    CiruclarLinkedList<Tenant> *list;

    TenantDao()
    {
        list = new CiruclarLinkedList<Tenant>();
    }

public:
    static TenantDao *getInstance();

    bool checkTenantUsernameTaken(string &username);

    void createTenant(string &username, string &password);

    optional<Tenant> getTenantById(int id);

    bool deleteTenantById(int id);

    // temporary function
    void printall()
    {
        this->list->showForward();
    }
};

TenantDao *TenantDao::instancePtr = nullptr;
int TenantDao::idCounter = 1;

TenantDao *TenantDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new TenantDao();
    }
    return instancePtr;
}

bool TenantDao::checkTenantUsernameTaken(string &username)
{
    Tenant tenant;
    tenant.setUsername(username);
    return this->list->customFind(tenant, [](Tenant &t1, Tenant &t2)
                                  { return t1.getUsername() == t2.getUsername(); });
}

void TenantDao::createTenant(string &username, string &password)
{
    Tenant tenant;
    tenant.setUserId(idCounter++);
    tenant.setUsername(username);
    tenant.setPassword(password);
    tenant.setUsername(username);
    tenant.setRole(1);
    tenant.setActive(true);
    list->add(tenant);
}

optional<Tenant> TenantDao::getTenantById(int id)
{
    Tenant tenant;
    tenant.setUserId(id);
    int index = this->list->customIndexOf(tenant, [](Tenant &t1, Tenant &t2)
                                          { return t1.getUserId() == t2.getUserId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->list->get(index);
}

bool TenantDao::deleteTenantById(int id)
{
    Tenant tenant;
    tenant.setUserId(id);
    int index = this->list->customIndexOf(tenant, [](Tenant &t1, Tenant &t2)
                                          { return t1.getUserId() == t2.getUserId(); });
    if (index == -1)
    {
        return false;
    }
    this->list->remove(index);
    return true;
}
