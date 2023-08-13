#include <iostream>
#include <optional>
#include "../../entity/tenant.h"
#include "../../dao/tenantDao.h"

using namespace std;

// Search Tenant ID to show tenant's details function.
void searchTenantID()
{
    int id;
    cin >> id;
    TenantDao *tenantDao = TenantDao::getInstance();
    optional<Tenant> optionalTenant = tenantDao->getTenantById(id);

    if (optionalTenant.has_value())
    {
        Tenant tenant = optionalTenant.value();

        cout << "Tenant Details:" << endl;
        cout << "-------------------------------\n";
        cout << "Tenant ID: " << tenant.getUserId() << endl;
        cout << "Username: " << tenant.getUsername() << endl;
        cout << "Role: " << tenant.getRole() << endl;
        cout << "Status: " << tenant.getStatus() << endl;
        cout << "-------------------------------\n";
    }
    else
    {
        cout << "No Tenant with ID: " << id << " exists." << endl;
    }
}

void tenentsPage()
{
    int selectedPage = 1;
    TenantDao *tenantDao = TenantDao::getInstance();
    int input;
    while (true)
    {
        tenantDao->sortIdByAsc();
        tenantDao->displayAllTentsByPage(10, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Enter your choice: ";
        cout << "-------------------------------\n";
        cout << "1. Change page\n";
        cout << "2. Search Tenant By ID\n";
        cout << "3. Delete Tenant By ID\n";
        cout << "0. Back\n";

        int choice;
        cin >> choice;
        int id;
        string anyKey;

        switch (choice)
        {
        case 1:
            cout << "Please type the page number to display the tenants\n";
            cin >> selectedPage;
            break;

        case 2:
            cout << "Please enter tenant id\n";
            searchTenantID();
            cout << "Press any key to continue.\n";
            cin >> anyKey;
            break;

        case 3:
            cout << "To go back, press \"0\" and enter.\n";
            cout << "-------------------------------\n";
            cout << "Please enter the Tenant ID:\n";
            cin >> id;
            if (id == 0)
            {
                return;
            }
            if (tenantDao->deleteInactiveTenantById(id))
            {
                cout << "Successfully remove tenantid: " + id << " from database\n";
                cout << "Press any key to continue.\n";
                cin >> anyKey;
                return;
            }
            cout << "Tenant ID : \"" + id << "\" is not found from your inactivity list, please try again.\n";
            return;

        default:
            cout << "Invalid option. Please try again.\n";

        case 0:
            return;
            break;
        }
    }
}