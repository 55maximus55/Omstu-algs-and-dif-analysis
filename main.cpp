#include <cstdlib>
#include <vector>
#include <iostream>

#include "Tester.h"
#include "BubbleSort.h"
#include "CombSort.h"
#include "QuickSort.h"

int main() {
    std::vector<int> vec = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    std::vector<int> res = {1, 2, 3, 4, 5, 5, 7, 8, 9};
    Assert(BubbleSort, vec, res);
    Assert(CombSort, vec, res);
    Assert(QuickSort, vec, res);

    return EXIT_SUCCESS;
}