#include <iostream>
#include "../../dao/propertyDao.h"
#include "displaySpecificProperty.h"

using namespace std;

void displayPropertyPage()
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
            displaySpecificPropertyPage();
            break;
        case 2:
            cout << "View favourite property." << endl;
            break;
        case 3:
            cout << "Place a rent request of favourite property." << endl;
            break;
        case 4:
            cout << "View renting history." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}