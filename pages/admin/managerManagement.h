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
    ManagerDao *managerDao = ManagerDao::getInstance();

    while (true) {
        int choice;
        cout << "\nModify Manager Status:\n";
        cout << "1. Update manager status\n";
        cout << "0. Return\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            return; // User chose to return
        } else if (choice == 1) {
            int id;
            cout << "Enter the ID of the manager: ";
            cin >> id;

            bool newActiveStatus;
            string statusInput;
            cout << "Enter new status (active or inactive): ";
            cin >> statusInput;

            if (statusInput == "active") {
                newActiveStatus = true;
            } else if (statusInput == "inactive") {
                newActiveStatus = false;
            } else {
                cout << "Invalid status. Use 'active' or 'inactive'." << endl;
                continue;
            }

            managerDao->updateManagerStatusById(id, newActiveStatus);
            return;
        } else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }
}


