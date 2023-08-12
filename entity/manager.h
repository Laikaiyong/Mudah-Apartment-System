#include <iostream>
#include "user.h"

using namespace std;

class Manager : public User
{
    bool active;

public:
    Manager(){};

    Manager(int userId, string username, string password, int role, bool active) : User(userId, username, password, role),active(active) {};

     friend std::ostream &operator<<(std::ostream &os, Manager &manager)
    {
        // Code to output the object's data to the ostream
        os << "Manager Details:" << endl;
        os << "Manager ID: " << manager.getUserId() << endl;
        os << "Manager: " << manager.getUsername() << endl;
        os << "Role: " << manager.getRole() << endl;
        os << "Active: " << manager.active << endl;
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
};