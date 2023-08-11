#include <iostream>
#include <string>

using namespace std;

void adminHome(string name)
{
    int input;
    while (true)
    {
        cout << "\nWelcome Admin - " << name << endl;
        cout << "Please enter your selected option:" << endl;
        cout << "1. Add new manager user." << endl;
        cout << "2. Update manager status." << endl;
        cout << "3. Display all registered tenants." << endl;
        cout << "4. Display property information." << endl;
        cout << "5. Sign out." << endl;
        cin >> input;

        switch (input)
        {
            case 1:
                // Implement the logic for adding a new manager user.
                break;
            case 2:
                // Implement the logic for updating manager status.
                break;
            case 3:
                // Implement the logic for displaying all registered tenants.
                break;
            case 4:
                // Implement the logic for displaying property information.
                break;
            case 5:
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}