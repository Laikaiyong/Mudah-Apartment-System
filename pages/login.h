#include <iostream>
#include "../entity/admin.h"
#include "../dao/tenantDao.h"
#include "../dao/managerDao.h"
#include "../pages/admin/home.h"
#include "../pages/tenant/home.h"
#include "../pages/manager/home.h"


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
        cout << "\nAdmin Login\nAttempt " << attempt << "\nUsername: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if (
            admin.login(username, password)
        )
        {
            adminHome(username);
            return;
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
        string username, password;
        cout << "\n**Tenant Login**\nAttempt " << attempt << "\nUsername: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        Tenant tenant = tenantDao->getTenantByUsername(username);

        if (tenant.login(username, password) && tenant.isActive())
        {
            cout << "Tenant login successful!" << endl;
            tenantDao->setCurrentTenent(tenant.getUserId());
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
    ManagerDao *managerDao = ManagerDao::getInstance();

    int attempt = 1;
    for (attempt; attempt <= 3; attempt++)
    {
        string username, password;
        cout << "\n**Manager Login**\nAttempt " << attempt << "\nUsername: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        try
        {
            Manager manager = managerDao->getManagerByUsername(username);

            if (!manager.isActive())
            {
                cout << "Manager is inactive. Cannot log in." << endl;
                return;
            }

            if (manager.login(username, password))
            {
                cout << "Manager login successful!" << endl;
                managerDao->setCurrentManager(manager.getUserId());
                managerHome();
                return;
            }
            else
            {
                cout << "Invalid credentials, try again.\n" << endl;
            }
        }
        catch (const runtime_error &)
        {
            cout << "Invalid username. Please try again.\n" << endl;
        }
    }

    cout << "Maximum login attempts reached.\n" << endl;
}



