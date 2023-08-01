#include <iostream>
#include "../data-structure/ArrayList.h"
#include "../entity/property.h"

using namespace std;

class PropertyDao
{
    static PropertyDao *instancePtr;

    ArrayList<Property> list;

    PropertyDao()
    {
    }

public:
    // deleting copy constructor
    PropertyDao(const PropertyDao &obj) = delete;

    static PropertyDao *getInstance();


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