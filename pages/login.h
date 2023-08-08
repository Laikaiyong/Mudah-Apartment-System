#include <iostream>
#include "../dao/tenantDao.h"
#include "../pages/admin/home.h"

using namespace std;

void adminLoginPage()
{
    int attempt = 1;
    for (attempt; attempt <= 3; attempt++)
    {
        string adminUsername = "admin";
        string adminPassword = "pwd";
        string username, password;
        cout << "\n**Admin Login**\nAttempt " << attempt << "\nUsername: ";
        cin >> username;
        
        cout << "Password: ";
        cin >> password;

        if (
            adminUsername == username &&
            adminPassword == password
        )
        {
            adminHome();
            break;
        }
        else
        {
            cout << "Invalid credentials, try again.\n" << endl;
        }
    }
}

void tenantLoginPage()
{
    
}

void managerLoginPage()
{
    
}