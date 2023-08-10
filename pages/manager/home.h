#include <iostream>
// #include "../../dao/managerDao.h"

using namespace std;

 void managerHome() {
        while(true) {
            cout << "-------------------------------\n";
            cout << "      Manager's Dashboard\n";
            cout << "-------------------------------\n";
          
            cout << "1. Display All Registered Tenants\n";
            cout << "2. Search Tenant Details\n";
            cout << "3. LogOut\n";
            cout << "-------------------------------\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;

            switch(choice) {
               
                // case 3: displayAllTenants(); break;
                // case 4: searchTenantDetails(); break;
                case 3: return;  // Exit the program
                default: cout << "Invalid choice. Try again.\n";
            }
        }
    }
