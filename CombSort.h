//
// Created by 55_maximus_55 on 17.09.2020.
//

#ifndef SORT_COMBSORT_H
#define SORT_COMBSORT_H

#include <vector>
#include <iostream>

std::vector<int> CombSort(std::vector<int> vec) {
    for (int i = vec.size() - 1; i > 0; --i) {
        for (int j = 0; j < vec.size() - i; ++j) {
            if (vec[j] > vec[j + i]) Swap(vec[j], vec[j + i]);
        }
    }
    return vec;

}

#endif //SORT_COMBSORT_H
