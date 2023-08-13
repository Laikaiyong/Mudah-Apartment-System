#ifndef SPECIFICPROPERTYPAGE_H
#define SPECIFICPROPERTYPAGE_H
#include <iostream>
#include <optional>
#include "../../entity/property.h"
#include "../../functionality/tenantFunc.h"

using namespace std;

void specificPropertyPage()
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
#endif