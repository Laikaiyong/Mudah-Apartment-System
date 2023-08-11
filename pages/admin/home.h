#include <iostream>
#include <string>
#include "../admin/displayRecord.h"
#include "../admin/managerManagement.h"

using namespace std;

void adminHome(string name)
{
    int input;
    while (true)
    {
        cout << "\nWelcome Admin - " << name << endl;
        cout << "Please enter your selected option:" << endl;
        cout << "1. Add new manager user." << endl;
        cout << "2. Update manager status." << endl;
        cout << "3. Display all registered tenants." << endl;
        cout << "4. Display property information." << endl;
        cout << "0. Sign out." << endl;
        cin >> input;

        switch (input)
        {
            case 0:
                return;
                break;
            case 1:
                addManager();
                return;
                break;
            case 2:
                modifyManagerStatus();
                return;
                break;
            case 3:
                displayTenant();
                return;
                break;
            case 4:
                displayProperty();
                return;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}