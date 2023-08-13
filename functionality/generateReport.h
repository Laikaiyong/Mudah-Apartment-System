#include <iostream>
#include "../data-structure/ArrayList.h"
#include "../searching/linearSearch.h"
#include "../sorting/mergeSort.h"
#include "../entity/tenant.h"
#include "../entity/property.h"
#include "../dao/tenantDao.h"

using namespace std;

struct PropertyCount
{
    Property property;
    int num;
};

void generateTop10FavourtieProperty()
{
    TenantDao *tenantDao = TenantDao::getInstance();
    int size;
    Tenant *tenantList = tenantDao->getAllTenant(size);
    ArrayList<PropertyCount> propertyCountList;
    Property *favourtiePropertyList;
    PropertyCount temp;
    int index;
    for (int i = 0; i < size; i++)
    {
        favourtiePropertyList = tenantList[i].getFavouritePropertyList()->cloneArray();

        for (int j = 0; j < tenantList->getFavouritePropertyList()->getSize(); j++)
        {
            temp.property = favourtiePropertyList[j];
            index = linearSearch(propertyCountList.getArray(), tenantList->getFavouritePropertyList()->getSize(), temp, [](PropertyCount &p1, PropertyCount &p2)
                             { return p1.property.getAdsId() == p2.property.getAdsId(); });
            if (index != -1)
            {
                propertyCountList.get(index).num++;
            }
            else
            {
                temp.num = 1;
                propertyCountList.add(temp);
            }
        }
    }
    mergeSort(propertyCountList.getArray(), propertyCountList.getSize(), [](PropertyCount &p1, PropertyCount &p2)
                             { return p1.num > p2.num; });
    cout << "------------------------------------------" << endl;
    size = propertyCountList.getSize() >= 10 ? 10 : propertyCountList.getSize();
    for (int i = 0; i < size; i++)
    {
        cout << "Top " << i + 1 << " Favourite Property:\n\n";
        cout << propertyCountList.get(i).property << endl;
        cout << "Number of Tenant's Favourite Property: " << propertyCountList.get(i).num << endl;
        cout << "------------------------------------------" << endl;
    }
}