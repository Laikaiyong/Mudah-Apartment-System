#pragma once
#include <iostream>
#include <optional>
#include "../dao/propertyDao.h"
#include "../dao/tenantDao.h"
#include "../dao/RentRequestDao.h"
#include "../entity/Tenant.h"

using namespace std;

void selectProperty(optional<Property> &optionalProperty)
{
    PropertyDao *propertyDao = PropertyDao::getInstance();
    string id;
    string anyKey;
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID:" << endl;
        cin >> id;
        if (id == "e")
        {
            optionalProperty = nullopt;
            return;
        }
        optionalProperty = propertyDao->getById(id);
        if (optionalProperty.has_value())
        {
            break;
        }
        cout << "Property ID : \"" + id + "\" is not found, please try again." << endl;
        cout << "Press any key to continue.\n";
        cin >> anyKey;
    }
    cout << endl;
    cout << optionalProperty.value() << endl;
}

void addFavouriteProperty(Property &property)
{
    string anyKey;
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    tenant->addFavourtiteProperty(property);
    cout << "Successfully added the selected property into your favourite property list.\n";
    cout << "Press any key to continue.\n";
    cin >> anyKey;
}

void deleteSpecificFavouriteProperty(Tenant &tenant)
{
    string id;
    string anyKey;
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID:" << endl;
        cin >> id;
        if (id == "e")
        {
            return;
        }
        if (tenant.removeFavouritePropertyById(id))
        {
            cout << "Successfully remove property id: " + id + " from your favourite property list" << endl;
            cout << "Press any key to continue.\n";
            cin >> anyKey;
            return;
        }
        cout << "Property ID : \"" + id + "\" is not found from your favourite property list, please try again." << endl;
    }
}

void createRentRequest()
{
    string id;
    string anyKey;
    optional<Property> optionalProperty;
    RentRequestDao *rentRequestDao = RentRequestDao::getInstance();
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    while (true)
    {
        cout << "To go back, press \"e\" and enter." << endl;
        cout << "Please type the property ID from your saved favourite property list:" << endl;
        cin >> id;
        if (id == "e")
        {
            return;
        }
        optionalProperty = tenant->getFavourtitePropertyById(id);
        if (optionalProperty.has_value())
        {
            rentRequestDao->createRentRequest(*tenant, optionalProperty.value());
            cout << "Successfully create rent request of property id: " + id << endl;
            cout << "Press any key to continue.\n";
            cin >> anyKey;
            return;
        }
        cout << "Property ID : \"" + id + "\" is not found from your favourite property list, please try again." << endl;
    }
}

void displayRentRequest(ArrayList<RentRequest> *rentRequestArray, int propPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = rentRequestArray->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (rentRequestArray->getSize() / propPerPage) + 1 : rentRequestArray->getSize() / propPerPage;

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
    RentRequest rentRequest;
    cout << endl;
    for (int i = end - 1; i >= start; i--)
    {
        rentRequest = rentRequestArray->get(i);
        cout << "----------------------------------------------------------" << endl;
        cout << rentRequest.getProperty() << endl;
        cout << "Approve Status: " + rentRequest.getStringApprove() << endl;
    }
    cout << "----------------------------------------------------------" << endl;
}

void displayFilterRentRequest()
{
    TenantDao *tenantDao = TenantDao::getInstance();
    Tenant *tenant = tenantDao->getCurrentTenant();
    RentRequestDao *rentRequestDao = RentRequestDao::getInstance();
    ArrayList<RentRequest> *rentRequestList = rentRequestDao->getAllRentRequestByTenantId(tenant->getUserId());
    
    int selectedPage = 1;
    int input;
    while (true)
    {
        if (rentRequestList->getSize() == 0)
        {
            cout << "Your Rent Request of Property is empty" << endl;
            return;
        }
        displayRentRequest(rentRequestList, 5, selectedPage);
        cout << "Current Page: " + to_string(selectedPage) << endl;
        cout << "Please press your selected option:" << endl;
        cout << "Option 1: Change page." << endl;
        cout << "Option 0: Back." << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            return;
            break;
        case 1:
            cout << "Please type the page number to display the property" << endl;
            cin >> selectedPage;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
    delete rentRequestList;
}
