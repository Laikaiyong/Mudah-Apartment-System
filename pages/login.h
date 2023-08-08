#include <iostream>
#include "../dao/tenantDao.h"
#include "../dao/managerDao.h"

using namespace std;

void logInPage()
{
    TenantDao *TenantDao = TenantDao::getInstance();
    string username = "";
    string pwd = "";
    cout << "Login as tenant, please fill in the information. Press \"0\" and enter to cancel sign up." << endl;
    while (true)
    {
        cout << "Username: " << endl;
        cin >> username;

        if (username == "0")
        {
            return;
        }
        if (!TenantDao->checkTenantUsernameTaken(username))
        {
            break;
        }
        cout << "Username has been taken." << endl;
    }

    while (true)
    {
        string comfirmPwd = "";
        cout << "Password: " << endl;
        cin >> pwd;
        if (pwd == "0")
        {
            return;
        }
        cout << "Comfirm Password: " << endl;
        cin >> comfirmPwd;

        if (comfirmPwd == "0")
        {
            return;
        }
        if (pwd == comfirmPwd)
        {
            break;
        }
        cout << "Password is not same as comfirm password." << endl;
    }
    TenantDao->createTenant(username, pwd);
    cout << "Account created successfully" << endl;
}