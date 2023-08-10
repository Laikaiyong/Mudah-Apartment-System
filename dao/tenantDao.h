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

    static Tenant *getCurrentTenant();

    static void setCurrentTenent(int id);

    bool checkTenantUsernameTaken(string &username);

    Tenant getTenantByUsername(string &username);

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
    TenantDao *tenantDao = TenantDao::getInstance();
    optional<Tenant> optionalTenant = tenantDao->getTenantById(id);
    if (optionalTenant.has_value())
    {
        currentTenant = &(optionalTenant.value());
    }
}

bool TenantDao::checkTenantUsernameTaken(string &username)
{
    Tenant tenant;
    tenant.setUsername(username);
    return this->list->customFind(tenant, [](Tenant &t1, Tenant &t2)
                                  { return t1.getUsername() == t2.getUsername(); });
}

Tenant TenantDao::getTenantByUsername(string &username)
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

    throw runtime_error("Tenant not found");
}

void TenantDao::createTenant(string &username, string &password)
{
    Tenant tenant;
    tenant.setUserId(User::getAndIncrementId());
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
