#include <iostream>
#include <optional>
#include "../../entity/tenant.h"
#include "../../dao/tenantDao.h"
#include "../../dao/rentRequestDao.h"

using namespace std;

void manageTentReqPage()
{
    int selectedPage = 1;
    RentRequestDao *rentrequestDao = RentRequestDao::getInstance();
    int input;
    while (true)
    {
        rentrequestDao->sortUserIdByAscRQ();
        rentrequestDao->displayAllRentReqByPage(5, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Enter your choice: ";
        cout << "-------------------------------\n";
        cout << "1. Change page\n";
        cout << "2. Approve Tenant's Rent Request\n";
        cout << "3. Update Payment Of Tenant Rent Request\n";
        cout << "0. Back\n";
           
        int choice;
        cin >> choice;
        int id;
        string anyKey;
        RentRequest rentrequest;

        switch(choice)
        {
        case 1:
            cout << "Please type the page number to display the tenant's request\n";
            cin >> selectedPage;
            break;

        case 2:
            cout << "Enter Tenant ID to Approve Rent Request\n";
            cin >> id;
            if (id == 0)
            {
                return;
            }
            rentrequest.setid(id);
            if (rentrequestDao->manageTenancyProcess(rentrequest))
            {
                cout << "Tenancy process completed. Property is now rented by " << rentrequest.getTenant().getUsername() << "." << endl;
                cout << "Press any key to continue.\n";
                cin >> anyKey;
                return;
            }
                cout << "Press any key to continue.\n";
                cin >> anyKey;
            return;

        case 3:
            cout << "Enter Tenant ID to Update Payment Request\n";
            cin >> id;
            if (id == 0)
            {
                return;
            }
            rentrequest.setid(id);
            if (rentrequestDao->managePaymentProcess(rentrequest))
             {
                cout << "Payment has been confirmed." << endl;
            }
                cout << "Payment has not been made." << endl;
            return;

        default:
            cout << "Invalid option. Please try again.\n";

        case 0: return;
            break;
        }
    }
}

   

