#include <iostream>
#include "../../entity/Tenant.h"
#include "../../dao/tenantDao.h"
#include "../../functionality/tenantFunc.h"

using namespace std;

void favouritePropertiesPage()
{
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    int selectedPage = 1;
    int input;
    while (true)
    {
        if (tenant->getFavouritePropertyList()->getSize() == 0)
        {
            cout << "Your Favourite Property is empty" << endl;
            return;
        }
        tenant->displayFavouritePropertyList(10, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Remove specific favourite property." << endl;
        cout << "Option 2: Change page." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            deleteSpecificFavouriteProperty(*tenant);
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