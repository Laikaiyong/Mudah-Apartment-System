#include <iostream>
#include "user.h"
#include "property.h"
#include "../data-structure/ArrayList.h"
#include "../data-structure/CircularLinkedList.h"

using namespace std;

class Tenant : public User
{
    CiruclarLinkedList<Property> *favourtitePropertyList;
    ArrayList<Property> *rentingHistoryPropertyList;
    bool active;

public:
    Tenant() : favourtitePropertyList(new CiruclarLinkedList<Property>()), rentingHistoryPropertyList(new ArrayList<Property>()){};

    Tenant(int userId, string username, string password, int role, bool active) : User(userId, username, password, role), active(active), favourtitePropertyList(new CiruclarLinkedList<Property>()), rentingHistoryPropertyList(new ArrayList<Property>()){};

    ~Tenant()
    {
        if (favourtitePropertyList != nullptr)
        {
            delete favourtitePropertyList;
            favourtitePropertyList = nullptr;
        }
        if (favourtitePropertyList != nullptr)
        {
            delete rentingHistoryPropertyList;
            rentingHistoryPropertyList = nullptr;
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
};