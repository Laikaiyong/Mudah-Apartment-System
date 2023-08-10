#include <iostream>
#include "../../dao/tenantDao.h"
#include "../../dao/managerDao.h"

using namespace std;

class ManagerHomepage {
    TenantDao *tenantDao;
    ManagerDao *managerDao;

public:
    ManagerHomepage() {
        tenantDao = TenantDao::getInstance();
        managerDao = ManagerDao::getInstance();
    }

    void login() {
        // Logic for manager login
        cout << "Enter Manager Credentials to Login" << endl;
        // Sample logic; can be expanded with actual authentication mechanism
    }

    void logout() {
        // Logic for logout
        cout << "Logged out successfully!" << endl;
    }

    void displayAllTenants() {
        tenantDao->printall();
    }

    void searchTenantDetails() {
        cout << "Enter Tenant Username to search: ";
        string query;
        cin >> query;
        
        if (tenantDao->checkTenantUsernameTaken(query)) {
            cout << "Tenant with username " << query << " found!" << endl;
        } else {
            cout << "No tenant found with the provided username." << endl;
        }
    }

    // Other methods for manager operations can be added similarly

    void displayMenu() {
        while(true) {
            cout << "-------------------------------\n";
            cout << "      Manager's Dashboard\n";
            cout << "-------------------------------\n";
            cout << "1. Login\n";
            cout << "2. Logout\n";
            cout << "3. Display All Registered Tenants\n";
            cout << "4. Search Tenant Details\n";
            cout << "5. Exit\n";
            cout << "-------------------------------\n";
            cout << "Enter your choice: ";
            
            int choice;
            cin >> choice;

            switch(choice) {
                case 1: login(); break;
                case 2: logout(); break;
                case 3: displayAllTenants(); break;
                case 4: searchTenantDetails(); break;
                case 5: return;  // Exit the program
                default: cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    ManagerHomepage managerHomepage;
    managerHomepage.displayMenu();
    return 0;
}