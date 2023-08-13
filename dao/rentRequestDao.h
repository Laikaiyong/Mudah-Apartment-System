#pragma once
#include <iostream>
#include <optional>
#include "../data-structure/ArrayList.h"
#include "../entity/property.h"
#include "../entity/tenant.h"
#include "../entity/rentRequest.h"
#include "../dao/propertyDao.h"
#include "../dao/tenantDao.h"
#include "../searching/binarySearch.h"
#include "../sorting/mergeSort.h"

using namespace std;

class RentRequestDao
{
    static RentRequestDao *instancePtr;

    ArrayList<RentRequest> *list;
    ArrayList<RentRequest> *filterList;

    RentRequestDao()
    {
        list = new ArrayList<RentRequest>();
        filterList = new ArrayList<RentRequest>();
    }

public:
    static RentRequestDao *getInstance();

    void createRentRequest(Tenant &tenant, Property &property);

    optional<RentRequest> getRentRequestById(int id);

    ArrayList<RentRequest> *getAllRentRequestByTenantId(int userId);

    void sortUserIdByAscRQ();

    template <typename Filter>
    void filter(Filter compare);

    void displayFilterRequestsByPage(int requestPerPage, int &startPage);

    void displayAllRentReqByPage(int rentPerPage, int &startPage);

    bool manageTenancyProcess(RentRequest &rentRequest);

    bool managePaymentProcess(RentRequest &rentRequest);
};

RentRequestDao *RentRequestDao::instancePtr = nullptr;

RentRequestDao *RentRequestDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new RentRequestDao();
    }
    return instancePtr;
}

void RentRequestDao::createRentRequest(Tenant &tenant, Property &property)
{
    this->list->add(RentRequest(tenant, property));
}

optional<RentRequest> RentRequestDao::getRentRequestById(int id)
{
    RentRequest rentRequest(id);
    int index = binarySearch(this->list->getArray(), this->list->getSize(), rentRequest, [](RentRequest &r1, RentRequest &r2)
                             { return r1.getId() < r2.getId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->list->get(index);
}

ArrayList<RentRequest> *RentRequestDao::getAllRentRequestByTenantId(int userId)
{
    ArrayList<RentRequest> *rentRequestArray = new ArrayList<RentRequest>();
    for (int i = 0; i < this->list->getSize(); i++)
    {
        if (this->list->get(i).getTenant().getUserId() == userId)
        {
            rentRequestArray->add(this->list->get(i));
        }
    }
    return rentRequestArray;
}

void RentRequestDao::sortUserIdByAscRQ()
{
    mergeSort(list->getArray(), list->getSize(), [](RentRequest &r1, RentRequest &r2)
              { return r1.getTenant().getUserId() < r2.getTenant().getUserId(); });
    cout << "Finish sort Tenant ID for rent request by ascending order" << endl;
}

template <typename Filter>
void RentRequestDao::filter(Filter compare)
{
    delete this->filterList;
    this->filterList = new ArrayList<RentRequest>();
    // add into filter list if match filter
    for (int i = 0; i < this->list->getSize(); i++)
    {
        if (compare(this->list->get(i)))
        {
            this->filterList->add(this->list->get(i));
        }
    }
    cout << "Successfully filter property" << endl;
}

void RentRequestDao::displayFilterRequestsByPage(int requestPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = filterList->getSize() % requestPerPage;
    int totalPage = restProp > 0 ? (filterList->getSize() / requestPerPage) + 1 : filterList->getSize() / requestPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * requestPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restProp;
    }
    else
    {
        end = start + requestPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << filterList->get(i) << endl;
    }
}

void RentRequestDao::displayAllRentReqByPage(int rentPerPage, int &startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restRent = list->getSize() % rentPerPage;
    int totalPage = restRent > 0 ? (list->getSize() / rentPerPage) + 1 : list->getSize() / rentPerPage;

    if (startPage > totalPage)
    {
        cout << "Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")" << endl;
        cout << "Displaying the last page" << endl;
        startPage = totalPage;
    }

    int start = (startPage - 1) * rentPerPage;
    int end;

    if (startPage == totalPage)
    {
        end = start + restRent;
    }
    else
    {
        end = start + rentPerPage;
    }
    cout << endl;
    for (int i = start; i < end; i++)
    {
        cout << list->get(i) << endl;
    }
}

bool RentRequestDao::manageTenancyProcess(RentRequest &rentRequest)
{
    int index = binarySearch(this->list->getArray(), this->list->getSize(), rentRequest, [](RentRequest &r1, RentRequest &r2)
                             { return r1.getId() < r2.getId(); });
    if (index == -1)
    {
        cout << "Rent Request ID : \"" << rentRequest.getId() << "\" is not found, please try again." << endl;
        return false;
    }
    rentRequest = this->list->get(index);

    PropertyDao *propertyDao = PropertyDao::getInstance();

    optional<Property> optionalProperty = propertyDao->getById(rentRequest.getProperty().getAdsId());
    Property property = optionalProperty.value();

    // Check if the property is available for rent
    if (property.getRentStatus() == "Unavailable")
    {
        cout << "Property is not available for rent." << endl;
        return false;
    }
    if (property.getRentStatus() == "Rented")
    {
        cout << "Property is already rented." << endl;
        return false;
    }
    // Check if the request is already approved
    if (rentRequest.getApprove() != 0)
    {
        cout << "Rent request is already approved." << endl;
        return false;
    }
    int input;
    cout << rentRequest << endl;
    cout << "------------------------------" << endl;
    cout << "Select an option:\n";
    cout << "1: Approve\n";
    cout << "2: Reject\n";
    cin >> input;
    if (input < 1 || input > 2)
    {
        cout << "Invalid Option" << endl;
        return false;
    }
    rentRequest.setApprove(input);
    if (input == 1)
    {
        cout << "Tenancy process completed. Rent Request ID: \"" << rentRequest.getId() << "\" is approved." << endl;
    }
    if (input == 2)
    {
        cout << "Tenancy process completed. Rent Request ID: \"" << rentRequest.getId() << "\" is rejected." << endl;
        return false;
    }

    // Mark property as rented and set tenant
    propertyDao->updatePropertyRentStatus(property, "Rented");
    return true;
}

bool RentRequestDao::managePaymentProcess(RentRequest &rentRequest)
{
    int index = binarySearch(this->list->getArray(), this->list->getSize(), rentRequest, [](RentRequest &r1, RentRequest &r2)
                             { return r1.getId() < r2.getId(); });
    if (index == -1)
    {
        cout << "Rent Request ID: " << rentRequest.getId() << " is not found, please try again." << endl;
        return false;
    }
    rentRequest = this->list->get(index);

    // Check if the request is already approved
    if (rentRequest.getApprove() != 1)
    {
        cout << "Rent request is not approved." << endl;
        return false;
    }

    // Check if the payment is already made
    if (rentRequest.isPaid())
    {
        cout << "Payment is already made." << endl;
        return false;
    }

    int input;
    cout << rentRequest << endl;
    cout << "------------------------------" << endl;
    cout << "Select an option:\n";
    cout << "1: Update Payment\n";
    cout << "2: Cancel\n";
    cin >> input;
    if (input < 1 || input > 2)
    {
        cout << "Invalid Option" << endl;
        return false;
    }

    if (input == 1)
    {
        // Mark the payment as made
        rentRequest.setPaid(true);
        Tenant &tenant = rentRequest.getTenant();
        Property property = rentRequest.getProperty();
        tenant.addRentHistoryPropertyList(property);
        cout << "Payment process completed. Rent Request ID: " << rentRequest.getId() << " payment is made." << endl;
        return true;
    }
    else
    {
        cout << "Payment process cancelled." << endl;
    }
    return false;
}