#include <iostream>
#include "user.h"

using namespace std;

class Admin : public User
{

public:
    Admin(string userId, string username, string password, int role) : User(userId, username, password, role) {};
};