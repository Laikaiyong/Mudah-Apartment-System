#include <iostream>
#include "user.h"

using namespace std;

class Manager : public User
{
    string activeStatus;

public:
    Manager(string userId, string username, string password, int role, string activeStatus) : User(userId, username, password, role), activeStatus(activeStatus) {};
};