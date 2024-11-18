#include "ArrayGenerator.h"
#include <algorithm>
#include <random>

std::vector<int> ArrayGenerator::generateRandomArray(int size, int minValue, int maxValue) {
    std::vector<int> array(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minValue, maxValue);
    for (int& num : array) {
        num = dist(gen);
    }
    return array;
}

std::vector<int> ArrayGenerator::generateReversedArray(int size) {
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = size - i;
    }
    return array;
}

std::vector<int> ArrayGenerator::generateNearlySortedArray(int size, int swaps) {
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, size - 1);
    for (int i = 0; i < swaps; ++i) {
        int idx1 = dist(gen);
        int idx2 = dist(gen);
        std::swap(array[idx1], array[idx2]);
    }
    return array;
}