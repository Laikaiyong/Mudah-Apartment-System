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
    CiruclarLinkedList<Tenant> *filterList;

    TenantDao()
    {
        list = new CiruclarLinkedList<Tenant>();
        this->createTenantByState("tenant", "secret", true);
        this->createTenantByState("tenant1", "secret", false);
    }

public:
    static TenantDao *getInstance();

    Tenant *getCurrentTenant();

    void setCurrentTenent(int id);

    bool checkTenantUsernameTaken(string &username);

    Tenant getTenantByUsername(string &username);

    void createTenant(string &username, string &password);

    void createTenantByState(string username, string password, bool activeState);

    optional<Tenant> getTenantById(int id);

    bool deleteTenantById(int id);

    template <typename Filter>
    void filter(Filter compare);

    void displayAllPropsByPage();

    void displayFilterPropsByPage();


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
    tenant.setRole(1);
    tenant.setActive(true);
    tenant.initFavouritePropertyList();
    tenant.initRentHistoryPropertyList();
    list->add(tenant);
}

void TenantDao::createTenantByState(string username, string password, bool activeState)
{
    Tenant tenant;
    tenant.setUserId(User::getAndIncrementId());
    tenant.setUsername(username);
    tenant.setPassword(password);
    tenant.setRole(1);
    tenant.setActive(activeState);
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

void TenantDao::displayAllPropsByPage()
{
    for (int i = 0; i < list->getSize(); i++)
    {
        cout << list->get(i) << endl;
    }
}

void TenantDao::displayFilterPropsByPage()
{
    if (filterList->getSize() > 0)
    {
        for (int i = 0; i < filterList->getSize(); i++)
        {
            cout << filterList->get(i) << endl;
        }
    }
}

template <typename Filter>
void TenantDao::filter(Filter compare)
{
    filterList = new CiruclarLinkedList<Tenant>();
    int totalMatch = 0;
    // increment the totalMatch if match filter
    if(list->getSize() != 0)
    {
        for (int i = 0; i < list->getSize(); i++)
        {
            if (compare(list->get(i)))
            {
                totalMatch++;
            }
        }
        if (totalMatch == 0)
        {
            filterList = new CiruclarLinkedList<Tenant>();
        }
        // create an array to store all the filter data
        Tenant *newArray = new Tenant[totalMatch];
        int j = 0;
        // store data if filter match
        for (int i = 0; i < list->getSize(); i++)
        {
            if (compare(list->get(i)))
            {
                newArray[j++] = list->get(i);
            }
        }
        filterList = new CiruclarLinkedList<Tenant>(newArray, totalMatch);
        cout << "Successfully filter tenant" << endl;
    }
    else
    {
        cout << "No records found, filter unavailable";
    } 
}
