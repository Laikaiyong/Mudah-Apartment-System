#include <iostream>
#include "user.h"

using namespace std;

class Manager : public User
{
    string activeStatus;

public:
    Manager(){};

    Manager(int userId, string username, string password, int role, string activeStatus) : User(userId, username, password, role), activeStatus(activeStatus) {};

    void setActiveStatus(string newActiveStatus)
    {
        activeStatus = newActiveStatus;
    }

    string getActiveStatus()
    {
        return this->activeStatus;
    }

    friend std::ostream &operator<<(std::ostream &os, Manager &manager)
    {
        // Code to output the object's data to the ostream
        os << "Manager Details:" << endl;
        os << "User ID: " << manager.getUserId() << endl;
        os << "Username: " << manager.getUsername() << endl;
        os << "Role: " << manager.getRole() << endl;
        os << "Active: " << manager.getActiveStatus() << endl;
        return os;
    }
};