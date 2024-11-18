#pragma once
#include <vector>

class ArrayGenerator {
public:
    static std::vector<int> generateRandomArray(int size, int minValue = 0, int maxValue = 6000);
    static std::vector<int> generateReversedArray(int size);
    static std::vector<int> generateNearlySortedArray(int size, int swaps);
};
