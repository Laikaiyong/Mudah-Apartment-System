#include <iostream>
#include "signUp.h"
#include "login.h"

using namespace std;

void tenantPage()
{
    int choice;

    while (true)
    {
        cout << "\nPlease select an option." << endl;
        cout << "1 : Login." << endl;
        cout << "2 : Sign Up." << endl;
        cout << "0 : Go back." << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            return;
        case 1:
            tenantLoginPage();
            return;
        case 2:
            signUpPage();
            return;
        default:
            cout << "\nInvalid Option, please try again.\n";
            break;
        }
    }
}

void homePage()
{
    int roleChoice;

    while (true)
    {
        cout << "\nWelcome to APH renting system\n\nPlease select a role\n\n1 : Manager\n2 : Tenant\n3 : Admin\nTo exit, press \"0\"" << endl;
        cout << "Choice: ";
        cin >> roleChoice;

        if (roleChoice == 1)
        {
            managerLoginPage();
        }
        else if (roleChoice == 2)
        {
            tenantPage();
        }
        else if (roleChoice == 3)
        {
            adminLoginPage();
        }
        else if (roleChoice == 0)
        {
            break;
        }
        else
        {
            cout << "\nInvalid Option, please try again.\n"
                 << endl;
        }
    }
}
