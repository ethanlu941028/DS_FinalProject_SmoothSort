#ifndef BASELINE_H
#define BASELINE_H

#include <vector>

using namespace std;

// 基準排序演算法的宣告

// Insertion Sort - O(n^2) 時間複雜度
void manual_insertion_sort(vector<int>& arr);

// Heap Sort - O(n log n) 時間複雜度
void heapify(vector<int>& arr, int n, int i);
void manual_heap_sort(vector<int>& arr);

// Quick Sort - 平均 O(n log n)，最差 O(n^2) 時間複雜度
int partition(vector<int>& arr, int low, int high);
void quick_sort_recursive(vector<int>& arr, int low, int high);
void manual_quick_sort(vector<int>& arr);

// STL Sort - 通常是 Introsort (Quicksort + Heapsort + Insertion sort)
void stl_sort(vector<int>& arr);

#endif // BASELINE_H