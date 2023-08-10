#include <iostream>
#include "dao/propertyDao.h"
#include "pages/signUp.h"
#include "search-method/BinarySearch.h"
using namespace std;

int main()
{
    PropertyDao* propertyDao = PropertyDao::getInstance();
 signUpPage();
    return 0;

    ///
    std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value = 6;

    auto greaterThan = [](int a, int b) { return a > b; };
    int result = binarySearch(array, value, greaterThan);

    if (result == -1) {
        std::cout << "Value not found!" << std::endl;
    } else {
        std::cout << "Value found at index: " << result << std::endl;
    }

    return 0;
}



    

