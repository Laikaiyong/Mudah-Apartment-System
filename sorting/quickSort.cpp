#include <iostream>
#include "../dao/propertyDao.h"
#include "../sorting/quickSort.h"

using namespace std;

int main() {
    PropertyDao* propertyDao = PropertyDao::getInstance();

    cout << "Original list: " << endl;
    propertyDao->printAll(); // Display the original Dao

    // Sorting the Dao by completionYear using QuickSort
    quickSort(propertyDao, 0, propertyDao->getSize() - 1, 0);

    cout << "Sorted Dao by completionYear: " << endl;
    propertyDao->printAll(); // Display the sorted list

    return 0;
}