#include <iostream>
#include "../dao/tenantDao.h"
#include "../entity/admin.h"
#include "../pages/admin/home.h"

using namespace std;

void adminLoginPage()
{
    Admin admin = Admin(
        1,
        "admin",
        "secret",
        3
    );
    int attempt = 1;
    for (attempt; attempt <= 3; attempt++)
    {
        string username, password;
        cout << "\n**Admin Login**\nAttempt " << attempt << "\nUsername: ";
        cin >> username;
        
        cout << "Password: ";
        cin >> password;

        if (
            admin.login(username, password)
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