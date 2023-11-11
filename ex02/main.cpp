#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib> // For atoi and exit
#include <iterator> // For std::distance

// Forward declarations of the sorting functions
void mergeInsertionSort(std::vector<int>& elements);
void mergeInsertionSortList(std::list<int>& elements);

bool isPositiveInteger(const char* str) {
    while (*str) {
        if (!isdigit(*str)) return false;
        str++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " list of integers" << std::endl;
        return 1;
    }

    std::vector<int> numbersVector;
    std::list<int> numbersList;

    // Parsing input
    for (int i = 1; i < argc; ++i) {
        if (!isPositiveInteger(argv[i]) || std::atoi(argv[i]) <= 0) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        int num = std::atoi(argv[i]);
        numbersVector.push_back(num);
        numbersList.push_back(num);
    }
    std::cout << "Before: ";
    for (std::vector<int>::iterator it = numbersVector.begin(); it != numbersVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Sort using vector
    clock_t startVector = clock();
    mergeInsertionSort(numbersVector);
    clock_t endVector = clock();
    double timeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1e6; // Convert to microseconds

    // Sort using list
    clock_t startList = clock();
    mergeInsertionSortList(numbersList);
    clock_t endList = clock();
    double timeList = static_cast<double>(endList - startList) / CLOCKS_PER_SEC * 1e6; // Convert to microseconds

    // Output results
    std::cout << "After(vector): ";
    for (std::vector<int>::iterator it = numbersVector.begin(); it != numbersVector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "After(list): ";
    for (std::list<int>::iterator it = numbersList.begin(); it != numbersList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : " << timeList << " us" << std::endl;

    return 0;
}