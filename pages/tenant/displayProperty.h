#include <iostream>
#include "../../dao/propertyDao.h"
#include "displaySpecificProperty.h"

using namespace std;

void displayPropertyPage()
{
    int selectedPage = 1;
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int input;
    while (true)
    {
        propertyDao->sortByDesc();
        propertyDao->displayAllPropsByPage(10, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Select specific property." << endl;
        cout << "Option 2: Change page." << endl;
        cout << "Option 0: Back." << endl;
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
            cout << "Please type the page number to display the property" << endl;
            cin >> selectedPage;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}