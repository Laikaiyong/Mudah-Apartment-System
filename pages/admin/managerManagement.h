#include <iostream>
#include "../../dao/managerDao.h"

using namespace std;

void addManager()
{
    ManagerDao *managerDao = ManagerDao::getInstance();
    string username = "";
    string pwd = "";
    cout << "Adding new manager, please fill in the information. Press \"0\" and enter to cancel sign up." << endl;
    while (true)
    {
        cout << "Username: ";
        cin >> username;

        if (username == "0")
        {
            return;
        }

        string confirmPwd = "";
        cout << "Password: ";
        cin >> pwd;
        if (pwd == "0")
        {
            return;
        }
        cout << "Confirm Password: ";
        cin >> confirmPwd;

        if (confirmPwd == "0")
        {
            return;
        }
        if (pwd == confirmPwd)
        {
            break;
        }
        cout << "Password is not same as comfirm password." << endl;
    }
    managerDao->createManager(username, pwd);
    cout << "Account created successfully" << endl;
    return;
}

void displayManager()
{
    ManagerDao *managerDao = ManagerDao::getInstance();
    managerDao->printall();
}

void modifyManagerStatus()
{

}