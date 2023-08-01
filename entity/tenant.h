#include <iostream>
#include "user.h"

using namespace std;

class Tenant : public User
{
    bool active;

public:
    Tenant(string userId, string username, string password, int role, bool active) : User(userId, username, password, role), active(active) {};
};