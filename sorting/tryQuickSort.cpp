#include <iostream>
#include "../data-structure/ArrayList.h" // Include the correct header file for ArrayList

// Generic comparison function to compare two objects
template <typename T>
bool compare(const T& a, const T& b) {
    return a < b;
}

// Helper function to swap two objects
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Generic partition function for QuickSort
template <typename T>
int partition(ArrayList<T>& arr, int low, int high) {
    T pivot = arr.get(high); // Choose the pivot as the last element
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        // Compare with the chosen property
        if (compare(arr.get(j), pivot)) {
            i++;
            swap(arr.get(i), arr.get(j));
        }
    }

    swap(arr.get(i + 1), arr.get(high));
    return i + 1;
}

// Generic QuickSort function
template <typename T>
void quickSort(ArrayList<T>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    // Creating an ArrayList of integers
    ArrayList<int> intList;
    intList.add(42);
    intList.add(17);
    intList.add(8);
    intList.add(99);
    intList.add(23);

    std::cout << "Original list: ";
    intList.printAll();

    // Sorting the list using QuickSort
    quickSort(intList, 0, intList.getSize() - 1);

    std::cout << "Sorted list: ";
    intList.printAll();

    // Creating an ArrayList of strings
    ArrayList<std::string> stringList;
    stringList.add("apple");
    stringList.add("banana");
    stringList.add("grape");
    stringList.add("cherry");
    stringList.add("kiwi");

    std::cout << "Original list: ";
    stringList.printAll();

    // Sorting the list using QuickSort
    quickSort(stringList, 0, stringList.getSize() - 1);

    std::cout << "Sorted list: ";
    stringList.printAll();

    return 0;
}
