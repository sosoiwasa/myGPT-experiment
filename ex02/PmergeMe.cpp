#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// Function to pair elements and perform initial comparisons
void pairAndCompare(std::vector<int>& elements, std::vector<int>& larger, std::vector<int>& smaller) {
    for (size_t i = 0; i < elements.size(); i += 2) {
        if (i + 1 < elements.size()) {
            if (elements[i] > elements[i + 1]) {
                larger.push_back(elements[i]);
                smaller.push_back(elements[i + 1]);
            } else {
                larger.push_back(elements[i + 1]);
                smaller.push_back(elements[i]);
            }
        } else {
            // Handling the case of an odd number of elements
            smaller.push_back(elements[i]);
        }
    }
}

// Recursive function to sort the larger elements
void recursiveSort(std::vector<int>& elements) {
    if (elements.size() <= 1) return;

    std::vector<int> larger, smaller;
    pairAndCompare(elements, larger, smaller);

    // Recursively sort both vectors
    recursiveSort(larger);
    recursiveSort(smaller);

    // Clear the original vector and merge the two sorted vectors back into it
    elements.clear();
    elements.reserve(larger.size() + smaller.size());
    std::merge(larger.begin(), larger.end(), smaller.begin(), smaller.end(), std::back_inserter(elements));
}

// Binary search function for insertion
int binarySearch(const std::vector<int>& sorted, int element, int start, int end) {
    while (start < end) {
        int mid = start + (end - start) / 2;
        if (sorted[mid] < element) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return start;
}

// Function to insert elements using binary search
void insertElements(std::vector<int>& sorted, std::vector<int>& unsorted) {
    for (size_t i = 0; i < unsorted.size(); ++i) {
        int pos = binarySearch(sorted, unsorted[i], 0, sorted.size());
        sorted.insert(sorted.begin() + pos, unsorted[i]);
    }
}

void mergeInsertionSort(std::vector<int>& elements) {
    if (elements.empty()) return;

    std::vector<int> larger, smaller;
    pairAndCompare(elements, larger, smaller);

    // Recursively sort both larger and smaller vectors
    recursiveSort(larger);
    recursiveSort(smaller);

    // Insert elements from the sorted smaller vector into the sorted larger vector
    insertElements(larger, smaller);

    // The larger vector is now fully sorted
    elements = larger;
}

// ###### List version ######

// Function to pair and compare elements in the list
void pairAndCompareList(std::list<int>& lst, std::list<int>& larger, std::list<int>& smaller) {
    bool isPair = false;
    int lastElement;

    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        if (isPair) {
            if (*it > lastElement) {
                larger.push_back(*it);
                smaller.push_back(lastElement);
            } else {
                larger.push_back(lastElement);
                smaller.push_back(*it);
            }
            isPair = false;
        } else {
            lastElement = *it;
            isPair = true;
        }
    }

    if (isPair) {
        // Handle the case of an odd number of elements
        smaller.push_back(lastElement);
    }
}

void mergeInsertionSortList(std::list<int>& lst) {
    if (lst.size() <= 1) return;

    std::list<int> larger, smaller;
    pairAndCompareList(lst, larger, smaller);

    mergeInsertionSortList(larger); // 再帰的に大きい要素をソート
    mergeInsertionSortList(smaller); // 再帰的に小さい要素をソート

    lst.clear(); // 元のリストをクリア

    std::list<int>::iterator itLarger = larger.begin();
    std::list<int>::iterator itSmaller = smaller.begin();

    // 小さい要素のリストを走査し、大きい要素のリストと統合
    while (itLarger != larger.end() && itSmaller != smaller.end()) {
        // 適切な位置に要素を挿入
        if (*itLarger < *itSmaller) {
            lst.push_back(*itLarger++);
        } else {
            // 小さい要素を挿入する正しい位置を見つける
            std::list<int>::iterator insertPos = lst.end();
            while (insertPos != lst.begin() && *prev(insertPos) > *itSmaller) {
                --insertPos;
            }
            lst.insert(insertPos, *itSmaller++);
        }
    }

    // 残りの要素を挿入
    while (itLarger != larger.end()) {
        lst.push_back(*itLarger++);
    }
    while (itSmaller != smaller.end()) {
        lst.insert(lst.end(), *itSmaller++);
    }
}

