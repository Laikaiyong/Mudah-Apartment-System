#pragma once
#include <iostream>
#include <optional>
#include "../dao/propertyDao.h"
#include "../dao/tenantDao.h"
#include "../entity/Tenant.h"

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
        cout << "Press any key to continue.\n";
        cin;
    }
    cout << endl;
    cout << optionalProperty.value() << endl;
}

void addFavouriteProperty(Property &property)
{
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    tenant->addFavourtiteProperty(property);
    cout << "Successfully added the selected property into your favourite property list.\n";
    cout << "Press any key to continue.\n";
    cin;
}

void deleteSpecificFavouriteProperty(Tenant &tenant)
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
            cout << "Press any key to continue.\n";
            cin;
            return;
        }
        cout << "Property ID : \"" + id + "\" is not found from your favourite property list, please try again." << endl;
    }
}
