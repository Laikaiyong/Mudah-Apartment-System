#include <iostream>
#include "../data-structure/CircularLinkedList.h"
#include "../entity/tenant.h"

using namespace std;

class TenantDao
{
    static TenantDao *instancePtr;

    CiruclarLinkedList<Tenant> *list;

    TenantDao()
    {
        list = new CiruclarLinkedList<Tenant>();
    }

public:
    static TenantDao *getInstance();


};

TenantDao *TenantDao::instancePtr = nullptr;

TenantDao *TenantDao::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new TenantDao();
    }
    return instancePtr;
}