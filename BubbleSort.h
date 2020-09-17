#ifndef TEST_BUBBLESORT_H
#define TEST_BUBBLESORT_H

#include <vector>
#include <iostream>

std::vector<int> BubbleSort(std::vector<int> vec) {
    for (int i = 0; i + 1 < vec.size(); ++i) {
        for (int j = i + 1; j < vec.size(); ++j) {
            if (vec[i] > vec[j]) Swap(vec[i], vec[j]);
        }
    }
    return vec;

}


#endif //TEST_BUBBLESORT_H