#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/ArrayList.h"
#include "../entity/property.h"
#include "../entity/tenant.h"
#include "../entity/rentRequest.h"
#include "../dao/propertyDao.h"
#include "../searching/binarySearch.h"

using namespace std;

class RentRequestDao
{
    static RentRequestDao *instancePtr;

    ArrayList<RentRequest> *list;

    RentRequestDao()
    {
        list = new ArrayList<RentRequest>();
    }

public:
    static RentRequestDao *getInstance();

    void createRentRequest(Tenant &tenant, Property &property);

    optional<RentRequest> getRentRequestById(int id);

    ArrayList<RentRequest> *getAllRentRequestByTenantId(int userId);
};

RentRequestDao *RentRequestDao::instancePtr = nullptr;

RentRequestDao *RentRequestDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new RentRequestDao();
    }
    return instancePtr;
}

void RentRequestDao::createRentRequest(Tenant &tenant, Property &property)
{
    this->list->add(RentRequest(tenant, property));
}

optional<RentRequest> RentRequestDao::getRentRequestById(int id)
{
    RentRequest rentRequest(id);
    int index = binarySearch(this->list->getArray(), this->list->getSize(), rentRequest, [](RentRequest &r1, RentRequest &r2)
                             { return r1.getId() < r2.getId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->list->get(index);
}

ArrayList<RentRequest> *RentRequestDao::getAllRentRequestByTenantId(int userId)
{
    ArrayList<RentRequest> *rentRequestArray = new ArrayList<RentRequest>();
    for (int i = 0; i < this->list->getSize(); i++)
    {
        if (this->list->get(i).getTenant().getUserId() == userId)
        {
            rentRequestArray->add(this->list->get(i));
        }
    }
    return rentRequestArray;
}