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
        cout << "5. Display manager." << endl;
        cout << "0. Sign out." << endl;
        cout << "Action: ";
        cin >> input;

        if (input == 0)
        {
            return;
        }
        else if (input == 1)
        {
            addManager();
        }
        else if (input == 2)
        {
            modifyManagerStatus();
        }
        else if (input == 3)
        {
            displayTenant();
        }
        else if (input == 4)
        {
            displayProperty();
        }
        else if (input == 5)
        {
            displayManager();
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}