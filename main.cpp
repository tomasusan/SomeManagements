#include <iostream>
#include <bits/ostream.tcc>

#include "Sort/Sort.h"

int main() {
    std::vector<int> arr = {4,1,5,6,1,5,7,12,5124,1241,-1,2342,11411,1212315,121,123124531,1312};
    Sort::sort(arr, ESortType::QuickSort);
    for (const int & it : arr) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    Sort::SortTest();
    return 0;
}
