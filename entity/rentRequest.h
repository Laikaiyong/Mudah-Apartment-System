#pragma once
#include <iostream>
#include "tenant.h"
#include "property.h"

using namespace std;

class RentRequest
{
    static int idCounter;

    int id;
    Tenant tenant;
    Property property;
    int approve;
    bool paid;

public:
    RentRequest(){};

    RentRequest(int id) : id(id) {};

    RentRequest(Tenant tenant, Property property) : id(getAndIncrementId()), tenant(tenant), property(property), approve(0), paid(false){};

    static int getAndIncrementId()
    {
        return idCounter++;
    }

    int getId()
    {
        return id;
    }

    Tenant &getTenant()
    {
        return tenant;
    }

    Property getProperty()
    {
        return property;
    }

    int getApprove()
    {
        return approve;
    }

    string getStringApprove()
    {
        switch (approve)
        {
        case 0:
            return "Pending";
        case 1:
            return "Approve";
        case 2:
            return "Reject";
        }
        return "";
    }

    void setApprove(int approve)
    {
        if (approve < 0 || approve >= 3)
        {
            cout << "Approve cannot be less than 0 or more than 2" << endl;
            return;
        }
        this->approve = approve;
    }

    bool isPaid()
    {
        return paid;
    }

    void setPaid(bool paid)
    {
        this->paid = paid;
    }
};
int RentRequest::idCounter = 1;