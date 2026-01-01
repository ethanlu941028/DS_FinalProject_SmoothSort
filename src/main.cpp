#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "smooth_sort.h" // 確保此檔案在同目錄
#include "../benchmark/baseline.h" // 包含其他排序演算法
#include "../benchmark/timer.h" // 包含計時工具

using namespace std;

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

    // 5. STL Sort (for comparison)
    vector<int> a_stl = original;
    long long t_stl = measure_time([](vector<int>& v){ stl_sort(v); }, a_stl);
    cout << "> STL Sort finished." << endl;

    // 統計結果
    cout << "\n" << left << setw(18) << "Algorithm" << setw(15) << "Time (ms)" << "Time (ns)" << endl;
    cout << string(60, '-') << endl;
    cout << left << setw(18) << "Smooth Sort" << setw(15) << t_smooth / 1000000.0 << t_smooth << endl;
    cout << left << setw(18) << "Heap Sort" << setw(15) << t_heap / 1000000.0 << t_heap << endl;
    cout << left << setw(18) << "Quick Sort" << setw(15) << t_quick / 1000000.0 << t_quick << endl;
    cout << left << setw(18) << "Insertion Sort" << setw(15) << t_insertion / 1000000.0 << t_insertion << endl;
    cout << left << setw(18) << "STL Sort" << setw(15) << t_stl / 1000000.0 << t_stl << endl;
    cout << string(60, '-') << endl;

    return 0;
}