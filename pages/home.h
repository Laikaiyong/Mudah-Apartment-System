#include <iostream>
#include "pages/login.h"
#include "pages/signUp.h"

using namespace std;

void homePage()
{
    int roleChoice;
    cout << "Welcome to APH renting system\n\nPlease select a role\n\n1 : Manager\n2 : Tenant\n3 : Admin\n\n" << endl;
    while (true)
    {
        cout << "Choice: " << endl;
        cin >> roleChoice;

        if (roleChoice == 1)
        {
            login
        }
        if (!TenantDao->checkTenantUsernameTaken(username))
        {
            break;
        }
        cout << "Username has been taken." << endl;
    }
}