#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/tenant.h"

using namespace std;

class TenantDao
{
    static TenantDao *instancePtr;
    static Tenant *currentTenant;

    CiruclarLinkedList<Tenant> *list;

    TenantDao()
    {
        list = new CiruclarLinkedList<Tenant>();
    }

public:
    static TenantDao *getInstance();

    Tenant *getCurrentTenant();

    void setCurrentTenent(int id);

    bool checkTenantUsernameTaken(string &username);

    optional<Tenant> getTenantByUsername(string &username);

    void createTenant(string &username, string &password);

    optional<Tenant> getTenantById(int id);

    void updateTenantStatusById(int id, bool activeStatus);

    bool deleteTenantById(int id);

    Tenant *getAllTenant(int &size);

    // temporary function
    void printall()
    {
        this->list->showForward();
    }
};

TenantDao *TenantDao::instancePtr = nullptr;
Tenant *TenantDao::currentTenant = nullptr;

TenantDao *TenantDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new TenantDao();
    }
    return instancePtr;
}

Tenant *TenantDao::getCurrentTenant()
{
    return currentTenant;
}

void TenantDao::setCurrentTenent(int id)
{
    Tenant tenant;
    tenant.setUserId(id);
    int index = this->list->customIndexOf(tenant, [](Tenant &t1, Tenant &t2)
                                          { return t1.getUserId() == t2.getUserId(); });
    if (index == -1)
    {
        cout << "Warning, tenant id " << id << "does not exist" << endl;
        return;
    }
    currentTenant = &(this->list->get(index));
}

bool TenantDao::checkTenantUsernameTaken(string &username)
{
    Tenant tenant;
    tenant.setUsername(username);
    return this->list->customFind(tenant, [](Tenant &t1, Tenant &t2)
                                  { return t1.getUsername() == t2.getUsername(); });
}

optional<Tenant> TenantDao::getTenantByUsername(string &username)
{
    Tenant dummyTenant;
    dummyTenant.setUsername(username);

    for (int i = 0; i < list->getSize(); i++) 
    {
        Tenant tenant = list->get(i);
        if (tenant.getUsername() == dummyTenant.getUsername())
        {
            return tenant;
        }
    }

    return nullopt;
}

void TenantDao::createTenant(string &username, string &password)
{
    Tenant tenant;
    tenant.setUserId(User::getAndIncrementId());
    tenant.setUsername(username);
    tenant.setPassword(password);
    tenant.setRole(1);
    tenant.setActive(true);
    tenant.initFavouritePropertyList();
    tenant.initRentHistoryPropertyList();
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

void TenantDao::updateTenantStatusById(int id, bool activeStatus)
{
    Tenant tempTenant;
    tempTenant.setUserId(id);
    int index = this->list->customIndexOf(tempTenant, [](Tenant &t1, Tenant &t2)
                                          { return t1.getUserId() == t2.getUserId(); });
    if (index == -1)
    {
        cout << "Update status failed, Tenant ID:" << tempTenant.getUserId() << " not found.";
        return;
    }
    Tenant &tenant = this->list->get(index);
    tenant.setActive(activeStatus);
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

Tenant *TenantDao::getAllTenant(int &size)
{
    size = this->list->getSize();
    return this->list->cloneArray();
}