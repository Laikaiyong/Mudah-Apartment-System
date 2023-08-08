#include <iostream>
#include "dao/propertyDao.h"
#include "pages/home.h"

using namespace std;

int main()
{
    PropertyDao* propertyDao = PropertyDao::getInstance();
    homePage();

    return 0;
}
