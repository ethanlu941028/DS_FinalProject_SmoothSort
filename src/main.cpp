#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <algorithm> // 必須包含，為了執行 std::sort 製造 Best Case
#include "smooth_sort.h" 
#include "../benchmark/baseline.h" 
#include "../benchmark/timer.h" 

using namespace std;

int main() {
    vector<int> sizes = {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};
    int num_trials = 3;

    ofstream csv_file("data/benchmark_data.csv");
    // 標頭新增 SmoothSortBest
    csv_file << "n,SmoothSort,SmoothSortBest,HeapSort,QuickSort,InsertionSort,STLSort" << endl;

    cout << "Starting benchmark (including Smoothsort Best Case)..." << endl;

    random_device rd;
    mt19937 gen(rd());

    for (int n : sizes) {
        double t_smooth_sum = 0, t_smooth_best_sum = 0, t_heap_sum = 0, t_quick_sum = 0, t_insertion_sum = 0, t_stl_sum = 0;

        for (int trial = 0; trial < num_trials; ++trial) {
            uniform_int_distribution<> dis(1, n);
            vector<int> original(n);
            for(int& x : original) x = dis(gen);

            // 1. Smooth Sort (一般隨機情況)
            vector<int> a_smooth = original;
            t_smooth_sum += measure_time([](vector<int>& v){ smoothsort::smooth_sort(v); }, a_smooth);

            // --- 新增：Smooth Sort (最優情況：已排序資料) ---
            vector<int> a_smooth_best = original;
            std::sort(a_smooth_best.begin(), a_smooth_best.end()); // 先排好序
            t_smooth_best_sum += measure_time([](vector<int>& v){ smoothsort::smooth_sort(v); }, a_smooth_best);

            // 2. Heap Sort
            vector<int> a_heap = original;
            t_heap_sum += measure_time([](vector<int>& v){ manual_heap_sort(v); }, a_heap);

            // 3. Quick Sort
            vector<int> a_quick = original;
            t_quick_sum += measure_time([](vector<int>& v){ manual_quick_sort(v); }, a_quick);

            // 4. Insertion Sort (防止大數據跑太久)
            if (n <= 50000) {
                vector<int> a_insertion = original;
                t_insertion_sum += measure_time([](vector<int>& v){ manual_insertion_sort(v); }, a_insertion);
            } else { t_insertion_sum = 0; }

            // 5. STL Sort
            vector<int> a_stl = original;
            t_stl_sum += measure_time([](vector<int>& v){ stl_sort(v); }, a_stl);
        }

        // 寫入 CSV，確保欄位順序與標頭一致
        csv_file << n << "," 
                 << (t_smooth_sum / num_trials) / 1000000.0 << ","
                 << (t_smooth_best_sum / num_trials) / 1000000.0 << "," // 這是 Best Case
                 << (t_heap_sum / num_trials) / 1000000.0 << ","
                 << (t_quick_sum / num_trials) / 1000000.0 << ","
                 << (t_insertion_sum / num_trials) / 1000000.0 << ","
                 << (t_stl_sum / num_trials) / 1000000.0 << endl;
        
        cout << "Finished n = " << setw(7) << n << endl;
    }

    csv_file.close();
    cout << "Benchmark complete! Data saved to data/benchmark_data.csv" << endl;
    return 0;
}