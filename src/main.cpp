#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include "smooth_sort.h" // 確保此檔案在同目錄

using namespace std;
using namespace std::chrono;

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

// 測量函式
template<typename Func>
long long measure_time(Func sort_func, vector<int>& data) {
    auto start = high_resolution_clock::now();
    sort_func(data);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

int main() {
    // 考慮到 Insertion Sort O(n^2) 的特性，
    // 若覺得跑太久，可以先將 n 調小 (例如 20000) 觀察差異
    int n = 100000; 
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    vector<int> original(n);
    for(int& x : original) x = dis(gen);

    cout << "--- Performance Test (Manual Implementation, n = " << n << ") ---" << endl;
    cout << "Note: Insertion Sort may take a while for large n..." << endl;

    // 1. Smooth Sort
    vector<int> a_smooth = original;
    long long t_smooth = measure_time([](vector<int>& v){ smoothsort::smooth_sort(v); }, a_smooth);
    cout << "> Smooth Sort finished." << endl;

    // 2. Manual Heap Sort
    vector<int> a_heap = original;
    long long t_heap = measure_time([](vector<int>& v){ manual_heap_sort(v); }, a_heap);
    cout << "> Heap Sort finished." << endl;

    // 3. Manual Quick Sort
    vector<int> a_quick = original;
    long long t_quick = measure_time([](vector<int>& v){ manual_quick_sort(v); }, a_quick);
    cout << "> Quick Sort finished." << endl;

    // 4. Manual Insertion Sort
    vector<int> a_insertion = original;
    long long t_insertion = measure_time([](vector<int>& v){ manual_insertion_sort(v); }, a_insertion);
    cout << "> Insertion Sort finished." << endl;

    // 統計結果
    cout << "\n" << left << setw(18) << "Algorithm" << setw(15) << "Time (ms)" << "Time (ns)" << endl;
    cout << string(55, '-') << endl;
    cout << left << setw(18) << "Smooth Sort" << setw(15) << t_smooth / 1000000.0 << t_smooth << endl;
    cout << left << setw(18) << "Heap Sort" << setw(15) << t_heap / 1000000.0 << t_heap << endl;
    cout << left << setw(18) << "Quick Sort" << setw(15) << t_quick / 1000000.0 << t_quick << endl;
    cout << left << setw(18) << "Insertion Sort" << setw(15) << t_insertion / 1000000.0 << t_insertion << endl;
    cout << string(55, '-') << endl;

    return 0;
}