//
// Created by 55_maximus_55 on 17.09.2020.
//

#ifndef SORT_QUICKSORT_H
#define SORT_QUICKSORT_H

#include <vector>
#include <iostream>

void QuickSort(std::vector<int>& vec, int a, int b) {
    if (b - a > 2) {
        int c = b - 1;
        int t = vec[c];

        std::vector<int> vec_less;
        std::vector<int> vec_greater;
        for (int i = a; i < b; i++) {
            if (i != c) {
                if (vec[i] < vec[c]) {
                    vec_less.push_back(vec[i]);
                } else {
                    vec_greater.push_back(vec[i]);
                }
            }
        }
        for (int i = 0; i < vec_less.size(); i++) {
            vec[a + i] = vec_less[i];
        }
        for (int i = 0; i < vec_greater.size(); i++) {
            vec[a + vec_less.size() + i + 1] = vec_greater[i];
        }
        c = a + vec_less.size();
        vec[a + vec_less.size()] = t;

        for (int i = a; i < b; i++) {
            cout << vec[i] << " ";
        }
        cout << endl;
        QuickSort(vec, a , c);
        QuickSort(vec, c, b);
    }
}

std::vector<int> QuickSort(std::vector<int> vec) {
    QuickSort(vec, 0, vec.size());
    return vec;
}

#endif //SORT_QUICKSORT_H
