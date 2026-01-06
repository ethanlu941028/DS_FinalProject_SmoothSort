#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <string>  // 新增：為了 string 類型
#include <algorithm> // 必須包含，為了執行 std::sort 製造 Best Case
#include "smooth_sort.h" 
#include "../benchmark/baseline.h" 
#include "../benchmark/timer.h" 

using namespace std;

// 顯示效能測試結果
void print_performance_test(int test_size = 100000) {
    cout << "\n--- Performance Test (Manual Implementation, n = " << test_size << ") ---" << endl;
    cout << "Note: Insertion Sort may take a while for large n..." << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, test_size);
    
    vector<int> original(test_size);
    for(int& x : original) x = dis(gen);

    struct TestResult {
        string name;
        long long time_ns;
    };
    
    vector<TestResult> results;

    // 1. Smooth Sort (隨機資料)
    {
        vector<int> a = original;
        long long time_ns = measure_time([](vector<int>& v){ smoothsort::smooth_sort(v); }, a);
        results.push_back({"Smooth Sort", time_ns});
        cout << "> Smooth Sort finished." << endl;
    }

    // 2. Heap Sort
    {
        vector<int> a = original;
        long long time_ns = measure_time([](vector<int>& v){ manual_heap_sort(v); }, a);
        results.push_back({"Heap Sort", time_ns});
        cout << "> Heap Sort finished." << endl;
    }

    // 3. Quick Sort
    {
        vector<int> a = original;
        long long time_ns = measure_time([](vector<int>& v){ manual_quick_sort(v); }, a);
        results.push_back({"Quick Sort", time_ns});
        cout << "> Quick Sort finished." << endl;
    }

    // 4. Insertion Sort (只在較小的數據集上執行)
    if (test_size <= 50000) {
        vector<int> a = original;
        long long time_ns = measure_time([](vector<int>& v){ manual_insertion_sort(v); }, a);
        results.push_back({"Insertion Sort", time_ns});
        cout << "> Insertion Sort finished." << endl;
    } else {
        // 對於大數據集，使用較小的樣本進行 Insertion Sort 測試
        cout << "> Insertion Sort (testing with smaller dataset due to O(n^2) complexity)..." << endl;
        vector<int> small_data(10000);
        for(int i = 0; i < 10000; i++) {
            small_data[i] = original[i % original.size()];
        }
        long long time_ns = measure_time([](vector<int>& v){ manual_insertion_sort(v); }, small_data);
        // 估算 100k 的時間 (粗略的 O(n^2) 估算)
        long long estimated_time = time_ns * (test_size / 10000) * (test_size / 10000);
        results.push_back({"Insertion Sort", estimated_time});
        cout << "> Insertion Sort finished (estimated for n=" << test_size << ")." << endl;
    }

    // 5. STL Sort
    {
        vector<int> a = original;
        long long time_ns = measure_time([](vector<int>& v){ stl_sort(v); }, a);
        results.push_back({"STL Sort", time_ns});
        cout << "> STL Sort finished." << endl;
    }

    // 顯示結果表格
    cout << "\nAlgorithm         Time (ms)      Time (ns)" << endl;
    cout << "-------------------------------------------------------" << endl;
    
    for (const auto& result : results) {
        double time_ms = result.time_ns / 1000000.0;
        cout << left << setw(18) << result.name 
             << fixed << setprecision(4) << setw(14) << time_ms
             << result.time_ns << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}

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
    
    // 顯示詳細的效能測試結果
    print_performance_test(100000);
    
    return 0;
}