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


void filterLoop(string type, string value)
{
    int filterStart = 1;
    string title;
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int input;
    while (true)
    {
        if (type == "rent")
        {
            if (value == "available")
            {
                propertyDao->filter([](Property &p1)
                { return p1.getRentStatus() == "Available"; });

                title = "\n-- Available Property --" ;
            }
            else if (value == "unavailable")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getRentStatus() == "Unavailable"; });

                title = "\n-- Unavailable Property --" ;
            }
            else if (value == "rented")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getRentStatus() == "Rented"; });
                title = "\n-- Rented Property --";
            }
            else
            {
                cout << "Invalid filter option, returning to action menu" << endl;
                return;
            }

        }
        else if (type == "furnished")
        {
            if (value == "-")
            {
                propertyDao->filter([](Property &p1)
                                    { return p1.getFurnished() == "-"; });
                    
                title = "\n-- Unknown Furnished Property --";
            }
            else if (value == "fully")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Fully Furnished"; });
                title = "\n-- 'Fully' Furnished Property --";
            }
            else if (value == "partial")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Partially Furnished"; });
                title = "\n-- 'Partially' Furnished Property --";
            }
            else if (value == "not")
            {
                propertyDao->filter([](Property &p1)
                    { return p1.getFurnished() == "Not Furnished"; });
                title = "\n-- 'Not' Furnished Property --";
            }
            else
            {
                cout << "Invalid filter option, returning to action menu" << endl;
                return;
            }
        }

        cout << title << endl;
        propertyDao->displayFilterPropsByPage(5, filterStart);

        cout << "Current Filtered Page: " + to_string(filterStart) << endl;
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
            cin >> filterStart;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

void displayProperty()
{
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int startPage = 1;
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
            else
            {
                filterLoop("rent", filterChoice);
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
            else 
            {
                filterLoop("furnished", filterChoice);
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