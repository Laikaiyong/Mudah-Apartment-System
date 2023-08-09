#include <iostream>
#include <optional>
#include "../../dao/propertyDao.h"

using namespace std;

void selectProperty(optional<Property> &optionalProperty)
{
    PropertyDao *propertyDao = PropertyDao::getInstance();
    string id;
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID:" << endl;
        cin >> id;
        if (id == "e")
        {
            optionalProperty = nullopt;
            return;
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
}

void addFavouriteProperty(Property &property)
{
    // TODO: add into tenant favourite list
    cout << property << endl;
    cout << "Successfully added the selected property into your favourite property list.";
}

void displaySpecificPropertyPage()
{
    optional<Property> optionalProperty;
    selectProperty(optionalProperty);
    if (!optionalProperty.has_value())
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
            addFavouriteProperty(optionalProperty.value());
            return;
            break;
        case 2:
            selectProperty(optionalProperty);
            if (!optionalProperty.has_value())
            {
                return;
            }
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}