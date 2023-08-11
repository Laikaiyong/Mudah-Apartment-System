#include <iostream>
#include "../admin/displayRecord.h"
#include "../admin/managerManagement.h"

using namespace std;

void adminHome(string name)
{
    while (true)
    {
        int choice = 0;
        cout << "\nWelcome Admin -" << name << endl;
        cout << "\nPlease select you action\n\n1 : Add Manager\n2 : Update Manager Status\n3 : Display Tenant\n4 : Display Property\nType 0 to sign out\n\nAction: ";
        cin >> choice;
        switch (choice)
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
            cout << "\nInvalid Option, please try again.\n";
            break;
        }
    }
}