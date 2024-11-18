#pragma once
#include <vector>
#include <string>

class SortTester {
public:
    void runTests();
private:
    void testStandardMergeSort(const std::string& arrayType);
    void testHybridMergeSort(const std::string& arrayType, int threshold);
    std::vector<int> getArray(const std::string& arrayType, int size);
    void saveResults(const std::string& filename, const std::vector<int>& sizes, const std::vector<double>& times);
};