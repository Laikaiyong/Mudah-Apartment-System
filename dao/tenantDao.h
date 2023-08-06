#pragma once
#include <iostream>
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

    void printall() {
        Tenant tenant;
        for (int i = 0; i < list->getSize(); i++) 
        {
            tenant = list->get(i);
        }
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
    return list->customFind(tenant, [](Tenant &t1, Tenant &t2)
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
