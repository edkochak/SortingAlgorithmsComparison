#pragma once
#include <vector>

class Sorter {
public:
    static void mergeSort(std::vector<int>& arr, int left, int right);
    static void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold);
private:
    static void merge(std::vector<int>& arr, int left, int mid, int right);
    static void insertionSort(std::vector<int>& arr, int left, int right);
};