#pragma once
#include <iostream>

using namespace std;

class User
{
    int userId;
    string username;
    string password;
    int role;

public:
    User() {};

    User(int userId, string username, string password, int role) : userId(userId), username(username), password(password), role(role){};

    int getUserId() 
    {
        return userId;
    }

    void setUserId(int newUserId)
    {
        userId = newUserId;
    }

    string getUsername() 
    {
        return username;
    }

    void setUsername(string& newUsername)
    {
        username = newUsername;
    }

    string getPassword() 
    {
        return password;
    }

    void setPassword(string& newPassword)
    {
        password = newPassword;
    }

    int getRole() 
    {
        return role;
    }

    void setRole(int newRole)
    {
        role = newRole;
    }

    bool login(
        string inputUsername,
        string inputPassword
    )
    {
        return this->getUsername() == inputUsername && this->getPassword() == inputPassword;
    }
};