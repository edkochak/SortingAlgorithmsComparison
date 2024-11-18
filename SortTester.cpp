#include "SortTester.h"
#include "ArrayGenerator.h"
#include "Sorter.h"
#include <chrono>
#include <fstream>
#include <iostream>

void SortTester::runTests() {
    std::vector<std::string> arrayTypes = {"random", "reversed", "nearly_sorted"};
    for (const auto& type : arrayTypes) {
        testStandardMergeSort(type);
        testHybridMergeSort(type, 10); // пример порогового значения
    }
}

void SortTester::testStandardMergeSort(const std::string& arrayType) {
    std::vector<int> sizes;
    std::vector<double> times;
    for (int size = 500; size <= 100000; size += 100) {
        std::vector<int> arr = getArray(arrayType, size);
        auto start = std::chrono::high_resolution_clock::now();
        Sorter::mergeSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        double msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        sizes.push_back(size);
        times.push_back(msec);
    }
    saveResults("standard_merge_" + arrayType + ".txt", sizes, times);
}

void SortTester::testHybridMergeSort(const std::string& arrayType, int threshold) {
    std::vector<int> sizes;
    std::vector<double> times;
    for (int size = 500; size <= 100000; size += 100) {
        std::vector<int> arr = getArray(arrayType, size);
        auto start = std::chrono::high_resolution_clock::now();
        Sorter::hybridMergeSort(arr, 0, arr.size() - 1, threshold);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        double msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        sizes.push_back(size);
        times.push_back(msec);
    }
    saveResults("hybrid_merge_" + arrayType + "_th" + std::to_string(threshold) + ".txt", sizes, times);
}

std::vector<int> SortTester::getArray(const std::string& arrayType, int size) {
    static std::vector<int> maxRandomArray = ArrayGenerator::generateRandomArray(10000);
    static std::vector<int> maxReversedArray = ArrayGenerator::generateReversedArray(10000);
    static std::vector<int> maxNearlySortedArray = ArrayGenerator::generateNearlySortedArray(10000, 10);

    if (arrayType == "random") {
        return std::vector<int>(maxRandomArray.begin(), maxRandomArray.begin() + size);
    } else if (arrayType == "reversed") {
        return std::vector<int>(maxReversedArray.begin(), maxReversedArray.begin() + size);
    } else if (arrayType == "nearly_sorted") {
        return std::vector<int>(maxNearlySortedArray.begin(), maxNearlySortedArray.begin() + size);
    } else {
        return {};
    }
}

void SortTester::saveResults(const std::string& filename, const std::vector<int>& sizes, const std::vector<double>& times) {
    std::ofstream outFile(filename);
    for (size_t i = 0; i < sizes.size(); ++i) {
        outFile << sizes[i] << " " << times[i] << "\n";
    }
    outFile.close();
}