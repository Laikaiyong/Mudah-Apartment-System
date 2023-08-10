#pragma once
#include <iostream>
#include <cmath>
#include "../data-structure/ArrayList.h"
#include "../entity/property.h"
#include "../file/readFile.h"
#include "../sorting/mergeSort.h"

using namespace std;

class PropertyDao
{
    static PropertyDao *instancePtr;

    ArrayList<Property> *list;
    ArrayList<Property> *filterList;

    PropertyDao()
    {
        int rowSize = 19991;
        list = new ArrayList<Property>(readFile(rowSize), rowSize);
        filterList = new ArrayList<Property>();
        this->sortByDesc();
    }

public:
    static PropertyDao *getInstance();

    int getSize();

    void printAll();

    void displayAllPropsByPage(int propPerPage, int startPage);

    void displayFilterPropsByPage(int propPerPage, int startPage);

    void sortByDesc();

    template <typename Filter>
    void filter(Filter compare);

    // Property &getById();
};

PropertyDao *PropertyDao::instancePtr = nullptr;

PropertyDao *PropertyDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new PropertyDao();
    }
    return instancePtr;
}

int PropertyDao::getSize()
{
    return list->getSize();
}

void PropertyDao::printAll()
{
    Property property;
    for (int n = 0; n < list->getSize(); n++)
    {
        property = list->get(n);
        cout << "Index: " << n << endl;
        cout << "Ads id: " << property.getAdsId() << endl;
        cout << "Property Name: " << property.getPropName() << endl;
        cout << "Completion Year: " << property.getCompletionYear() << endl;
        cout << "Monthly Rent: " << property.getMonthlyRent() << endl;
        cout << "Location: " << property.getLocation() << endl;
        cout << "Property Type: " << property.getPropertyType() << endl;
        cout << "Rooms: " << property.getRooms() << endl;
        cout << "Parking: " << property.getParking() << endl;
        cout << "Bathroom: " << property.getBathroom() << endl;
        cout << "Size: " << property.getSize() << endl;
        cout << "Furnished: " << property.getFurnished() << endl;
        cout << "Facilities: " << property.getFacilities() << endl;
        cout << "Additional Facilities: " << property.getAdditionalFacilities() << endl;
        cout << "-------------------------------------" << endl
             << endl;
    }
}

void PropertyDao::displayAllPropsByPage(int propPerPage, int startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = list->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (list->getSize() / propPerPage) + 1 : list->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        throw runtime_error("Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")");
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
}

void PropertyDao::displayFilterPropsByPage(int propPerPage, int startPage)
{
    if (startPage < 1)
    {
        throw invalid_argument("Starting page must be more than or equal one");
    }
    int restProp = filterList->getSize() % propPerPage;
    int totalPage = restProp > 0 ? (filterList->getSize() / propPerPage) + 1 : filterList->getSize() / propPerPage;

    if (startPage > totalPage)
    {
        throw runtime_error("Total Page (" + to_string(totalPage) + ") have exceeded the starting page (" + to_string(startPage) + ")");
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
        cout << filterList->get(i) << endl;
    }
}

void PropertyDao::sortByDesc()
{
    mergeSort(list->getArray(), list->getSize(), [](Property &p1, Property &p2)
              {
                  if (p1.getMonthlyRent() != p2.getMonthlyRent()) {
                    return p1.getMonthlyRent() > p2.getMonthlyRent();
                  } 
                  else if (p1.getLocation() != p2.getLocation()) {
                    return p1.getLocation() > p2.getLocation();
                  }
                  return p1.getSize() >= p1.getSize(); });
    cout << "Finish sort by descending order" << endl;
}

template <typename Filter>
void PropertyDao::filter(Filter compare)
{
    delete this->filterList;
    int totalMatch = 0;
    // increment the totalMatch if match filter
    for (int i = 0; i < this->list->getSize(); i++)
    {
        if (compare(this->list->get(i)))
        {
            totalMatch++;
        }
    }
    if (totalMatch == 0)
    {
        this->filterList = new ArrayList<Property>();
    }
    // create an array to store all the filter data
    Property *newArray = new Property[totalMatch];
    int j = 0;
    // store data if filter match
    for (int i = 0; i < this->list->getSize(); i++)
    {
        if (compare(this->list->get(i)))
        {
            newArray[j++] = this->list->get(i);
        }
    }
    this->filterList = new ArrayList<Property>(newArray, totalMatch);
    cout << "Successfully filter property" << endl;
}

// Property &PropertyDao::getById() {

// }
