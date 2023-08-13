#include <iostream>
#include "../../dao/propertyDao.h"
#include "properties.h"
#include "favouriteProperties.h"
#include "rentingHistoryProperties.h"
#include "rentRequest.h"
#include "searchPropertiesName.h"

using namespace std;

void tenantHome()
{
    int input;
    while (true)
    {
        cout << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Tenant Dashboard" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: View all property." << endl;
        cout << "Option 2: Search property name." << endl;
        cout << "Option 3: View favourite property." << endl;
        cout << "Option 4: Place a rent request of favourite property." << endl;
        cout << "Option 5: View renting history." << endl;
        cout << "Option 0: Sign Out." << endl;
        cout << "--------------------------------------------------------" << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            propertiesPage();
            break;
        case 2:
            searchPropertiesNamePage();
            break;
        case 3:
            favouritePropertiesPage();
            break;
        case 4:
            rentRequestPage();
            break;
        case 5:
            rentingHistoryPropertiesPage();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}