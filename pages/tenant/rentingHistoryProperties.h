#include <iostream>
#include "../../entity/Tenant.h"
#include "../../dao/tenantDao.h"

using namespace std;

void rentingHistoryPropertiesPage()
{
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    int selectedPage = 1;
    int input;
    while (true)
    {
        if (tenant->getRentHistoryPropertyList()->getSize() == 0)
        {
            cout << "Your Rent History of Property is empty" << endl;
            return;
        }
        tenant->displayRentHistoryPropertyList(10, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
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