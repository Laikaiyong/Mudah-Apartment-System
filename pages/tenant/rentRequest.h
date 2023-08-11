#include <iostream>
#include "../../dao/tenantDao.h"
#include "../../functionality/tenantFunc.h"

using namespace std;

void rentRequestPage()
{
    int input;
    while (true)
    {
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Create rent request." << endl;
        cout << "Option 2: View all rent request." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            createRentRequest();
            break;
        case 2:
            displayFilterRentRequest();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}