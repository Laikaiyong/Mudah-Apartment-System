#include <iostream>
#include "../dao/tenantDao.h"
#include "../pages/admin/home.h"
#include "../pages/tenant/home.h"

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
    TenantDao *tenantDao = TenantDao::getInstance();

    int attempt = 1;
    for (attempt; attempt <= 3; attempt++)
    {
        string tenantUsername = "tenant"; // Hardcoded username
        string tenantPassword = "tenant_pwd"; // Hardcoded password
        string username, password;
        cout << "\n**Tenant Login**\nAttempt " << attempt << "\nUsername: ";
        cin >> username;
        
        cout << "Password: ";
        cin >> password;

        if (
            tenantUsername == username &&
            tenantPassword == password
        )
        {
            Tenant tenant = tenantDao->getTenantByUsername(username);
            tenantHome();
            return;
        }
        else
        {
            cout << "Invalid credentials, try again.\n" << endl;
        }
    }

    cout << "Maximum login attempts reached.\n" << endl;
}

void managerLoginPage()
{
    
}