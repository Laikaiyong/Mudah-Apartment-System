#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/tenant.h"
#include "../sorting/mergeSort.h"

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

        // Initialize Tenants
        this->createTenantByState("tenant", "secret", true);
        this->createTenantByState("tenant1", "secret", false);
    }

public:
    static TenantDao *getInstance();

    Tenant *getCurrentTenant();

    void setCurrentTenent(int id);

    bool checkTenantUsernameTaken(string &username);

    optional<Tenant> getTenantByUsername(string &username);

    void createTenant(string &username, string &password);

    void createTenantByState(string username, string password, bool activeState);

    optional<Tenant> getTenantById(int id);

    void updateTenantStatusById(int id, bool activeStatus);

    bool deleteInactiveTenantById(int id);

    Tenant *getAllTenant(int &size);
    
    void displayAllTentsByPage(int tentPerPage, int &startPage);

    void sortIdByAsc();

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

void TenantDao::createTenantByState(string username, string password, bool activeState)
{
    Tenant tenant;
    tenant.setUserId(User::getAndIncrementId());
    tenant.setUsername(username);
    tenant.setPassword(password);
    tenant.setRole(1);
    tenant.setActive(activeState);
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

bool TenantDao::deleteInactiveTenantById(int id)
{
    Tenant tenant;
    tenant.setUserId(id);
    int index = this->list->customIndexOf(tenant, [](Tenant &t1, Tenant &t2)
                                          { return t1.getUserId() == t2.getUserId(); });

    if (index == -1)
    {
        return false; // Tenant not found
    }

    Tenant &foundTenant = this->list->get(index);
    
    if (foundTenant.isActive())
    {
        return false; // Cannot delete active tenant
    }
    this->list->remove(index); // Delete inactive tenant
    return true;
}

Tenant *TenantDao::getAllTenant(int &size)
{
    size = this->list->getSize();
    return this->list->cloneArray();
}

void TenantDao::displayAllTentsByPage(int tentPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restTent = list->getSize() % tentPerPage;
    int totalPage = restTent > 0 ? (list->getSize() / tentPerPage) + 1 : list->getSize() / tentPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * tentPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restTent;
    }
    else
    {
        end = start + tentPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << list->get(i) << endl;
    }
}

void TenantDao::sortIdByAsc()
{
    mergeSort(list->cloneArray(), list->getSize(), [](Tenant &t1, Tenant &t2)
              { return t1.getUserId() < t2.getUserId(); });
    cout << "Finish sort Tenant ID by ascending order" << endl;
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
