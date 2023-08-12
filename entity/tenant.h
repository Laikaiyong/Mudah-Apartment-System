#pragma once
#include <iostream>
#include <optional>
#include "user.h"
#include "property.h"
#include "../data-structure/ArrayList.h"
#include "../data-structure/CircularLinkedList.h"

using namespace std;

class Tenant : public User
{
    CiruclarLinkedList<Property> *favourtitePropertyList;
    ArrayList<Property> *rentHistoryPropertyList;
    bool active;

public:
    Tenant() : favourtitePropertyList(nullptr), rentHistoryPropertyList(nullptr){};

    Tenant(int userId, string username, string password, int role, bool active) : User(userId, username, password, role), active(active), favourtitePropertyList(nullptr), rentHistoryPropertyList(nullptr){};

    ~Tenant() {}

    friend std::ostream &operator<<(std::ostream &os, Tenant &tenant)
    {
        // Code to output the object's data to the ostream
        os << "Tenant Details:" << endl;
        os << "User ID: " << tenant.getUserId() << endl;
        os << "Username: " << tenant.getUsername() << endl;
        os << "Role: " << tenant.getRole() << endl;
        os << "Status: " << tenant.getStatus() << endl;
        return os;
    }

    bool isActive()
    {
        return active;
    }

    void setActive(bool newActive)
    {
        active = newActive;
    }

    string getStatus()
    {
        return active ? "Active" : "Inactive";
    }

    CiruclarLinkedList<Property> *getFavouritePropertyList()
    {
        return this->favourtitePropertyList;
    }

    void initFavouritePropertyList()
    {
        if (this->favourtitePropertyList == nullptr)
            this->favourtitePropertyList = new CiruclarLinkedList<Property>();
    }

    ArrayList<Property> *getRentHistoryPropertyList()
    {
        return this->rentHistoryPropertyList;
    }

    void initRentHistoryPropertyList()
    {
        if (this->rentHistoryPropertyList == nullptr)
            this->rentHistoryPropertyList = new ArrayList<Property>();
    }

    void displayFavouritePropertyList(int propPerPage, int &startPage);

    bool checkFavourtitePropertyExist(Property &property);

    void addFavourtiteProperty(Property &property);

    optional<Property> getFavourtitePropertyById(string id);

    bool removeFavouritePropertyById(string id);

    void displayRentHistoryPropertyList(int propPerPage, int &startPage);

    void addRentHistoryPropertyList(Property &property);
};

void Tenant::displayFavouritePropertyList(int propPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = favourtitePropertyList->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (favourtitePropertyList->getSize() / propPerPage) + 1 : favourtitePropertyList->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * propPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restProp;
    }
    else
    {
        end = start + propPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << favourtitePropertyList->get(i) << endl;
    }
}

bool Tenant::checkFavourtitePropertyExist(Property &property)
{
    return this->favourtitePropertyList->customFind(property, [](Property &p1, Property &p2)
                                          { return p1.getAdsId() == p2.getAdsId(); });
}

void Tenant::addFavourtiteProperty(Property &property)
{
    this->favourtitePropertyList->add(property);
}

optional<Property> Tenant::getFavourtitePropertyById(string id)
{
    Property property;
    property.setAdsId(id);
    int index = this->favourtitePropertyList->customIndexOf(property, [](Property &p1, Property &p2)
                                          { return p1.getAdsId() == p2.getAdsId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->favourtitePropertyList->get(index);
}

bool Tenant::removeFavouritePropertyById(string id)
{
    Property property;
    property.setAdsId(id);
    int index = this->favourtitePropertyList->customIndexOf(property, [](Property &p1, Property &p2)
                                                            { return p1.getAdsId() == p2.getAdsId(); });
    if (index == -1)
    {
        return false;
    }
    this->favourtitePropertyList->remove(index);
    return true;
}

void Tenant::displayRentHistoryPropertyList(int propPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = rentHistoryPropertyList->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (rentHistoryPropertyList->getSize() / propPerPage) + 1 : rentHistoryPropertyList->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * propPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restProp;
    }
    else
    {
        end = start + propPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << rentHistoryPropertyList->get(i) << endl;
    }
}

void Tenant::addRentHistoryPropertyList(Property &property)
{
    this->rentHistoryPropertyList->add(property);
}
