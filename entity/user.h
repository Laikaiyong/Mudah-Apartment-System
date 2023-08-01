#pragma once
#include <iostream>

using namespace std;

class User
{
    string userId;
    string username;
    string password;
    int role;

public:
    User(string userId, string username, string password, int role) : userId(userId), username(username), password(password), role(role){};
};