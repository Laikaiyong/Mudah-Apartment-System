#include <iostream>
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
    Tenant() : favourtitePropertyList(new CiruclarLinkedList<Property>()), rentHistoryPropertyList(new ArrayList<Property>()){};

    Tenant(int userId, string username, string password, int role, bool active) : User(userId, username, password, role), active(active), favourtitePropertyList(new CiruclarLinkedList<Property>()), rentHistoryPropertyList(new ArrayList<Property>()){};

    ~Tenant()
    {
        if (favourtitePropertyList != nullptr)
        {
            delete favourtitePropertyList;
            favourtitePropertyList = nullptr;
        }
        if (favourtitePropertyList != nullptr)
        {
            delete rentHistoryPropertyList;
            rentHistoryPropertyList = nullptr;
        }
    }

    bool isActive()
    {
        return active;
    }

    void setActive(bool newActive)
    {
        active = newActive;
    }

    void displayFavouritePropertyList(int propPerPage, int startPage);

    CiruclarLinkedList<Property> *getFavouritePropertyList();

    void addFavourtiteProperty(Property property);

    bool removeFavouritePropertyById(string id);

    void displayRentHistoryPropertyList(int propPerPage, int startPage);

    void addRentHistoryPropertyList(Property property);
};

void Tenant::displayFavouritePropertyList(int propPerPage, int startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    if (favourtitePropertyList->getSize() == 0)
    {
        cout << "Your Favourite Property is empty" << endl;
        return;
    }
    int restProp = favourtitePropertyList->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (favourtitePropertyList->getSize() / propPerPage) + 1 : favourtitePropertyList->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) << endl;
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

CiruclarLinkedList<Property> *Tenant::getFavouritePropertyList()
{
    return this->favourtitePropertyList;
}

void Tenant::addFavourtiteProperty(Property property)
{
    this->favourtitePropertyList->add(property);
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

void Tenant::displayRentHistoryPropertyList(int propPerPage, int startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    if (favourtitePropertyList->getSize() == 0)
    {
        cout << "Your Rent History of Property is empty" << endl;
        return;
    }
    int restProp = rentHistoryPropertyList->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (rentHistoryPropertyList->getSize() / propPerPage) + 1 : rentHistoryPropertyList->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) << endl;
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

void Tenant::addRentHistoryPropertyList(Property property)
{
    this->rentHistoryPropertyList->add(property);
}
