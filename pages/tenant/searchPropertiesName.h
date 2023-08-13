#include <iostream>
#include "../../dao/propertyDao.h"
#include "specificProperty.h"

using namespace std;

void displaySearchPropsByPage(ArrayList<Property> *list, int propPerPage, int &startPage)
{
    if (list->getSize() == 0)
    {
        cout << "No results found, please try again with another search property name" << endl;
        return;
    }
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = list->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (list->getSize() / propPerPage) + 1 : list->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * propPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restProp;
    }
    else
    {
        end = start + propPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << list->get(i) << endl;
    }
    cout << "Current Page: " + to_string(startPage) << endl;
}

void searchPropertiesNamePage()
{
    string searchName;
    int selectedPage = 1;
    PropertyDao *propertyDao = PropertyDao::getInstance();
    int input;
    cout << "Please type the property name to search all the property." << endl;
    cin >> searchName;
    propertyDao->sortByDesc();
    ArrayList<Property> *list = propertyDao->searchByPropertyName(searchName);
    while (true)
    {
        displaySearchPropsByPage(list, 10, selectedPage);
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Search property name." << endl;
        cout << "Option 2: Select specific property." << endl;
        cout << "Option 3: Change page." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            delete list;
            cout << "Please type the property name to search all the property." << endl;
            cin >> searchName;
            selectedPage = 1;
            list = propertyDao->searchByPropertyName(searchName);
            break;
        case 2:
            specificPropertyPage();
            break;
        case 3:
            cout << "Please type the page number to display the property." << endl;
            cin >> selectedPage;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}