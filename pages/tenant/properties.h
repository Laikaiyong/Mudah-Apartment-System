#include <iostream>
#include <algorithm>
#include <vector>
#include "../../dao/propertyDao.h"
#include "specificProperty.h"

using namespace std;

void sortPropertyPage(string sortOption)
{
    int selectedPage = 1;
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int input;
    while (true)
    {
        if (sortOption == "rent")
        {
            propertyDao->sortMonthlyRentByDesc();
        }
        else if (sortOption == "size")
        {
            propertyDao->sortSizeByDesc();
        }
        else if (sortOption == "location")
        {
            propertyDao->sortLocationByDesc();
        }

        propertyDao->displayAllPropsByPage(10, selectedPage);
        cout << "Current Sorted Page: " + to_string(selectedPage) << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Change page." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            cout << "Please type the page number to display the property" << endl;
            cin >> selectedPage;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

void propertiesPage()
{
    int selectedPage = 1;
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int input;
    string sort;
    vector<string> validSort {"rent", "size", "location"};
    while (true)
    {
        propertyDao->sortByDesc();
        propertyDao->displayAllPropsByPage(10, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Select specific property." << endl;
        cout << "Option 2: Change page." << endl;
        cout << "Option 3: Sort properties." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            specificPropertyPage();
            break;
        case 2:
            cout << "Please type the page number to display the property" << endl;
            cin >> selectedPage;
            break;
        case 3:
            cout << "\nPlease type the sort option in descending order\n(rent, size, location)\n\nChoice : ";
            cin >> sort;

            if (find(validSort.begin(), validSort.end(), sort) != validSort.end())
            {
                sortPropertyPage(sort);
            }
            else
            {
                cout << "Invalid sorting option. Returning to properties home" << endl;
            }
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}
