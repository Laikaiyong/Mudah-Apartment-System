#pragma once
#include <iostream>
#include <optional>
#include "../dao/propertyDao.h"
#include "../entity/Tenant.h"

using namespace std;

void deleteSpecificProperty(Tenant &tenant)
{
    string id;
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID:" << endl;
        cin >> id;
        if (id == "e")
        {
            return;
        }
        if (tenant.removeFavouritePropertyById(id))
        {
            cout << "Successfully remove property id: " + id + " from your favourite property list" << endl;
            return;
        }
        cout << "Property ID : \"" + id + "\" is not found from your favourite property list, please try again." << endl;
    }
}
