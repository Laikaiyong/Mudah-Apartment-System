#pragma once
#include <iostream>
#include <optional>
#include <cmath>
#include "../data-structure/ArrayList.h"
#include "../entity/property.h"
#include "../file/readFile.h"
#include "../sorting/mergeSort.h"
#include "../sorting/oldQuickSort.h"
#include "../searching/binarySearch.h"

using namespace std;

class PropertyDao
{
    static PropertyDao *instancePtr;
    static int currentSort;

    ArrayList<Property> *list;
    ArrayList<Property> *filterList;

    PropertyDao()
    {
        int rowSize = 19991;
        list = new ArrayList<Property>(readFile(rowSize), rowSize);
        filterList = new ArrayList<Property>();
        this->sortByDesc();
        this->printAll();
    }

public:
    static PropertyDao *getInstance();

    int getSize();

    void printAll();

    /*  display the list by pages
        parameter: 
        propPerPage - number of property shown in one page
        startPage - starting page to display
        Example: propPerPage = 10, startPage = 3, display start from index (30 - 1) */
    void displayAllPropsByPage(int propPerPage, int startPage);

    
    /*  display the filter list by pages
        parameter: 
        propPerPage - number of property shown in one page
        startPage - starting page to display
        Example: propPerPage = 5, startPage = 7, display start from index (35 - 1) */
    void displayFilterPropsByPage(int propPerPage, int startPage);

    void sortByDesc();

    void sortIdByAsc();

    void sortMonthlyRentByAsc();

    template <typename Filter>
    void filter(Filter compare);

    optional<Property> getById(string id);
};

PropertyDao *PropertyDao::instancePtr = nullptr;
int PropertyDao::currentSort = 1;

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
    if (PropertyDao::currentSort == 0) 
    {
        return;
    }
    mergeSort(list->getArray(), list->getSize(), [](Property &p1, Property &p2)
              {
                  if (p1.getMonthlyRent() != p2.getMonthlyRent()) {
                    return p1.getMonthlyRent() > p2.getMonthlyRent();
                  } 
                  else if (p1.getLocation() != p2.getLocation()) {
                    return p1.getLocation() > p2.getLocation();
                  }
                  return p1.getSize() >= p2.getSize(); });
    PropertyDao::currentSort = 0;
    cout << "Finish sort by descending order" << endl;
}

void PropertyDao::sortIdByAsc()
{
    mergeSort(list->getArray(), list->getSize(), [](Property &p1, Property &p2)
              { return p1.getAdsId() < p2.getAdsId(); });
    PropertyDao::currentSort = 1;
    cout << "Finish sort ID by ascending order" << endl;
}

void PropertyDao::sortMonthlyRentByAsc()
{
    quickSort(list->getArray(), 0, list->getSize() - 1,  [](Property &p1, Property &p2)
              { return p1.getMonthlyRent() < p2.getMonthlyRent(); });
    PropertyDao::currentSort = 2;
    cout << "Finish sort Monthly Rent by ascending order" << endl;
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

optional<Property> PropertyDao::getById(string id)
{
    Property property;
    property.setAdsId(id);
    sortIdByAsc();
    int index = binarySearch(this->list->getArray(), this->list->getSize(), property, [](Property &p1, Property &p2)
                             { return p1.getAdsId() < p2.getAdsId(); });
    if (index == -1)
    {
        return nullopt;
    }
    return this->list->get(index);
}