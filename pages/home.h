#include <iostream>
#include "signUp.h"
#include "login.h"

using namespace std;

void homePage()
{
    int roleChoice;
    cout << "Welcome to APH renting system\n\nPlease select a role\n\n1 : Manager\n2 : Tenant\n3 : Admin\n\n" << endl;
    while (true)
    {
        cout << "Choice: ";
        cin >> roleChoice;

        if (roleChoice == 1)
        {
           managerLoginPage();
        }
        else if (roleChoice == 2)
        {
            tenantLoginPage();
        }
        else if (roleChoice == 3)
        {
            adminLoginPage();
        }
        else
        {
            cout << "\nInvalid Option, please try again.\n" << endl;
            return;
        }
    }
}