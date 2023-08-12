#include <iostream>
#include "../../dao/tenantDao.h"
#include "tenants.h"
using namespace std;

 void managerHome() {
    while(true) {
        cout << "-------------------------------\n";
        cout << "      Manager's Dashboard\n";
        cout << "-------------------------------\n";

        cout << "1. Display All Registered Tenant' Details\n";
        cout << "2. Generate Report\n";
        cout << "3. Manage Tenency Process\n";
        cout << "4. Manage payment of confirmed tenency\n";
        cout << "0. LogOut\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch(choice) {          
   
            case 1:
                tenentsPage();
                break;
            case 2:
                //();
                break;
            case 3:
                //();
                break;
            case 4:
                //;
                break;

            default: cout << "Invalid choice. Try again.\n";

            case 0: return; // Exit the program
            break;
        }        
    }
}
