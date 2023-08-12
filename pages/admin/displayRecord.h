#include <iostream>
#include "../../dao/tenantDao.h"
#include "../../dao/propertyDao.h"

using namespace std;

void displayTenant()
{
    TenantDao *tenantDao = TenantDao::getInstance();
    cout << "-- All Tenant --" << endl;
    tenantDao->displayAllPropsByPage();

    string filterChoice = "";
    cout << "Filter tenant? (active / inactive)\nSelect \"0\" to return to action menu\nFilter Choice: ";
    cin >> filterChoice;

    if (filterChoice == "0")
    {
        return;
    }
    else if (filterChoice == "active")
    {
        tenantDao->filter([](Tenant &t1)
              { return t1.isActive() == 1; });
        
        cout << "\n-- Active Tenant --" << endl;
        tenantDao->displayFilterPropsByPage();
        return;
    }
    else if (filterChoice == "inactive")
    {
        tenantDao->filter([](Tenant &t1)
              { return t1.isActive() == 0; });

        cout << "\n-- Inactive Tenant --" << endl;
        tenantDao->displayFilterPropsByPage();
        return;
    }
    else
    {
        cout << "Invalid filter option, returning to action menu" << endl;
    }
}

void displayProperty()
{
    PropertyDao *propertyDao = PropertyDao::getInstance();  
}