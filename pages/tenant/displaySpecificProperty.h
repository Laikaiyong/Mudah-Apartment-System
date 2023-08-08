#include <iostream>
#include <optional>
#include "../../dao/propertyDao.h"

using namespace std;

bool selectProperty()
{
    PropertyDao *propertyDao = PropertyDao::getInstance();
    string id;
    optional<Property> optionalProperty;
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID:" << endl;
        cin >> id;
        if (id == "e")
        {
            return true;
        }
        optionalProperty = propertyDao->getById(id);
        if (optionalProperty.has_value())
        {
            break;
        }
        cout << "Property ID : \"" + id + "\" is not found, please try again." << endl;
    }
    cout << endl;
    cout << optionalProperty.value() << endl;
    return false;
}

void displaySpecificPropertyPage()
{
    if (selectProperty())
    {
        return;
    }
    int input;
    while (true)
    {
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Add as favourite property." << endl;
        cout << "Option 2: Select another specific property." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            cout << "Add as favourite" << endl;
            break;
        case 2:
            if (selectProperty())
            {
                return;
            }
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}