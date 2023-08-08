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

    void *displayFavouritePropertyList();

    CiruclarLinkedList<Property> *getFavouritePropertyList();

    void addFavourtiteProperty(Property property);

    bool removeFavouriteProperty(Property property);

    void *displayRentHistoryPropertyList();

    void addRentHistoryPropertyList(Property property);
};

void *Tenant::displayFavouritePropertyList()
{
    cout << endl;
    for (int i = 0; i < this->favourtitePropertyList->getSize(); i++)
    {
        this->favourtitePropertyList->showForward();
    };
}

CiruclarLinkedList<Property> *Tenant::getFavouritePropertyList()
{
    return this->favourtitePropertyList;
}

void Tenant::addFavourtiteProperty(Property property)
{
    this->favourtitePropertyList->add(property);
}

bool Tenant::removeFavouriteProperty(Property property)
{
    return this->favourtitePropertyList->remove(property);
}

void *Tenant::displayRentHistoryPropertyList()
{
    cout << endl;
    for (int i = 0; i < this->rentHistoryPropertyList->getSize(); i++)
    {
        cout << this->rentHistoryPropertyList->get(i) << endl;;
    };
}

void Tenant::addRentHistoryPropertyList(Property property)
{
    this->rentHistoryPropertyList->add(property);
}
