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
    int startPage = 1;
    int filterStart = 1;
    cout << "-- All Property --\n\nPage " << startPage << endl;
    propertyDao->displayAllPropsByPage(5, startPage);

    while (true)
    {
        int nextOption;
        cout << "\nWhat's your next action?\n\n1 : Continue Scrolling\n2 : Filter Rent Status\n3 : Filter Furnished State\nSelect \"0\" to return to action menu\n\nAction: ";
        cin >> nextOption;

        // Continue scrolling
        if (nextOption == 1)
        {
            while (true)
            {
                startPage += 1;
                cout << "-- All Property --\n\nPage " << startPage << endl;
                propertyDao->displayAllPropsByPage(5, startPage);

                int scrollOption;
                cout << "\nContinue Scroll?\n\n1 : Continue\n*Enter other input to stop\n\nScroll Option: ";
                cin >>  scrollOption;

                if (scrollOption != 1)
                {
                    return;
                }
            }
        }
        // Filter Rent Status (Available, Unavailable)
        else if(nextOption == 2)
        {
            string filterChoice = "";
            cout << "Filter Availability? (available, unavailable, rented)\nSelect \"0\" to return to action menu\nFilter Choice: ";
            cin >> filterChoice;

            if (filterChoice == "0")
            {
                return;
            }
            else if (filterChoice == "available")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getRentStatus() == "Available"; });
                
                cout << "\n-- Available Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else if (filterChoice == "unavailable")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getRentStatus() == "Unavailable"; });
                cout << "\n-- Unavailable Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else if (filterChoice == "rented")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getRentStatus() == "Rented"; });
                cout << "\n-- Rented Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else
            {
                cout << "Invalid filter option, returning to action menu" << endl;
                return;
            }
        }
        //  Filter Furnished Status (-, Fully Furnished, Partially Furnished, Not Furnished)
        else if(nextOption == 3)
        {
            string filterChoice = "";
            cout << "Filter Furnished State? (-, fully, partial, not)\nSelect \"0\" to return to action menu\nFilter Choice: ";
            cin >> filterChoice;

            if (filterChoice == "0")
            {
                return;
            }
            else if (filterChoice == "-")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "-"; });
                
                cout << "\n-- '-' Furnished Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else if (filterChoice == "fully")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Fully Furnished"; });
                cout << "\n-- 'Fully' Furnished Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else if (filterChoice == "partial")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Partially Furnished"; });
                cout << "\n-- 'Partially' Furnished Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else if (filterChoice == "not")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Not Furnished"; });
                cout << "\n-- 'Not' Furnished Property --" << endl;
                propertyDao->displayFilterPropsByPage(5, filterStart);
                return;
            }
            else
            {
                cout << "Invalid filter option, returning to action menu" << endl;
            }
        }
        // Return to main functionality
        else if(nextOption == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid option, returning back to action menu" << endl;
            return;
        }
    }
}