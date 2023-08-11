#include <iostream>
#include "../../dao/propertyDao.h"
#include "properties.h"
#include "favouriteProperties.h"
#include "rentingHistoryProperties.h"
#include "rentRequest.h"

using namespace std;

void tenantHome()
{
    int input;
    while (true)
    {
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: View all property." << endl;
        cout << "Option 2: View favourite property." << endl;
        cout << "Option 3: Place a rent request of favourite property." << endl;
        cout << "Option 4: View renting history." << endl;
        cout << "Option 0: Sign Out." << endl;
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
            favouritePropertiesPage();
            break;
        case 3:
            rentRequestPage();
            break;
        case 4:
            rentingHistoryPropertiesPage();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}