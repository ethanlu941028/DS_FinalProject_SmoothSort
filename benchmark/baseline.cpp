#include "baseline.h"
#include <algorithm>
#include <vector>
using namespace std;

// --- 手動實作 Insertion Sort ---
// 時間複雜度: O(n^2)，在 n=100,000 時會明顯緩慢
void manual_insertion_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // 將大於 key 的元素向後移動一位
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// --- 手動實作 Heap Sort ---
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void manual_heap_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// --- 手動實作 Quick Sort ---
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort_recursive(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void manual_quick_sort(vector<int>& arr) {
    if (arr.empty()) return;
    quick_sort_recursive(arr, 0, arr.size() - 1);
}

// STL sort 包裝函數
void stl_sort(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}